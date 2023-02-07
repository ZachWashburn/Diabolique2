// WindowsImportHide.cpp : Defines the functions for the static library.
//
#include "WindowsImportHide.h"
#include "RebuiltWindowsAPI.h"
#include <Windows.h>
#include <libloaderapi2.h>
#include <PETools.h>
namespace WindowsImportHide
{
	void* LoadWindowsFunction(const char* szModule, const char* szFuncName)
	{
		HMODULE handle = RebuiltWindowsAPI::GetModuleA(szModule);
		if (!handle)
		{
			WINDOWS_IMPORT_HIDE(LoadLibraryA, "kernel32.dll");
			handle = _LoadLibraryA(szModule);
		}
#ifdef _DEBUG
		void* pFunc = PETools::GetExportAddress(handle, szFuncName);
#else
		void* pFunc = RebuiltWindowsAPI::GetExportAddress(handle, szFuncName);
#endif
		return 	pFunc;
	}

	void* LoadWindowsFunction(const char* szModule, unsigned long ulFuncHash)
	{
		HMODULE handle = RebuiltWindowsAPI::GetModuleA(szModule);

		if (!handle)
		{
			WINDOWS_IMPORT_HIDE(LoadLibraryA, "kernel32.dll");
			handle = _LoadLibraryA(szModule);
		}

		void* pFunc = RebuiltWindowsAPI::GetExportAddressByHash(handle, ulFuncHash);

		return 	pFunc;
	}
}


