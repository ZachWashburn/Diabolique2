#include "CUpdateableImageDisplay.h"
#if  defined(_H_CUPDATEABLEIMAGEDISPLAY)

#include <iostream>
#include <windows.h>
#include <vector>
#include <atlimage.h> 
#include <fstream>
#include <map>
#include <mutex>


WNDPROC prevWndProc;

std::mutex m_DisplaysLock;
std::map<HWND, CUpdatableImageDisplay*> g_Displays;

//CUpdatableImageDisplay* g_pCurrentInstance = nullptr; // HACK HACK HACK HACK!!!!!
LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_MOUSEMOVE:
        break;

    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
    {
        m_DisplaysLock.lock();
        CUpdatableImageDisplay* pUpdatable = g_Displays[hwnd];
        m_DisplaysLock.unlock();
        if (pUpdatable)
            pUpdatable->OnKeyPress(wParam);
        break;
    }
    case WM_LBUTTONDOWN:
        break;
    case WM_WINDOWPOSCHANGING:

        break;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}


LRESULT CALLBACK myNewWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_MOUSEMOVE:
        break;

    case WM_SYSKEYDOWN:
        break;
    case WM_KEYDOWN:
        break;

    case WM_LBUTTONDOWN:
        break;
    case WM_WINDOWPOSCHANGING:
        WINDOWPOS* pos = (WINDOWPOS*)lParam;
        RECT rectFather;
        break;
    }

    return CallWindowProc(prevWndProc, hwnd, uMsg, wParam, lParam);
}
CUpdatableImageDisplay::CUpdatableImageDisplay()
{
#if 0
    if (g_pCurrentInstance)
    {
        MessageBoxA(NULL, "CUpdatableImageDisplay :: CUpdatableImageDisplay ALREADY EXISTS!\n", NULL, NULL);
    }
#endif

    //g_pCurrentInstance = this;
}
CUpdatableImageDisplay::~CUpdatableImageDisplay()
{

    m_bKill = true;

    if (message_thread)
    {
        message_thread->join();
        delete message_thread;
    }

    if (render_thread)
    {
        render_thread->join();
        delete render_thread;
    }

    if (texture_thread)
    {
        texture_thread->join();
        delete texture_thread;
    }
    UnregisterClassA("WIN32WINDOWCLASS", GetModuleHandle(NULL));

    m_DisplaysLock.lock();
    g_Displays.erase(m_HWND);
    m_DisplaysLock.unlock();

    //g_pCurrentInstance = nullptr;
};

long CUpdatableImageDisplay::InitialDirect3D(HWND hwnd)
{
    if (m_pDirect3D && m_pDirect3DDevice)
        return S_FALSE;

    if (!m_pDirect3D)m_pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
    D3DDISPLAYMODE Display;
    m_pDirect3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &Display);
    D3DPRESENT_PARAMETERS Direct3DParametr;
    ZeroMemory(&Direct3DParametr, sizeof(D3DPRESENT_PARAMETERS));
    Direct3DParametr.Windowed = 1;
    Direct3DParametr.SwapEffect = D3DSWAPEFFECT_DISCARD;
    Direct3DParametr.BackBufferFormat = Display.Format;

    Direct3DParametr.BackBufferWidth = m_Width;
    Direct3DParametr.BackBufferHeight = m_Height;
    Direct3DParametr.Windowed = TRUE;
    Direct3DParametr.SwapEffect = D3DSWAPEFFECT_DISCARD; //FLIP does not help
    Direct3DParametr.hDeviceWindow = hwnd;
    //Direct3DParametr.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
#if 0
    Direct3DParametr.MultiSampleType = D3DMULTISAMPLE_NONE;
    Direct3DParametr.MultiSampleQuality = 0;
    Direct3DParametr.BackBufferFormat = D3DFMT_A8R8G8B8;
    Direct3DParametr.BackBufferCount = 2;
    Direct3DParametr.EnableAutoDepthStencil = TRUE;
    Direct3DParametr.AutoDepthStencilFormat = D3DFMT_D16;

#endif


    m_pDirect3D->CreateDevice(D3DADAPTER_DEFAULT,
        D3DDEVTYPE::D3DDEVTYPE_HAL,
        hwnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &Direct3DParametr,
        &m_pDirect3DDevice
    );

    return S_OK;
}

