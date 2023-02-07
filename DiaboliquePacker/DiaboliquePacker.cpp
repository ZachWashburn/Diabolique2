// DiaboliquePacker.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "DiaboliquePacker.h"

#include "../Diabolique2/miniz.h"
#include <PETools.h>
#include <iostream>
void __declspec(noinline) load_dll(HMODULE hMod)
{
    PETools::INIT_PETools_NoPass();

    PIMAGE_SECTION_HEADER pSectionData = PETools::GetSectionHeaderByName((void*)hMod, ".coke");

    char* pCompDLL = (char*)hMod + pSectionData->VirtualAddress;



    __int32   nFullDataSize = ((float)*(__int32*)pCompDLL);
    __int32   CompDataSize = (*(__int32*)(pCompDLL + sizeof(_int32)));
    
    
    if(CompDataSize > nFullDataSize)
        _asm int 3

    char* pPackedDLL = (char*)malloc(nFullDataSize);
    memset(pPackedDLL, 0xCC, nFullDataSize);

    int ret = mz_uncompress((unsigned char*)pPackedDLL, (mz_ulong*)&nFullDataSize, (unsigned char*)pCompDLL + (sizeof(__int32)*2), CompDataSize);

    if(ret != MZ_OK)
        _asm int 3

    __int64 nSize = *(__int64*)pPackedDLL;
    __int64 lolnSize = nSize;
    __int64 _lolnSize = lolnSize;

    printf("%d\n", nSize);

    void* pBaseAddress = PETools::MapToMemory((char*)pPackedDLL + sizeof(__int64), nSize);

    memset(pPackedDLL, 0xCC, nFullDataSize);
    free(pPackedDLL);

    BOOL(WINAPI * _DllMain)(
        HINSTANCE hinstDLL,
        DWORD fdwReason,
        LPVOID lpReserved) = (decltype(_DllMain))PETools::GetFileEntryPoint(pBaseAddress);

    _DllMain((HINSTANCE)pBaseAddress, DLL_PROCESS_ATTACH, NULL);

}

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


#ifdef PACK_HERE
#include <fstream>

void pack_file(std::string file_name, std::string stub_name, std::string file_name_out)
{
    PETools::INIT_PETools_NoPass();



    std::fstream additional(file_name, std::ios::in | std::ios::binary);
    additional.seekg(0, std::ios::end);
    size_t nAdditionalDllSize = additional.tellg();

    printf("File is %d bytes!\n", nAdditionalDllSize);

    char* pBuffer = (char*)malloc(nAdditionalDllSize + sizeof(__int64));
    additional.seekg(0, std::ios::beg);
    additional.read(pBuffer + sizeof(__int64), nAdditionalDllSize);
    additional.close();

    *(__int64*)pBuffer = nAdditionalDllSize;



    // nFullSize
    // nUncompSize


    int nMaxCompressBounds = mz_compressBound(nAdditionalDllSize + sizeof(__int64));
    __int32* pCompressedFile = (__int32* )malloc(nMaxCompressBounds + (sizeof(__int32)*2));

    int nComp = mz_compress2((unsigned char*)pCompressedFile + (sizeof(__int32) * 2),
        (mz_ulong*)&nMaxCompressBounds, 
        (unsigned char*)pBuffer,
        nAdditionalDllSize + sizeof(__int64), MZ_UBER_COMPRESSION
    );
    pCompressedFile[0] = nAdditionalDllSize + sizeof(__int64);
    pCompressedFile[1] = nMaxCompressBounds;



    printf("Compressed Size Is : %d\n", nMaxCompressBounds);

    if (nComp != 0)
    {
        _asm int 3
    }


    //free(pBuffer);



    std::fstream packer_file(stub_name, std::ios::in | std::ios::binary);
    packer_file.seekg(0, std::ios::end);
    size_t nStubSize = packer_file.tellg();

    printf("Stub Size Is : %d\n", nStubSize);

    char* pStubBuffer = (char*)malloc(nStubSize);
    packer_file.seekg(0, std::ios::beg);
    packer_file.read(pStubBuffer, nStubSize);
    packer_file.close();


    void* pRawData = PETools::AddSection(
        ".coke", pStubBuffer, nStubSize, pCompressedFile,
        nMaxCompressBounds + (sizeof(__int32) * 2),
        nMaxCompressBounds + (sizeof(__int32) * 2),
        IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_MEM_READ | IMAGE_SCN_CNT_UNINITIALIZED_DATA, false
    );

    free(pStubBuffer);
    if (!pRawData)
    {
        _asm int 3
    }






    //free(pStubBuffer);

#if 0
    std::fstream _out(file_name_out.c_str(), std::ios::out | std::ios::binary);
    int nSize = nStubSize; // nMaxCompressBounds + 


    if (!_out.is_open())
    {
        _asm int 3
    }

    for (int i = 0; i < nSize; i+= min(nSize - i, 4096))
    {
        _out.write((const char*)pRawData + i, min(nSize - i, 4096));
        _out.flush();
    }
    _out.close();
#endif

    printf("New File Size Is %d\n", nStubSize);

    HANDLE h = CreateFileA(file_name_out.c_str(),    // name of the file
        GENERIC_WRITE, // open for writing
        0,             // sharing mode, none in this case
        0,             // use default security descriptor
        CREATE_ALWAYS, // overwrite if exists
        FILE_ATTRIBUTE_NORMAL,
        0);
    if (h)
    {


        DWORD dwBytesWritten = NULL;
        for (int i = 0; i < nStubSize;)
        {
            if (!WriteFile(h, pRawData, nStubSize - i, &dwBytesWritten, NULL))
            {
                HRESULT hRes = GetLastError();
                printf("Windows Err : %d\n", hRes);
                _asm int 3;
            }
            i += dwBytesWritten;
        }

        std::cout << "CreateFile() succeeded\n";
        CloseHandle(h);
    }
    else
    {
        std::cerr << "CreateFile() failed:" << GetLastError() << "\n";
    }



    std::cin.get();

    //HMODULE hTest = LoadLibraryA("out.dll");

    std::cout << "Hello World!\n";
}
#endif
#include <Windows.h>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#if 1
#ifndef PACK_HERE
    AllocConsole();
    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);




    while (!IsDebuggerPresent())
    {
        Sleep(200);
    }
    _asm int 3
#endif
#endif

#ifdef PACK_HERE
    AllocConsole();
    FILE* fDummy;
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);


    pack_file("Diabolique2.dll", "..\\ReleaseDLL\\stub.exe", "packerplswork.exe");
    return 0;
#endif


    load_dll(hInstance);

    while (true)
    {
        Sleep(99999999);
    }

    return (int)0;
}
