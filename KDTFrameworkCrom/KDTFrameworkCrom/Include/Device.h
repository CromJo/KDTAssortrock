#pragma once

#include "GameInfo.h"

class CDevice
{
private:
	// IUnknown이란 것을 상속받고 있는 자료형인데,
	// 1. IUnknown은 Com객체를 말한다.
	// 2. 동적할당은 반드시 Delete를 해야하는데,
	//	IUnknown은 SmartPointer를 이용해서 알아서 처리하도록
	//	만들어져 있다.
	// 3. IUnknown을 상속받은 자료형은 전부 이름 앞에 I가 붙어있다.
	// 4. I가 붙은 자료형은 메모리 제거시 반드시 제공하는 함수를 
	//	사용해 제거해야 한다.
	// 5. 메모리 제거 함수 : Release() 함수
	ID3D11Device* mDevice = nullptr;
	// 6. Device Context라는 것이 있는데 이것을통해 권한을 위임받아
	//	사용할 수 있게 된다.
	// 7. 대부분의 기능은 Device가 아닌 DeviceContext에서 이루어진다.
	ID3D11DeviceContext* mContext = nullptr;

	/*
		0. Buffer란?
			- 임시 저장 공간을 의미
			- 화면에 1280 x 720 픽셀(점)으로 이루어져있는데,
				색을 저장하기 위한 공간을 의미한다.
			- 주 표면 버퍼
		1. Double Buffer
			- Back Buffer에 미리 그림을 그려주고,
				Main Buffer에 고속복사를 해줌으로써,
				깜빡이는 현상을 제거하는 기술이다.

		2. Flipping Buffer (Page Flipping)
			- DirectX에서 사용하는 고속복사 기능
			- Back Buffer에 미리 그림을 그려주고,
				Back Buffer를 Main Buffer로 만들어준다.
				즉 Back Buffer -> Main Buffer가 되고,
				Main Buffer -> Back Buffer가 된다.
	*/

	// Page Flipping 처리를 위한 사용.
	IDXGISwapChain* mSwapChain = nullptr;
	
	ID3D11RenderTargetView* mTargetView = nullptr;
	ID3D11DepthStencilView* mDepthView = nullptr;

	HWND mHandleWindow;
	FResolution mRS;

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
		return mRS;
	}

public:
	bool Init(HWND hWnd, unsigned int Width, 
		unsigned int Height, bool WindowMode);
	void ClearBackBuffer(float ClearColor[4]);
	void ClearDepthStencil(float Depth, unsigned char Stencil);
	void SetTarget();
	void Render();

	DECLARE_SINGLE(CDevice)
};
