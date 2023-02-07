#include "ScreenMelter.h"
#include "BaseIncludes.h"



int nRandWidth = 150, nRandHeight = 15, nSpeed = 1;
int nScreenWidth, nScreenHeight;

LRESULT WINAPI MelterProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch (Msg) {
    case WM_CREATE:
    {
        HDC hdcDesktop = GetDC(HWND_DESKTOP);
        HDC hdcWindow = GetDC(hWnd);
        BitBlt(hdcWindow, 0, 0, nScreenWidth, nScreenHeight, hdcDesktop, 0, 0, SRCCOPY);
        ReleaseDC(hWnd, hdcWindow);
        ReleaseDC(HWND_DESKTOP, hdcDesktop);
        SetTimer(hWnd, 0, nSpeed, NULL);
        ShowWindow(hWnd, SW_SHOW);
    }
    return 0;
    case WM_ERASEBKGND:
        return 0;
    case WM_PAINT:
        ValidateRect(hWnd, NULL);
        return 0;
    case WM_TIMER:
    {
        HDC hdcWindow = GetDC(hWnd);
        int nXPos = (rand() % nScreenWidth) - (nRandWidth / 2),
            nYPos = (rand() % nRandHeight),
            nWidth = (rand() % nRandWidth);
        BitBlt(hdcWindow, nXPos, nYPos, nWidth, nScreenHeight, hdcWindow, nXPos, 0, SRCCOPY);
        ReleaseDC(hWnd, hdcWindow);
    }
    return 0;
    case WM_CLOSE:
    case WM_DESTROY:
    {
        KillTimer(hWnd, 0);
        PostQuitMessage(0);
    }
    return 0;
    }
    return DefWindowProc(hWnd, Msg, wParam, lParam);
}

void MeltScreen()
{
    WINDOWS_IMPORT_HIDE(GetSystemMetrics, "user32.dll");
    WINDOWS_IMPORT_HIDE(GetModuleHandleA, "kernel32.dll");
    WINDOWS_IMPORT_HIDE(RegisterClassA, "User32.dll");
    WINDOWS_IMPORT_HIDE(CreateWindowExA, "User32.dll");

    int nScreenWidth = _GetSystemMetrics(SM_CXSCREEN);
    int nScreenHeight = _GetSystemMetrics(SM_CYSCREEN);

    WNDCLASSA wndClass = 
    { 0, MelterProc, 0, 0, _GetModuleHandleA(NULL), NULL, LoadCursor(NULL, IDC_ARROW), 0, NULL, XorStr("Melter") };
    if (!_RegisterClassA(&wndClass)) return;

    HWND hWnd = _CreateWindowExA
    (0, XorStr("Melter"), NULL, WS_POPUP, 0, 0, nScreenWidth, nScreenHeight, HWND_DESKTOP, NULL,
        _GetModuleHandleA(NULL), NULL
    );

    if (!hWnd) return;

    return;
}