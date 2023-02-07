#include "CDiaSocketPassthrough.h"
#include <BaseIncludes.h>

bool CDiaSocketPassthrough::ShutDown()
{
	if (m_bInitialized && m_pSockDataTransfer)
	{
		m_pSockDataTransfer->ShutDown();
		delete m_pSockDataTransfer;
		return false;
	}
}

bool CDiaSocketPassthrough::Initialize(void* pArgs, size_t nDataSize)
{
	socket_passthrough_init init;
	if (!init.ParseFromArray(pArgs, nDataSize))
		return false;


	if (init.server())
	{
		// TODO
		//m_Socket = CreateListenSocket(init);
		return false;
	}


	return (ConnectClientSocket(init) != INVALID_SOCKET) || m_pSockDataTransfer;
}

bool CDiaSocketPassthrough::IsConnectionAlive()
{
	if (m_bInitialized && m_pSockDataTransfer)
		return m_pSockDataTransfer->IsConnectionAlive();


	return true; // TODO
}

//virtual bool SendData(void* pData, size_t nDataSize, size_t& nDataSent) = 0;
//virtual bool RecvData(void* pBuffer, size_t nBufferSize, size_t& nDataRecieved) = 0;
bool CDiaSocketPassthrough::RecvData(void* pBuffer, size_t nBufferSize, size_t& nDataRecieved)
{
	if (m_bInitialized && m_pSockDataTransfer)
		m_pSockDataTransfer->RecvData(pBuffer, nBufferSize, nDataRecieved);

	return false;
}

bool CDiaSocketPassthrough::SendData(void* pBuffer, size_t nDataSize, size_t& nDataSent)
{
	if (m_bInitialized && m_pSockDataTransfer)
		m_pSockDataTransfer->SendData(pBuffer, nDataSize, nDataSent);

	return false;
}

SOCKET CDiaSocketPassthrough::ConnectClientSocket(socket_passthrough_init& init)
{
	WINDOWS_IMPORT_HIDE(WSAStartup, "Ws2_32.dll");

	if (init.ipv6())
		return INVALID_SOCKET; // it's coming soon!
	else
	{
		if (m_pSockDataTransfer)
			return INVALID_SOCKET;

		CWinSocksDataTransfer::_initialize_data old_init_struct;
		strcpy_s(old_init_struct.m_IPAddress, sizeof(old_init_struct.m_IPAddress), init.ip().c_str());
		strcpy_s(old_init_struct.m_Port, sizeof(old_init_struct.m_Port), init.port().c_str());
		old_init_struct.m_bServer = false;
		old_init_struct.m_nSocketOverride = INVALID_SOCKET;
		
		m_pSockDataTransfer = new CWinSocksDataTransfer();

		if (!m_pSockDataTransfer)
			return INVALID_SOCKET;

		if (!m_pSockDataTransfer->Initialize(&old_init_struct, sizeof(old_init_struct)))
		{

			delete m_pSockDataTransfer;
			m_pSockDataTransfer = nullptr;
			return INVALID_SOCKET;
		}

		m_bInitialized = true;
	}

	return INVALID_SOCKET;
}



#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)
bool __stdcall GenerateInitializationForSocketPassthrough(std::string input, void** ppMemory, size_t& nDataSize)
{
	socket_passthrough_init init;
	printf(XorStr("\n\n\n			   === SOCKET PASSTHROUGH INITIALIZATION ===          \n"));
	printf(XorStr("Please Input IP Address (IPv4 or IPv6):\n> "));

	input.clear();
	std::getline(std::cin, input);
	init.set_ip(input);

	printf(XorStr("Please Input Port:\n> "));
	input.clear();
	std::getline(std::cin, input);
	init.set_port(input);

	printf(XorStr("Please Input 1 for IPv6, 0 for IPv4 :\n> "));
	input.clear();
	std::getline(std::cin, input);
	init.set_ipv6(atoi(input.c_str()));

	printf(XorStr("Please Input 1 for Server, 0 for Client :\n> "));
	input.clear();
	std::getline(std::cin, input);
	init.set_server(atoi(input.c_str()));

	printf(XorStr("			 === END SOCKET PASSTHROUGH INITIALIZATION ===          \n\n\n"));

	int nSize = init.ByteSizeLong();

	*ppMemory = malloc(nSize);

	if (!*ppMemory)
		return false;

	if (!init.SerializeToArray(*ppMemory, nSize))
		return false;

	//nDataSize = nSize;

	return true;
}


bool __stdcall UserPassthroughForSocketPassthrough(std::string* input)
{
	*input += "\r\n";
	return true;
}
#endif