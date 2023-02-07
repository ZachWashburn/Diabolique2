#include "IDiaboliqueConnection.h"



void IDiaboliqueConnection::Startup(bool bStartAutoThreads)
{
	char* m_pWorkingBuffer = nullptr;
	size_t m_nWorkingBufferSize = 0;
	size_t m_nWorkingBufferPosition = 0;
	m_SendingPause.PauseThreads();
	if (bStartAutoThreads)
	{
		m_pDataReceiveThread = new std::thread(&IDiaboliqueConnection::_INTRNL_RecvThread, this);
		m_pDataSendThread = new std::thread(&IDiaboliqueConnection::_INTRNL_SendThread, this);
	}
}

// Recursive, maybe we should cap max stack size....
// or handle it before and call? Currently this seems fine
// and makes for smaller code
void IDiaboliqueConnection::_INTRNL_HandleDataFromTransfer(char buffer[DIABOLIQUENETWORKBUFFERSIZE], int nDataSizeRecieved)
{
	int nReadPosition = 0;
	int nDataReadAmount = 0;
	// Handle Partial Header Read
	if (m_nCurrentMessageHeaderReadPos < sizeof(message_header_t))
	{
		int nDataLeft = sizeof(message_header_t) - m_nCurrentMessageHeaderReadPos;
		int nDataToRead = min(nDataLeft, nDataSizeRecieved);
		memcpy_s((char*)&m_CurrentMessageHeader + m_nCurrentMessageHeaderReadPos,
			nDataLeft,
			buffer, nDataToRead);

		//	Add Current Read Amount To Buffer
		m_nCurrentMessageHeaderReadPos += nDataSizeRecieved;

		// Take Off The Header Size From The The Total Data

		nDataSizeRecieved -= nDataToRead;
		nReadPosition += nDataToRead;
	}

	if (!nDataSizeRecieved) // okay no data!
		return;

	int nMessageDataSize = m_CurrentMessageHeader.m_nTotalSize;

	if (nMessageDataSize > (DIABOLIQUEMAXNETMESSAGESIZE - sizeof(message_header_t)))
	{
		m_bFatalError = true;
		return; // well we ain't recovering....
	}

	if (!nMessageDataSize)
		return;

	if (!m_pWorkingBuffer)
	{
		m_pWorkingBuffer = (char*)malloc(nMessageDataSize);
		m_nWorkingBufferPosition = 0;
	}

	m_nWorkingBufferSize = nMessageDataSize;

	nDataReadAmount = min((size_t)nDataSizeRecieved, m_nWorkingBufferSize - m_nWorkingBufferPosition);

	memcpy_s(m_pWorkingBuffer + m_nWorkingBufferPosition,
		m_nWorkingBufferSize - m_nWorkingBufferPosition,
		buffer + nReadPosition, nDataReadAmount
	);

	m_nWorkingBufferPosition += nDataReadAmount;
	nDataSizeRecieved -= nDataReadAmount;
	nReadPosition += nDataReadAmount;

	if (m_nWorkingBufferPosition == m_nWorkingBufferSize)
	{
		void* pOutData = nullptr;
		size_t nDataSize = 0;
		if (!unpackage_data(m_CurrentMessageHeader, m_pWorkingBuffer, m_nWorkingBufferSize, &pOutData, nDataSize)
			|| !pOutData)
		{
			if (pOutData)
				free(pOutData);

			free(m_pWorkingBuffer);
			m_pWorkingBuffer = 0;
			m_CurrentMessageHeader = message_header_t();
			m_nWorkingBufferPosition = 0;
			m_nCurrentMessageHeaderReadPos = 0;
		}
		else
		{
			free(m_pWorkingBuffer);
			m_pWorkingBuffer = 0;

			_INTRNL_HandleMessage(m_CurrentMessageHeader.m_nType, pOutData, nDataSize);

			m_CurrentMessageHeader = message_header_t();
			m_nWorkingBufferPosition = 0;
			m_nCurrentMessageHeaderReadPos = 0;

			free(pOutData);
		}
	}

	if (nDataSizeRecieved)
		_INTRNL_HandleDataFromTransfer(buffer + nReadPosition, nDataSizeRecieved);
}

void IDiaboliqueConnection::_INTRNL_RecieveDataFromTransfer()
{
	char buffer[DIABOLIQUENETWORKBUFFERSIZE];

	size_t nDataSizeRecieved;
	bool bSuccess = m_pDataTransfer->RecvData(buffer, sizeof(buffer), nDataSizeRecieved);
	if (!bSuccess || !nDataSizeRecieved)
		return;

	_INTRNL_HandleDataFromTransfer(buffer, nDataSizeRecieved);
}


