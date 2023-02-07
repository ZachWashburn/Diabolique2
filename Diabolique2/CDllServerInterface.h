#pragma once
#if defined(SERVER) && defined(SERVER_DLL)

#include <IDiaboliqueServerInterface.h>
#include <CWinSocksDataTransfer.h>
void __stdcall ModuleCreationResultHandler(CDiaboliqueServerClient* pClient, void* pData, size_t nDataSize)
{

    module_creation_result creation_result;

    if (!creation_result.ParseFromArray(pData, nDataSize))
        return;


    if (creation_result.failure() || !creation_result.has_index())
        printf("\n[client index : %d] Module Creation Failure! (Type : %s)\n", ModuleTypeToString((DiaboliqueModuleType_t)creation_result.type()).c_str());
    else
    {
        pClient->OnModuleCreation(creation_result.index(), (DiaboliqueModuleType_t)creation_result.type());
        printf("\n[client index : %d] Module Creation Success! Index : %d (Type : %s)\n", pClient->GetClientID(), creation_result.index(), ModuleTypeToString((DiaboliqueModuleType_t)creation_result.type()).c_str());
    }
}


void __stdcall ModuleMessageHandler(CDiaboliqueServerClient* pClient, void* pData, size_t nDataSize)
{
    module_message message;

    if (!message.ParseFromArray(pData, nDataSize))
        return;


    size_t _nDataSize = message.data().length();
    char* buffer = (char*)_malloca(_nDataSize + 1);
    memset(buffer, 0, _nDataSize + 1);
    memcpy_s(buffer, _nDataSize, message.data().data(), _nDataSize);

    for (int i = 0; i < _nDataSize; i++)
        buffer[i] = buffer[i] == '\0' ? ' ' : buffer[i];

    printf("%s", buffer);
    _freea(buffer);
}

class CDllServerInterface : public IDiaboliqueServerInterface
{
public:

private:
    virtual void _INTRNL_AcceptClientsThread()
    {
        printf("Creating CDLLServerInterface!\n");
        PopulateCommands();
        while (true)
        {

            CWinSocksDataTransfer* DataTransferServer = new CWinSocksDataTransfer();
            CWinSocksDataTransfer::_initialize_data data_server;
            strcpy(data_server.m_Port, "27100");
            data_server.m_bServer = true;
            data_server.m_nSocketOverride = INVALID_SOCKET;

            DataTransferServer->Initialize(&data_server,
                sizeof(CWinSocksDataTransfer::_initialize_data));

            CDiaboliqueServerClient* client = new CDiaboliqueServerClient();
            client->SetDataTranfer(DataTransferServer);
            client->AddMessageHandler(diabolique_message_type_t::k_dmCTSModuleCreationNotify, &ModuleCreationResultHandler);
            client->AddMessageHandler(diabolique_message_type_t::k_dmATAModuleData, &ModuleMessageHandler);
            int nID = AddClient(client);
            printf("Added Client : %d\n", nID);
        }
    }
};

#define EXPORT extern "C" __declspec(dllexport)
CDllServerInterface* g_pDLLInterface = nullptr;

typedef intptr_t ItemListHandle;
extern "C" __declspec(dllexport) CDllServerInterface * __stdcall Get_Diabolique_Server() { return new CDllServerInterface(); }

extern "C" __declspec(dllexport) bool __stdcall GetConnectedClients(int** itemsFound, int* itemCount)
{
    auto items = g_pDLLInterface->GetClients();
    for (int i = 0; i < 500; i++)
    {
        items.push_back((int)i);
    }
    *itemsFound = items.data();
    *itemCount = items.size();
    return true;
}

extern "C" __declspec(dllexport) int __stdcall GetClientCount()
{
    return g_pDLLInterface->GetClients().size();
}

extern "C" __declspec(dllexport) void __stdcall GetClients(long* len, int** data)
{
    auto clis = g_pDLLInterface->GetClients();
    *len = clis.size();
    auto size = (*len) * sizeof(int);
    *data = static_cast<int*>(malloc(size));
    memcpy(*data, clis.data(), size);
}


#include <Windows.h>
#include <oleauto.h>
extern "C" __declspec(dllexport) BSTR __stdcall GetConnectionName(int nIndex)
{
    bool bFailed = false;
    std::string name = g_pDLLInterface->GetClientName(nIndex, &bFailed);
    std::wstring conv(name.begin(), name.end());
    return SysAllocString(conv.c_str());
}


#endif