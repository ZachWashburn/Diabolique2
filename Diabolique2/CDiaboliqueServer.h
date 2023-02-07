#if (defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)) && !defined(SERVER_DLL)
#ifndef _H_CDIABOLIQUESERVER
#define _H_CDIABOLIQUESERVER

#ifdef _MSC_VER
#pragma once
#endif

#include <CDiaboliqueServerClient.h>
#include <BaseIncludes.h>
#include <CUpdateableImageDisplay.h>
#include <CDiaFileTransport.h>
#include <CCurrentEnviroment.h>

class CDiaboliqueServer
{
public:

	void AddMessageHandlerToClient(int nClientID, diabolique_message_type_t nType, fnServerClientMessageCallback pCallback)
	{
		CDiaboliqueServerClient* pCli = GetClientForID(nClientID);
		if (!pCli)
			return;

		pCli->AddMessageHandler(nType, pCallback);
	}

	void SendMessageToClient(int nClientID, diabolique_message_type_t nType, google::protobuf::MessageLite* pMessage)
	{
		CDiaboliqueServerClient* pCli = GetClientForID(nClientID);
		if (!pCli)
			return;

		pCli->SendMessageToTransfer(nType, pMessage);
	}

	void SendMessageToCurrentClient(diabolique_message_type_t nType, google::protobuf::MessageLite* pMessage)
	{
		return SendMessageToClient(m_nCurrentClientID, nType, pMessage);
	}

	void SendModuleMessageToCurrentClient(int nModule, void* pData, size_t nDataSize)
	{
		return SendModuleMessageToClient(m_nCurrentClientID, nModule, pData, nDataSize);
	}

	void SendModuleMessageToClient(int nClientID, int nModule, void* pData, size_t nDataSize)
	{
		CDiaboliqueServerClient* pCli = GetClientForID(nClientID);
		if (!pCli)
			return;


		module_message mod_message;
		mod_message.set_data((char*)pData, nDataSize);
		mod_message.set_module_index(nModule);
	
		pCli->SendMessageToTransfer(diabolique_message_type_t::k_dmATAModuleData, &mod_message);
	}

	void SetCurrentClient(int nClient)
	{
		m_nCurrentClientID = nClient;
	}

	void PollClientData(int nClientID)
	{
		CDiaboliqueServerClient* pCli = GetClientForID(nClientID);
		if (!pCli)
			return;

		pCli->PollRecieveData();

		if (pCli->IsConnectionProblem())
		{
			m_ConnectionLock.lock();
			m_Connections.erase(nClientID);
			delete pCli;
			m_ConnectionLock.unlock();
		}
			

	}

	void PollCurrentClientData()
	{
		PollClientData(m_nCurrentClientID);
	}

	void PollClients()
	{
		m_ConnectionLock.lock();
		for (const auto& cli : m_Connections)
		{
			CDiaboliqueServerClient* pCli = cli.second;
			pCli->PollRecieveData();

			if (pCli->IsConnectionProblem())
			{
				m_Connections.erase(cli.first);
				delete pCli;
			}
		}
		m_ConnectionLock.unlock();
	}

#if defined(SERVER) || defined(DEBUG) || defined(SERVER_CLIENT)
	std::string GetConnectionName(int nIndex, bool* pFailed = nullptr)
	{
		if (pFailed)
			*pFailed = true;
		auto pcli = GetClientForID(nIndex);

		if (!pcli)
			return "";

		if (pFailed)
			*pFailed = false;
	
		return pcli->GetConnectionName();
	}
#endif

	int AddClient(CDiaboliqueServerClient* pClient)
	{
		std::lock_guard<std::mutex> _(m_ConnectionLock);
		unsigned int i = 1; 

		for (auto it = m_Connections.cbegin(), end = m_Connections.cend();
			it != end && i == it->first; ++it, ++i)
		{
		}
		pClient->SetOwner(this);
		m_Connections[i] = pClient;
		pClient->SetClientID(i);
		return i;
	}

