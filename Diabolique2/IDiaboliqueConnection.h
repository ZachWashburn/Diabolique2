#ifndef _H_IDIABOLIQUECONNECTION
#define _H_IDIABOLIQUECONNECTION
#ifdef _MSC_VER
#pragma once
#endif

#include "BaseIncludes.h"
#include "DiaboliqueProtocol.h"


typedef IDataTransfer* (__stdcall* fnAutoDataTransferRestarter_t)(IDataTransfer* pOldTransfer);
class IDiaboliqueConnection
{
public:

	void Startup(bool bStartAutoThreads);

	// Not Really Thread Safe.... BE CAREFUL FOR NOW!
	virtual void SetDataTranfer(IDataTransfer* pTransport) { 

		m_pDataTransfer = pTransport; m_bConnectionProblem = false; 
		m_SendingPause.UnPauseThreads();
	}

	virtual void PollRecieveData()
	{ 
		_INTRNL_RecieveDataFromTransfer();

		if ((!m_pDataTransfer->IsConnectionAlive() || m_bConnectionProblem) && m_pRestarterFunction)
		{
			m_SendingPause.PauseThreads();

			m_pDataTransfer = m_pRestarterFunction(m_pDataTransfer);

			m_SendingPause.UnPauseThreads();
		}
		else {
			// just always notify that we are on!
			m_SendingPause.UnPauseThreads();
		}

	};

	virtual void SendMessageToTransfer(diabolique_message_type_t nType, google::protobuf::MessageLite* pMessage);
	virtual void SendSeralizedMessageToTransfer(diabolique_message_type_t nType, void* pMessage, int nMessageSize);
	bool IsConnectionProblem()
	{
		return m_bConnectionProblem;
	}

#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
	virtual std::string GetConnectionName() {
		if (!m_pDataTransfer) { return "unnamed"; }
		else { return m_pDataTransfer->GetConnectionName(); }
	}
#endif


	void SetAutoRestarter(fnAutoDataTransferRestarter_t pfn)
	{
		m_pRestarterFunction = pfn;
	}

protected:
	// main connection 
	// defined as a abstract, so quick swapping of connection
	// methods is allowed.
	IDataTransfer* m_pDataTransfer = nullptr;

	virtual void _INTRNL_GetFetchDataForSend(diabolique_message_type_t& nType, void* pBuffer, size_t nBufferSize, size_t& nDataRecieved) = 0;
	virtual void _INTRNL_HandleMessage(diabolique_message_type_t nType, void* pData, size_t nDataSize) = 0;
	void _INTRNL_RecieveDataFromTransfer();
	void _INTRNL_SendDataToTransfer(void* pData, size_t nDataSize, size_t& nDataSent);
	std::atomic<bool> m_bFatalError = false;
	std::atomic<bool> m_bTransfersDead = false;
	std::mutex m_DataTransferLock;
	fnAutoDataTransferRestarter_t m_pRestarterFunction = nullptr;

	CThreadPauser m_SendingPause;
private:
	// Receiving Network Transmit Data
	message_header_t m_CurrentMessageHeader;
	size_t m_nCurrentMessageHeaderReadPos = 0;

	char* m_pWorkingBuffer = nullptr;
	size_t m_nWorkingBufferSize = 0;
	size_t m_nWorkingBufferPosition = 0;

	void _INTRNL_RecvThread();
	void _INTRNL_SendThread();

	void _INTRNL_HandleDataFromTransfer(char buffer[DIABOLIQUENETWORKBUFFERSIZE], int nDataSizeRecieved);
	std::thread* m_pDataReceiveThread;
	std::thread* m_pDataSendThread;
	std::atomic<bool> m_bKillThread = false;
	std::atomic<bool> m_bConnectionProblem = false;

	std::mutex m_SendingLock;

};

void package_data_for_send(diabolique_message_type_t dmtType, void* pData, size_t nDataSize, void** ppOutData, size_t& nOutDataSize, bool bCompress, bool Encrypt = false);
bool unpackage_data(message_header_t msg_head, void* pData, size_t nDataSize, void** ppOutData, size_t& nOutDataSize);


#endif // _H_IDIABOLIQUECONNECTION