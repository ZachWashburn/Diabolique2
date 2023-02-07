#ifndef _H_CWINSOCKSDATATRANSFER
#define _H_CWINSOCKSDATATRANSFER

#ifdef _MSC_VER
#pragma once
#endif

#include <IDataTransfer.h>
#include <BaseIncludes.h>

class CWinSocksDataTransfer : public IDataTransfer
{
public:

#pragma pack(push, 1)
	struct _initialize_data
	{
		char m_IPAddress[64]; // MAXHOSTNAMELEN
		char m_Port[11];
		bool m_bServer;
		SOCKET m_nSocketOverride;
	};
#pragma pack(pop)

	virtual bool Initialize(void* pArgs, size_t nDataSize);
	virtual bool ShutDown();
	virtual bool SendData(void* pData, size_t nDataSize, size_t& nDataSent);
	virtual bool RecvData(void* pBuffer, size_t nBufferSize, size_t& nDataRecieved);
	virtual bool IsConnectionAlive();
#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
	virtual std::string GetConnectionName()
	{
		return m_Name;
	}
#endif
	
protected:
	SOCKET InitializeClientConnection(_initialize_data* pInit);
	SOCKET InitializeServerConnection(_initialize_data* pInit);
	bool SetSocketBlocking(int fd, bool blocking);
private:
	std::atomic<bool> m_bAlive;
	SOCKET m_Socket;

#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
	std::string m_Name;
#endif
};







#endif