void IDiaboliqueConnection::SendSeralizedMessageToTransfer(diabolique_message_type_t nType, void* pMessage, int nMessageSize)
{
	std::lock_guard<std::mutex> _(m_SendingLock);

	void* pBuffer = nullptr;
	size_t nAllocationSize = 0;
	package_data_for_send(nType, pMessage, nMessageSize, &pBuffer, nAllocationSize, true);

	if (!pBuffer)
		return;

	size_t nTotalDataSent = 0;
	while (nTotalDataSent < nAllocationSize)
	{
		size_t nDataSent = 0;
		_INTRNL_SendDataToTransfer((char*)pBuffer + nTotalDataSent, nAllocationSize - nTotalDataSent, nDataSent);
		nTotalDataSent += nDataSent;
	}

	free(pBuffer);
}

void IDiaboliqueConnection::SendMessageToTransfer(diabolique_message_type_t nType, google::protobuf::MessageLite* pMessage)
{
	std::lock_guard<std::mutex> _(m_SendingLock);
	int nSize = pMessage->ByteSizeLong();
	int nAllocationSize = nSize;
	void* pBuffer = _malloca(nAllocationSize);

	if (!pBuffer)
		return;

#if 0
	message_header_t* pHeader = reinterpret_cast<message_header_t*>(pBuffer);
	pHeader->m_nTotalSize = nSize;
	strcpy(pHeader->m_CheckSum, DIABOLIQUEPACKETCHECKSUM);
	pHeader->m_nType = nType;
#endif

	if (pMessage->SerializeToArray((char*)pBuffer, nSize))
	{
		//memcpy_s((char*)pBuffer + sizeof(message_header_t), nSize, pData, nDataSize);

		char* pData = nullptr;
		size_t nSizeOfDataToSend = 0;
		package_data_for_send(nType, pBuffer, nSize, (void**)&pData, nSizeOfDataToSend, true);

		nAllocationSize = nSizeOfDataToSend;
		size_t nTotalDataSent = 0;
		while (nTotalDataSent < nAllocationSize)
		{
			size_t nDataSent = 0;
			_INTRNL_SendDataToTransfer((char*)pData + nTotalDataSent, nAllocationSize - nTotalDataSent, nDataSent);
			nTotalDataSent += nDataSent;
		}

		if(pData)
			free(pData);

	}

	_freea(pBuffer);
}

void IDiaboliqueConnection::_INTRNL_SendDataToTransfer(void* pData, size_t nDataSize, size_t & nDataSent)
{
	nDataSent = 0;
	if (!m_pDataTransfer)
		return;

	m_pDataTransfer->SendData(pData, nDataSize, nDataSent);
}

void IDiaboliqueConnection::_INTRNL_RecvThread()
{
	while (!m_bKillThread)
	{
		if (!m_pDataTransfer)
			continue;

		if (!m_pDataTransfer->IsConnectionAlive())
		{
			m_bConnectionProblem = true;
			if (m_pRestarterFunction)
			{
				m_SendingPause.PauseThreads();
				m_pDataTransfer = m_pRestarterFunction(m_pDataTransfer);
				m_SendingPause.UnPauseThreads();
			}
			else
			{
				delete m_pDataTransfer;
				m_pDataTransfer = nullptr;
			}

			continue;
		}

		_INTRNL_RecieveDataFromTransfer();

#if !defined(SERVER) && !defined(SERVER_CLIENT)
		WINDOWS_IMPORT_HIDE(Sleep, "Kernel32.dll");
		_Sleep(100);
#endif

	}
}


