#pragma once
#include "GameInfo.h"

/*
	 깜박거림을 해결하는 방법
	 1. 페이지 플리핑 (DirectX 방식)
			Back Buffer가 존재한다.
	 2. 더블 버퍼링 (WinAPI 방식)
			주 표면 방식에 Buffer에 그려진 그림을 고속복사하여 넣는 방식.
			Buffer : 임시저장공간
			Primary Buffer : 주화면 버퍼
			Back Buffer : 임시 화면 공간
	 
	 directX 11은 쉐이더에서 HLSL 언어를 사용한다

*/

// .lib를 링크 걸어주는 기능이다. 
class CDevice
{
private:
	ID3D11Device* mDevice = nullptr;		// 화면 갱신용 데이터
	ID3D11DeviceContext* mContext = nullptr;

	// 페이지 플리핑 처리용 데이터
	IDXGISwapChain* mSwapChain = nullptr;
	
	// Depth : Depth 또는 Stencil을 저장할 수 있음.
	//	Stencil		: 특수효과 처리 기능
	//	- Depth		: 3 byte
	//	- Stencil	: 1 byte로 처리 
	ID3D11RenderTargetView* mTargetView = nullptr;
	ID3D11DepthStencilView* mDepthView = nullptr;

	HWND mHandleWindow;
	FResolution mResolution;

	bool mWindowMode = true;

public:
	ID3D11Device* GetDevice() const
	{
		return mDevice;
	}

	ID3D11DeviceContext* GetContext() const
	{
		return mContext;
	}

	IDXGISwapChain* GetSwapChain() const
	{
		return mSwapChain;
	}

	const FResolution& GetResolution() const
	{
		return mResolution;
	}

	bool GetWindowMode()	const
	{
		return mWindowMode;
	}

public:
	// 화면, X, Y, 윈도우 모드 (최소화, 창모드, 전체화면 등)
	bool Init(HWND hWnd, unsigned int Width, unsigned int Height, bool WindowMode);
	void ClearBackBuffer(float ClearColor[4]);
	void ClearDepthStencil(float Depth, unsigned char Stencil);
	void SetTarget();
	void Render();

	DECLARE_SINGLE(CDevice);
};

