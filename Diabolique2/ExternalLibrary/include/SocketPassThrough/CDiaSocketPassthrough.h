#ifndef _C_DIASOCKETPASSTHROUGH
#define _C_DIASOCKETPASSTHROUGH

#ifdef _MSC_VER
#pragma once
#endif

#include <IDataTransfer.h>
#include <IDiaboliqueModule.h>
#include <IDiaboliqueIO.h>

// MUHAHAHAHA, abuse my own code to write less of it!
#include <CWinSocksDataTransfer.h>

class CDiaSocketPassthrough : public IDiaboliqueModule
{
public:
	virtual bool Initialize(void* pArgs, size_t nDataSize);
	virtual bool ShutDown();
	virtual bool SendData(void* pData, size_t nDataSize, size_t& nDataSent);
	virtual bool RecvData(void* pBuffer, size_t nBufferSize, size_t& nDataRecieved);
	virtual bool IsConnectionAlive();
	virtual bool FreeLibrary() { return true; }
#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
	virtual std::string GetConnectionName()
	{
		return "SOCKET_PASSTHROUGH";
	}
#endif
private:

	//SOCKET CreateListenSocket(socket_passthrough_init& init);

	SOCKET ConnectClientSocket(socket_passthrough_init& init);

	SOCKET m_Socket;

	CWinSocksDataTransfer* m_pSockDataTransfer = nullptr;
	std::atomic<bool> m_bInitialized = false;
};

inline IDiaboliqueModule* __stdcall CreateSocketPassthrough()
{
	return new CDiaSocketPassthrough();
}

#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)

bool __stdcall GenerateInitializationForSocketPassthrough(std::string input, void** ppMemory, size_t& nDataSize);
bool __stdcall UserPassthroughForSocketPassthrough(std::string* input);

class InitSocketPassthroughPreProcessor : public IDiaboliqueModuleServerDefaultInitializer
{
public:
	InitSocketPassthroughPreProcessor()
	{
		_INIT_AddModulePreProcessor(&UserPassthroughForSocketPassthrough, &GenerateInitializationForSocketPassthrough, (int)DiaboliqueModuleType_t::k_dmtSocketPassthrough, "Socket Passthrough");
	}
};

inline InitSocketPassthroughPreProcessor socket_passthrough;
#endif
#endif // _C_DIASOCKETPASSTHROUGH