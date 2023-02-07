#ifndef _H_CDIABOLIQUESERVERCLIENT
#define _H_CDIABOLIQUESERVERCLIENT
#ifdef _MSC_VER
#pragma once
#endif

#include <BaseIncludes.h>
#include <IDiaboliqueConnection.h>

class CDiaboliqueServerClient;
class CDiaboliqueServer;
typedef void(CDiaboliqueServer::* fnServerClientMessageCallback)(CDiaboliqueServerClient* pClient, void* pData, size_t nDataSize);

class CDiaboliqueServerClient : public IDiaboliqueConnection
{
public:

	CDiaboliqueServerClient(int nID, CDiaboliqueServer* pServer) : m_nClientID(nID), m_pOwner(pServer) {}
	CDiaboliqueServerClient(CDiaboliqueServer* pServer) : m_nClientID(0), m_pOwner(pServer) {}
	CDiaboliqueServerClient() {}

	virtual void SetClientID(int nID)
	{
		m_nClientID = nID;
	}

	virtual void SendData(void* pData, size_t nDataSize, size_t& nDataSent)
	{
		_INTRNL_SendDataToTransfer(pData, nDataSize, nDataSent);
	}

	virtual void AddMessageHandler(diabolique_message_type_t nType, fnServerClientMessageCallback pCallback)
	{
		m_Callbacks[nType] = pCallback;
	}

	virtual int GetClientID()
	{
		return m_nClientID;
	}

	virtual void SetOwner(CDiaboliqueServer* pServer)
	{
		m_pOwner = pServer;
	}

	virtual std::map<int, DiaboliqueModuleType_t> GetModuleTypeMap()
	{
		return m_ModuleTypeMap;
	}

	virtual void OnModuleCreation(int nIndex, DiaboliqueModuleType_t nType)
	{
		m_ModuleTypeMap[nIndex] = nType;
	}

	virtual void Disconnect()
	{
		m_pDataTransfer->ShutDown();
	}

protected:
	virtual void _INTRNL_HandleMessage(diabolique_message_type_t nType, void* pData, size_t nDataSize)
	{
		if (!m_pOwner)
			return; 

		fnServerClientMessageCallback pCallback = m_Callbacks[nType];

		if (!pCallback)
			return;

		(m_pOwner->*pCallback)(this, pData, nDataSize);
	}

	virtual void _INTRNL_GetFetchDataForSend(diabolique_message_type_t& nType, void* pBuffer, size_t nBufferSize, size_t& nDataRecieved)
	{
		// TODO : Implement Buffering Send Data!!!!
	}

	int m_nClientID = -1;
	std::map<diabolique_message_type_t, fnServerClientMessageCallback> m_Callbacks;
	std::map<int, DiaboliqueModuleType_t> m_ModuleTypeMap;
	CDiaboliqueServer* m_pOwner = nullptr;
};






#endif // _H_CDIABOLIQUESERVERCLIENT