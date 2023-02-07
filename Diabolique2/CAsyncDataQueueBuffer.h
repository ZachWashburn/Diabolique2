#ifndef _H_CASYNCDATAQUEUEBUFFER
#define _H_CASYNCDATAQUEUEBUFFER

#ifndef _MSC_VER
#pragma once
#endif

#include <AES/AES.h>
#include <string>

template<int nMaxBuffer = 4096*10>
class CAsyncDataQueueBuffer
{
public:
	struct data_buffer_t
	{
		data_buffer_t(){}
		data_buffer_t(int nDataSize)
		{
			m_pData = malloc(nDataSize);
			info.m_nTotalBufferSize = nDataSize;
		}
		~data_buffer_t() 
		{
			if (m_pData)
				free(m_pData);
		}
		bool has_space(int nSize)
		{
			return (nSize + info.m_nDataOffsetByte) < info.m_nTotalBufferSize;
		}

		struct data_buffer_header_t
		{
			int m_nTotalBufferSize;
			int m_nDataOffsetByte = 0;
		} info;

		void* m_pData = nullptr;
		std::mutex m_DataLock;
	};

	CAsyncDataQueueBuffer(){}
	CAsyncDataQueueBuffer(std::string file_path) : m_BackupFilePath(file_path)
	{
		OpenFile(file_path);
	}

	bool OpenFile(std::string file_path)
	{
		m_pFile = new std::fstream(file_path, std::ios::app | std::ios::out | std::ios::binary | std::ios::in);

		return m_pFile && m_pFile->is_open();
	}

	bool IsOpen()
	{
		return m_pFile && m_pFile->is_open();
	}


	void* GetData(size_t& nDataSize)
	{
		std::lock_guard<std::mutex> _(m_BuffersLock);

		data_buffer_t* pData = GetCurrentRecvBuffer();
		nDataSize = pData->info.m_nTotalBufferSize;

		void* pBuffer = malloc(nDataSize);

		if (!pBuffer)
			return nullptr;

		memcpy(pBuffer, pData->m_pData, nDataSize);

		return pBuffer;
	}

	bool AddData(void* pData, int nDataSize)
	{
		std::lock_guard<std::mutex> _(m_BuffersLock);

		if (nDataSize > nMaxBuffer)
			return false;

		if (!m_DataBuffer.has_space(nDataSize))
		{

		}

		return true;
	}

	void BackupDataBufferToFile()
	{
		const char* szData = m_BackupBuffer.m_pData;

		m_pFile->write(szData, m_BackupBuffer.info.m_nTotalBufferSize);
		m_pFile->flush();
		delete m_BackupBuffer;
		m_BackupBuffer = new data_buffer_t(nMaxBuffer);
	}


protected:




private:


	void CheckBackupRefresh()
	{

	}


	// Assumes Lock Held!
	data_buffer_t* GetCurrentRecvBuffer()
	{

	}


	// we work in bytes, not bits. Because we ain't cool
	// like valve

	std::mutex m_BuffersLock;
	data_buffer_t m_DataBuffer = data_buffer_t(nMaxBuffer);
	data_buffer_t* m_BackupBuffer = new data_buffer_t(nMaxBuffer);

	std::string m_BackupFilePath;

	std::fstream* m_pFile;

	AES m_AESKey;
};



#endif