void CUpdatableImageDisplay::OnKeyPress(DWORD dwKeyCode)
{
    switch (dwKeyCode)
    {
    case VK_UP:
        m_flYScale += 0.01f;
        break;
    case VK_DOWN:
        m_flYScale -= 0.01f;
        break;
    case VK_LEFT:
        m_flXScale -= 0.01f;
        break;
    case VK_RIGHT:
        m_flXScale += 0.01f;
        break;
    }
}
void CUpdatableImageDisplay::AddNewData(std::string image, int nWidth, int nHeight)
{
    m_ImageData.m_ImageDataLock.lock();

    m_ImageData.m_ImageData = image;
    m_ImageData.m_Width = nWidth;
    m_ImageData.m_Height = nHeight;

    m_ImageData.m_ImageDataLock.unlock();
}

void CUpdatableImageDisplay::_INTERNAL_RENDER_THREAD()
{
    while (!m_bKill)
    {
#if 0
        RECT rect;
        if (GetWindowRect(hwnd, &rect))
        {
            m_Width  = rect.right - rect.left;
            m_Height = rect.bottom - rect.top;
        }
#endif
        m_pDirect3DDevice->BeginScene();

        if (!m_pSprite)
        {
            D3DXCreateSprite(m_pDirect3DDevice, &m_pSprite);
        }
        m_ss.m_Lock.lock();
        if (m_ss.pTex)
        {
            m_pDirect3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET, 0x00000000, 0,0);
            //D3DXCreateSprite(m_pDirect3DDevice, &m_pSprite);
            m_pSprite->Begin(0);
            D3DXVECTOR3 pos = D3DXVECTOR3(0, 0, 0.0f);


            ::D3DXMATRIX scaling_matrix;
            ::D3DXMATRIX rotation_matrix;
            ::D3DXMATRIX move_matrix;
            ::D3DXMATRIX intermediate_matrix;
            ::D3DXMATRIX final_matrix;

            float scale_x = 0.f;
            float scale_y = 0.f;

            //scale_y = min((float)m_Width / (float)m_ss.m_Dimensions.first, (float)m_Height / (float)m_ss.m_Dimensions.second);

            //::D3DXMatrixScaling(&scaling_matrix, ((float)m_Width / (float)m_ss.m_Dimensions.first) * .9f, scale_y * ((float)m_Height / (float)m_ss.m_Dimensions.second), 1.0f);
            ::D3DXMatrixScaling(&scaling_matrix, m_flXScale, m_flYScale, 1.0f);
            ::D3DXMatrixRotationZ(&rotation_matrix, 0);
            ::D3DXMatrixTranslation(&move_matrix, 0, 0, 1.0f);
            ::D3DXMatrixMultiply(&intermediate_matrix, &scaling_matrix, &rotation_matrix);
            ::D3DXMatrixMultiply(&final_matrix, &intermediate_matrix, &move_matrix);

            m_pSprite->SetTransform(&final_matrix);
 
            m_pSprite->Draw(m_ss.pTex, NULL, NULL, &pos, 0xFFFFFFFF);
            m_pSprite->End();
            m_ss.m_bRendered = true;

        }
        m_ss.m_Lock.unlock();
        m_pDirect3DDevice->EndScene();

        m_pDirect3DDevice->Present(0, 0, 0, 0);
        //UpdateWindow(m_HWND);
      
    }

}

void CUpdatableImageDisplay::_INTERNAL_TEXTURE_THREAD()
{
    while (!m_bKill)
    {
        //auto buf = TakeScreenShot(g_ss.m_DimensionsInt.first, g_ss.m_DimensionsInt.second);

        m_ImageData.m_ImageDataLock.lock();

        if (m_ImageData.m_ImageData.empty())
        {
            m_ImageData.m_ImageDataLock.unlock();
            continue;
        }


        // this whole thing is a hack, but this is super hack....
        // ignore all incoming data until we have rendered....
#if 0
        m_ss.m_Lock.lock();
        if (!m_ss.m_bRendered)
        {
            m_ss.m_Lock.unlock();
            m_ImageData.m_ImageDataLock.unlock();
            continue;
        }
        else if (m_ss.pTex)
        {
            m_ss.pTex->Release();
            m_ss.pTex = nullptr;
        }
        m_ss.m_Lock.unlock();
#endif
        

        m_workingss.m_DimensionsInt = std::pair<int, int>(m_ImageData.m_Width, m_ImageData.m_Height);

        LPDIRECT3DTEXTURE9 pTex = NULL;
        HRESULT hRet = D3DXCreateTextureFromFileInMemory(m_pDirect3DDevice, m_ImageData.m_ImageData.data(), m_ImageData.m_ImageData.size(), &pTex);

        if (pTex)
        {
            if (m_workingss.pTex)
            {
                m_ss.m_Lock.lock();
                if (m_ss.m_bRendered)
                {
                    if (m_ss.pTex)
                    {
                        m_ss.pTex->Release();
                        m_ss.pTex = nullptr;
                    }

                    m_ss.pTex = m_workingss.pTex;
                    m_ss.m_Dimensions = m_workingss.m_Dimensions;
                    m_ss.m_bRendered = false;
                }
                else
                {
                    m_workingss.pTex->Release();
                    m_workingss.pTex = nullptr;
                }
                m_ss.m_Lock.unlock();
            }

            m_workingss.pTex = pTex;
            m_workingss.m_Dimensions = m_workingss.m_DimensionsInt;
            m_ImageData.m_ImageData.clear();
            m_ImageData.m_ImageData.shrink_to_fit();
        }
        else
        {
            int l = 0;
        }
        m_ImageData.m_ImageDataLock.unlock();
    }
    
}

