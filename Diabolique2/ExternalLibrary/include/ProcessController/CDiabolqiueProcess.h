/*

	Wrapper For The ProcessController


*/
#ifndef _H_CDIABOLIQUEPROCESS
#define _H_CDIABOLIQUEPROCESS

#ifdef _MSC_VER
#pragma once
#endif
#include <IDiaboliqueModule.h>
#include <IDiaboliqueIO.h>
#include "ProcessController.h"


class CDiaboliqueProcess : public IDiaboliqueModule
{
public:
	CDiaboliqueProcess();

#pragma pack(push, 1)
	struct cdiaboliqueprocess_startup_message_t
	{
		char m_Path[MAX_PATH];
		char m_CmdLine[MAX_PATH];
		BOOL m_bHiddenWindow;
	};
#pragma pack(pop)

	virtual bool Initialize(void* pArgs, size_t nDataSize);
	virtual bool ShutDown();
	virtual bool FreeLibrary();
	virtual bool SendData(void* pData, size_t nDataSize, size_t& nDataSent);
	virtual bool RecvData(void* pBuffer, size_t nBufferSize, size_t& nDataRecieved);
	virtual bool IsConnectionAlive() { return (m_bAlive || !m_bInitialized); } // if we aren't initialized, we have yet to be born

	HANDLE GetProcessHandle()
	{
		return (HANDLE)m_Process.GetProcessHandle();
	}

#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
	virtual std::string GetConnectionName()
	{
		return "CDiaboliqueProcess";
	}
#endif

private:
	ProcessController::CProcess m_Process;
	std::atomic<bool> m_bAlive = false;
	std::atomic<bool> m_bInitialized = false;
};

void InitializeProcessController();
inline IDiaboliqueModule* __stdcall CreateProcessController()
{

	if (!ProcessController::IsInitialized())
	{
		InitializeProcessController();
	}

	return new CDiaboliqueProcess();
}

#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)

bool __stdcall GenerateInitializationForProcess(std::string input, void** ppMemory, size_t& nDataSize);
inline bool __stdcall UserPassthroughForProcess(std::string* input)
{
	*input += "\r\n";
	return true;
}

class InitProcessControllerPreProcessor : public IDiaboliqueModuleServerDefaultInitializer
{
public:
	InitProcessControllerPreProcessor()
	{
		_INIT_AddModulePreProcessor(&UserPassthroughForProcess, &GenerateInitializationForProcess, (int)DiaboliqueModuleType_t::k_dmtProcessController, "Process Controller");
	}
};

inline InitProcessControllerPreProcessor pcpreprocess;


void InitializeProcessController();

#endif // #if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
#endif // _H_CDIABOLIQUEPROCESS