void IDiaboliqueConnection::_INTRNL_SendThread()
{
	WINDOWS_IMPORT_HIDE(Sleep, "Kernel32.dll");
	_Sleep(100); // MSVC!!!

	while (!m_bKillThread)
	{
		if (!m_pDataTransfer)
			continue; 
#if !defined(SERVER) || defined(SERVER_CLIENT)
		// printf("send thread waiting!\n");
		_Sleep(1); // MSVC!!!

		m_SendingPause.Check();
#endif
#ifdef _DEBUG
		if (m_bKillThread)
			int l = 0;
#endif

		char buffer[DIABOLIQUENETWORKBUFFERSIZE];
		size_t nDataRead;
		diabolique_message_type_t nType = diabolique_message_type_t::k_dmATAINVALID;
		_INTRNL_GetFetchDataForSend(nType, buffer, sizeof(buffer), nDataRead);

		if (!nDataRead)
			continue;
#if 0
		int nSizeOfDataToSend = sizeof(message_header_t) + nDataRead;
		message_header_t* pMessageHeader = nullptr;
		char* pData = (char*)malloc(nSizeOfDataToSend);
		pMessageHeader = reinterpret_cast<message_header_t*>(pData);
		*pMessageHeader = message_header_t();
		strcpy(pMessageHeader->m_CheckSum, DIABOLIQUEPACKETCHECKSUM);
		pMessageHeader->m_nTotalSize = nDataRead;
		pMessageHeader->m_nType = nType;
		memcpy(pData + sizeof(message_header_t), buffer, nDataRead);
#endif

		char* pData = nullptr;
		size_t nSizeOfDataToSend = 0;
		package_data_for_send(nType, buffer, nDataRead, (void**)&pData, nSizeOfDataToSend, true);


		size_t nTotalDataSent = 0;
		while ((int)nTotalDataSent < nSizeOfDataToSend)
		{
			size_t nDataSent = 0;
			m_pDataTransfer->SendData(pData + nTotalDataSent, nSizeOfDataToSend - nTotalDataSent, nDataSent);
			nTotalDataSent += nDataSent;
		}

		free(pData);
	}
	return;
}


void package_data_for_send(diabolique_message_type_t dmtType, void* pData, size_t nDataSize, void** ppOutData, size_t& nOutDataSize, bool bCompress, bool Encrypt)
{

	void* pDataBuffer = pData;
	bool bCompressed = false;

	message_header_t msgHead;
	memset(&msgHead, 0, sizeof(message_header_t));

	strcpy(msgHead.m_CheckSum, XorStr(DIABOLIQUEPACKETCHECKSUM));

#ifdef DIABOLIQUE_NET_ENCRYPTED
	if (Encrypt)
	{
		// TODO : Enc
		msgHead.m_bEncrypted = true;
	}
#endif

#ifdef DIABOLIQUE_NET_COMPRESSION_ENABLED
	for (; bCompress;)
	{
		mz_ulong nCompressedDataSize = mz_compressBound(nDataSize);

		unsigned char* pCompressedData = (unsigned char*)malloc(nCompressedDataSize);

		if (!pCompressedData)
			break;

		int mzRes = mz_compress2(
			pCompressedData,
			&nCompressedDataSize,
			(unsigned char*)pDataBuffer,
			nDataSize,
			MZ_UBER_COMPRESSION // is speed going to be an issue here?
		);

		if (mzRes != MZ_OK)
			break;

		if (nCompressedDataSize >= nDataSize)
		{
			free(pCompressedData);
			break;
		}

		msgHead.m_nUncompressedSize = nDataSize;

		pDataBuffer = pCompressedData;
		nDataSize = nCompressedDataSize;
		bCompressed = true;
		break;
	}
#endif
	
	msgHead.m_nTotalSize = nDataSize;
	msgHead.m_nType = dmtType;
	nOutDataSize = nDataSize + sizeof(msgHead);

	*ppOutData = malloc(nOutDataSize);


	if (!*ppOutData)
		return;

	memcpy(*ppOutData, &msgHead, sizeof(msgHead));
	memcpy((char*)*ppOutData + sizeof(msgHead), pDataBuffer, nDataSize);

	if (bCompressed)
		free(pDataBuffer);
}

bool unpackage_data(message_header_t msg_head, void* pData, size_t nDataSize, void** ppOutData, size_t& nOutDataSize)
{
	void* pDataBuffer = pData;
	bool bCompressed = false;
	if (strcmp(XorStr(DIABOLIQUEPACKETCHECKSUM), msg_head.m_CheckSum))
		return false;

	if (msg_head.m_nTotalSize > nDataSize)
		return false;

#ifdef DIABOLIQUE_NET_COMPRESSION_ENABLED

	if (msg_head.m_nUncompressedSize)
	{
		unsigned char* pUnCompedBuffer = (unsigned char* )malloc(msg_head.m_nUncompressedSize);

		mz_ulong buffersize = msg_head.m_nUncompressedSize;

		int mzRet = mz_uncompress(pUnCompedBuffer, &buffersize, (unsigned char*)pData, nDataSize);

		if (mzRet != MZ_OK)
			return false;

		pDataBuffer = pUnCompedBuffer;
		bCompressed = true;
		nDataSize = buffersize;
	}
#endif


	*ppOutData = malloc(nDataSize);

	if (!*ppOutData)
		return false;

	memcpy_s(*ppOutData, nDataSize, pDataBuffer, nDataSize);
	nOutDataSize = nDataSize;

	if (bCompressed)
		free(pDataBuffer);

	return true;
}
