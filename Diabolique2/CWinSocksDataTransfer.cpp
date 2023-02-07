#include "CWinSocksDataTransfer.h"



SOCKET CWinSocksDataTransfer::InitializeServerConnection(_initialize_data* pInit)
{

    static WINDOWS_IMPORT_HIDE(getaddrinfo, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(freeaddrinfo, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(closesocket, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(socket, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(bind, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(listen, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(accept, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(WSAStartup, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(WSACleanup, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(inet_ntoa, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(ntohs, "Ws2_32.dll");


    WSADATA wsaData;
    int iResult;
    struct addrinfo* result = NULL;
    struct addrinfo hints;
    SOCKET Socket = INVALID_SOCKET;


    iResult = _WSAStartup.call(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        return Socket;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    SOCKET ListenSocket = INVALID_SOCKET;
    // Resolve the server address and port
    iResult = _getaddrinfo(NULL, pInit->m_Port, &hints, &result);
    if (iResult != 0) {
        _WSACleanup();
        return Socket;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = _socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        _freeaddrinfo(result);
        _WSACleanup();
        return Socket;
    }

    // Setup the TCP listening socket
    iResult = _bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        _freeaddrinfo(result);
        _closesocket(ListenSocket);
        _WSACleanup();
        return Socket;
    }

    _freeaddrinfo(result);

    iResult = _listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        _closesocket(ListenSocket);
        _WSACleanup();
        return Socket;
    }

    // Accept a client socket

    struct sockaddr_in client_info = { 0 };
    int size = sizeof(client_info);
    Socket = _accept(ListenSocket, (sockaddr*)&client_info, &size);
    if (Socket == INVALID_SOCKET) {
        _closesocket(ListenSocket);
        _WSACleanup();
        return Socket;
    }
#if defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT)

#pragma warning( disable : 4996 )
    char* connected_ip = _inet_ntoa(client_info.sin_addr);
    int port = _ntohs(client_info.sin_port);
#pragma warning(default:4996)

    m_Name = std::string(connected_ip);
    m_Name += ":";
    m_Name += std::to_string(port);
#endif


    // No longer need server socket
    _closesocket(ListenSocket);
    m_Socket = Socket;
    SetSocketBlocking(m_Socket, false);
    return Socket;


}
SOCKET CWinSocksDataTransfer::InitializeClientConnection(_initialize_data* pInit)
{
    WSADATA wsaData;
    int iResult;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    SOCKET ConnectSocket = INVALID_SOCKET;

    static WINDOWS_IMPORT_HIDE(getaddrinfo, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(freeaddrinfo, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(closesocket, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(socket, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(connect, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(WSAStartup, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(WSACleanup, "Ws2_32.dll");

    iResult = _WSAStartup.call(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        return ConnectSocket;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;
    // Resolve the server address and port
    iResult = _getaddrinfo(pInit->m_IPAddress, pInit->m_Port, &hints, &result);
    if (iResult != 0) {
        _WSACleanup();
        return ConnectSocket;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = _socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            _WSACleanup();
            return 1;
        }



        // Connect to server.
        iResult = _connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            _closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    if (!SetSocketBlocking(ConnectSocket, false))
    {
        _WSACleanup();
        return INVALID_SOCKET;
    }

    _freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        _WSACleanup();
        return ConnectSocket;
    }

    m_Socket = ConnectSocket;
    return ConnectSocket;
}

bool CWinSocksDataTransfer::Initialize(void* pData, size_t nDataSize)
{
	if (nDataSize < sizeof(_initialize_data))
		return false;

	_initialize_data* pInit = reinterpret_cast<_initialize_data*>(pData);

	if (pInit->m_nSocketOverride != INVALID_SOCKET) 
	{ // probably a local client, or someone won't be communicating like they intend too lmao
		m_Socket = pInit->m_nSocketOverride;
		return true;
	}

    if (pInit->m_bServer)
        return INVALID_SOCKET != InitializeServerConnection(pInit);
    else 
        return INVALID_SOCKET != InitializeClientConnection(pInit);
}

bool CWinSocksDataTransfer::ShutDown()
{
    static WINDOWS_IMPORT_HIDE(shutdown, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(closesocket, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(WSACleanup, "Ws2_32.dll");
    m_Socket = INVALID_SOCKET;
    _shutdown(m_Socket, SD_BOTH);
    _closesocket(m_Socket);
    _WSACleanup();
    return true;
}


bool CWinSocksDataTransfer::SendData(void* pData, size_t nDataSize, size_t& nDataSent)
{
    static WINDOWS_IMPORT_HIDE(send, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(WSAGetLastError, "Ws2_32.dll");

    int iResult = _send(m_Socket, (const char*)pData, nDataSize, NULL);

    if (iResult == SOCKET_ERROR)
    {
        iResult = _WSAGetLastError();
        switch (iResult)
        {

        case WSAEWOULDBLOCK:
            break;
        case WSAENOTCONN:
        case WSAENOTSOCK:
        case WSAESHUTDOWN:
        case WSAECONNABORTED:
        case WSAETIMEDOUT:
        case WSAECONNRESET:
        default:
#ifdef _DEBUG
            printf("Send Socket Error : %d\n", iResult);
#endif
            m_Socket = INVALID_SOCKET;
            return false;
        }

        return false;
    }
    else if (iResult == 0)
    {
        m_Socket = INVALID_SOCKET;
        return false;
    }
    else
    {
        nDataSent += iResult;
    }

    return m_Socket != INVALID_SOCKET;
}

bool CWinSocksDataTransfer::RecvData(void* pBuffer, size_t nBufferSize, size_t& nDataRecieved)
{
    static WINDOWS_IMPORT_HIDE(recv, "Ws2_32.dll");
    static WINDOWS_IMPORT_HIDE(WSAGetLastError, "Ws2_32.dll");

    int iResult = _recv(m_Socket, (char*)pBuffer, nBufferSize, NULL);
    nDataRecieved = 0;


    if (iResult == SOCKET_ERROR)
    {
        iResult = _WSAGetLastError();
        switch (iResult)
        {

        case WSAEWOULDBLOCK:
            break;
        case WSAENOTCONN:
        case WSAENOTSOCK:
        case WSAESHUTDOWN:
        case WSAECONNABORTED:
        case WSAETIMEDOUT:
        case WSAECONNRESET:
        default:
#ifdef _DEBUG
            printf("Recv Socket Error : %d\n", iResult);
#endif
            m_Socket = INVALID_SOCKET;
            m_bAlive = false;
            return false;
        }

        return false;
    }
    else if (iResult == 0)
    {
        m_Socket = INVALID_SOCKET;
        m_bAlive = false;
        return false;
    }
    else
    {
        nDataRecieved += iResult;
    }


    return m_Socket != INVALID_SOCKET;
}

bool CWinSocksDataTransfer::IsConnectionAlive()
{
    return m_Socket != INVALID_SOCKET;
}

bool CWinSocksDataTransfer::SetSocketBlocking(int fd, bool blocking)
{
    static WINDOWS_IMPORT_HIDE(ioctlsocket, "Ws2_32.dll");

    if (fd < 0) return false;
    unsigned long mode = blocking ? 0 : 1;
    return (_ioctlsocket(fd, FIONBIO, &mode) == 0) ? true : false;
}