void CUpdatableImageDisplay::_INTERNAL_MESSAGE_THREAD()
{
    //Create a window class structure to define our window
    SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);


    WNDCLASSEXA wcex;
    ZeroMemory(&wcex, sizeof(WNDCLASSEXA)); //ZERO it out
    wcex.cbClsExtra = 0; //no extra bytes
    wcex.cbWndExtra = 0; //no extra bytes
    wcex.cbSize = sizeof(WNDCLASSEXA); //set size in bytes
    wcex.style = CS_HREDRAW | CS_VREDRAW; //Basically states that window should be redraw both HORIZ. and VERT.
    wcex.hInstance = GetModuleHandle(NULL); //Set handle to application instance;
    wcex.lpfnWndProc = MsgProc; //Set message procedure (explained later)
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Set window icon (standard application icon)
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW); //Set window arrow (standard windows arrow)
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //Set clear background
    wcex.lpszClassName = "WIN32WINDOWCLASS"; //Name it w.e you like. 
    wcex.lpszMenuName = NULL; //We are not using a menu at this time.
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION); //Set small window icon (standard application icon)

    //Now we must register the window class
    //Here is an example of some simple error checking
    //This can be quite useful for larger projects to debug errors
    if (!RegisterClassExA(&wcex))
    {
        MessageBoxA(NULL, "CUpdatableImageDisplay :: Failed to register window class", NULL, NULL);
        return;
    }



    RECT r = { 0, 0, m_Width, m_Height };
    DWORD style = WS_THICKFRAME | WS_POPUP | WS_TILEDWINDOW; //The standard windows style. Basic resizeable window |  WS_OVERLAPPEDWINDOW
    AdjustWindowRect(&r, style, false);
    int width = r.right - r.left;  //correct width based on requested client size
    int height = r.bottom - r.top;  //correct height based on requested client size
    int x = GetSystemMetrics(SM_CXSCREEN) / 2 - width / 2; //Centers window on desktop
    int y = GetSystemMetrics(SM_CYSCREEN) / 2 - height / 2; //Centers window on desktop

    //Third step:
    //Create our window
    //lpClassName: MUST BE SAME AS ABOVE FROM WINDOW CLASS
    m_HWND = CreateWindowA("WIN32WINDOWCLASS", "D3D9TUTORIAL_01", style, x, y,
        width, height, NULL, NULL, GetModuleHandleA(NULL), NULL);

    m_DisplaysLock.lock();
    g_Displays[m_HWND] = this;
    m_DisplaysLock.unlock();

    prevWndProc = (WNDPROC)SetWindowLongPtr(m_HWND, GWL_WNDPROC, (LONG_PTR)&myNewWndProc);

    EnableWindow(m_HWND, TRUE);
    //Check window creation



    if (!m_HWND)
    {
        MessageBoxA(NULL, "Failed to create window", NULL, NULL);
        return;
    }

    InitialDirect3D(m_HWND);

    ShowWindow(m_HWND, SW_SHOW);

    render_thread = new std::thread(&CUpdatableImageDisplay::_INTERNAL_RENDER_THREAD, this);
    texture_thread = new std::thread(&CUpdatableImageDisplay::_INTERNAL_TEXTURE_THREAD, this);

    MSG msg;
    while (GetMessageW(&msg, m_HWND, NULL, NULL) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
        //UpdateWindow(m_HWND);
    }

    m_bKill = true;


}

bool CUpdatableImageDisplay::InitializeWindow(int nWidth, int nHeight )
{
    m_Height = nHeight;
    m_Width = nWidth;

    message_thread = new std::thread(&CUpdatableImageDisplay::_INTERNAL_MESSAGE_THREAD, this);


    return true;
}





#endif