	int RemoveClient(int ClientID)
	{
		std::lock_guard<std::mutex> _(m_ConnectionLock);

		if (m_Connections.find(ClientID) == m_Connections.end())
			return {};


		m_Connections[ClientID]->Disconnect();
		delete m_Connections[ClientID];
		m_Connections.erase(ClientID);


		return 0;
	}

	CDiaboliqueServerClient* GetClientForID(int nClientID)
	{
		std::lock_guard<std::mutex> _(m_ConnectionLock);
		if (m_Connections.find(nClientID) == m_Connections.end())
			return nullptr;


		return m_Connections[nClientID];
	}

	std::vector<int> GetClients()
	{
		std::lock_guard<std::mutex> _(m_ConnectionLock);
		std::vector<int> client_indexes;
		for (const auto& cli : m_Connections)
			client_indexes.push_back(cli.first);

		return client_indexes;
	}

	int GetCurrentClient()
	{
		return m_nCurrentClientID;
	}


	std::map<int, DiaboliqueModuleType_t> GetCurrentClientModuleMap()
	{
		std::lock_guard<std::mutex> _(m_ConnectionLock);
		if (m_Connections.find(m_nCurrentClientID) == m_Connections.end())
			return {};

		return m_Connections[m_nCurrentClientID]->GetModuleTypeMap();
	}


	void ModuleCreationResultHandler(CDiaboliqueServerClient* pClient, void* pData, size_t nDataSize)
	{

		module_creation_result creation_result;

		if (!creation_result.ParseFromArray(pData, nDataSize))
			return;

		bool bCurClient = pClient->GetClientID() == m_nCurrentClientID;

		if (creation_result.failure() || !creation_result.has_index())
		{
			if (bCurClient)
			{
				printf("\n[client index : %d] Module Creation Failure! (Type : %s)\n", ModuleTypeToString((DiaboliqueModuleType_t)creation_result.type()).c_str());
			}
		}
		else
		{
			pClient->OnModuleCreation(creation_result.index(), (DiaboliqueModuleType_t)creation_result.type());
			if(bCurClient)
				printf("\n[client index : %d] Module Creation Success! Index : %d (Type : %s)\n", pClient->GetClientID(), creation_result.index(), ModuleTypeToString((DiaboliqueModuleType_t)creation_result.type()).c_str());
		}
	}


	void ModuleMessageHandler(CDiaboliqueServerClient* pClient, void* pData, size_t nDataSize)
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

	void InitializeScreenCaptureWindow(int nWidth, int nHeight)
	{
		if (pUpdatableImage && !pUpdatableImage->IsClosed())
			return;
		else if (pUpdatableImage && pUpdatableImage->IsClosed())
		{
			delete pUpdatableImage;
			pUpdatableImage = nullptr;
		}

		pUpdatableImage = new CUpdatableImageDisplay();


		pUpdatableImage->InitializeWindow(nWidth, nHeight);
	}

	//void __cdecl AddNew

	void ScreenCapImageData(CDiaboliqueServerClient* pClient, void* pData, size_t nDataSize)
	{
		screen_capture scap;
		if (!scap.ParseFromArray(pData, nDataSize))
			return;


		if (!pUpdatableImage)
			return;

		// do file dump
		bool bCurClient = pClient->GetClientID() == m_nCurrentClientID;

		if (!bCurClient)
			return;

		pUpdatableImage->AddNewData(scap.data(), scap.width(), scap.height());

	}

	void FileSegmentHandle(CDiaboliqueServerClient* pClient, void* pData, size_t nDataSize);

private:
	std::map<int, CDiaboliqueServerClient*> m_Connections;
	std::mutex m_ConnectionLock;
	int m_nCurrentClientID = -1;
	CUpdatableImageDisplay* pUpdatableImage = nullptr;
	CDiaFileTransport m_Files;
};



#pragma once


#endif // _H_CDIABOLIQUESERVER
#endif
