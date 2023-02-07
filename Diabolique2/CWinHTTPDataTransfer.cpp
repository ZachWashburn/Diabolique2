#include "CWinHTTPDataTransfer.h"
#include <winhttp.h>

// SESSIONS https://docs.microsoft.com/en-us/windows/win32/winhttp/winhttp-sessions-overview



bool CWinHTTPDataTransfer::Initialize(void* pArgs, size_t nDataSize)
{
	WINDOWS_IMPORT_HIDE(WinHttpOpen, "Winhttp.dll");
	WINDOWS_IMPORT_HIDE(WinHttpConnect, "Winhttp.dll");
	WINDOWS_IMPORT_HIDE(WinHttpOpenRequest, "Winhttp.dll");


	cwinhttpdata_initalization_data_t data;


	//WinHttpOpen(

	int nSize = 0;
	void* pStack = nullptr; // PASS_TYPE(testing_function)::dump_arguments_memory(init, nSize);
	CREATE_PASS_TYPE_CALL_MEMORY(WinHttpOpen, nSize, pStack, NULL, NULL, NULL, NULL, NULL);


	return true;
}





void test()
{

}

