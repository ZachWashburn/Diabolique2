#if !defined(_H_CUPDATEABLEIMAGEDISPLAY) && (defined(SERVER) || defined(_DEBUG) || defined(SERVER_CLIENT))
#define _H_CUPDATEABLEIMAGEDISPLAY
#pragma once

#include <string>
#include <thread>
#include <mutex>


#include <shellscalingapi.h>
#include <d3d9.h>
#include <d3dx9tex.h>

#pragma comment(lib, "Shcore.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

// Uses D3DX9, spawns 3 threads
class CUpdatableImageDisplay
{
public:
	CUpdatableImageDisplay();
	~CUpdatableImageDisplay();

	bool InitializeWindow(int nWidth, int nHeight);


	void AddNewData(std::string image, int nWidth, int nHeight);


	void OnKeyPress(DWORD dwKeyCode);

	bool IsClosed()
	{
		return m_bKill;
	}

protected:
	long InitialDirect3D(HWND hwnd);


	void _INTERNAL_RENDER_THREAD();
	void _INTERNAL_TEXTURE_THREAD();
	void _INTERNAL_MESSAGE_THREAD();
private:

	int m_Width = 0;
	int m_Height = 0;

	IDirect3D9* m_pDirect3D;
	IDirect3DDevice9* m_pDirect3DDevice;

	std::thread* message_thread = nullptr;
	std::thread* render_thread = nullptr;
	std::thread* texture_thread = nullptr;

	struct SSData
	{
		std::mutex m_Lock;
		LPDIRECT3DTEXTURE9 pTex = nullptr;
		std::pair<int, int> m_Dimensions = { 0,0 };
		std::pair<int, int> m_DimensionsInt = { 0,0 };
		bool m_bRendered = true;
	};


	struct ImageData
	{
		std::mutex m_ImageDataLock;
		std::string m_ImageData;
		int m_Height = 0;
		int m_Width = 0;
	};

	ImageData m_ImageData;

	SSData m_ss;
	SSData m_workingss;

	LPD3DXSPRITE m_pSprite = nullptr;
	HWND m_HWND = NULL;

	std::atomic<bool> m_bKill = false;


	float m_flXScale = 1.f;
	float m_flYScale = 1.f;
};


#endif // _H_CUPDATEABLEIMAGEDISPLAY