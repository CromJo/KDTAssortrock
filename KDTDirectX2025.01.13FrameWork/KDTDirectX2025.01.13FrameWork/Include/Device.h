#pragma once
#include "GameInfo.h"

/*
	 ���ڰŸ��� �ذ��ϴ� ���
	 1. ������ �ø��� (DirectX ���)
			Back Buffer�� �����Ѵ�.
	 2. ���� ���۸� (WinAPI ���)
			�� ǥ�� ��Ŀ� Buffer�� �׷��� �׸��� ��Ӻ����Ͽ� �ִ� ���.
			Buffer : �ӽ��������
			Primary Buffer : ��ȭ�� ����
			Back Buffer : �ӽ� ȭ�� ����
	 
	 directX 11�� ���̴����� HLSL �� ����Ѵ�

*/

// .lib�� ��ũ �ɾ��ִ� ����̴�. 
class CDevice
{
private:
	ID3D11Device* mDevice = nullptr;		// ȭ�� ���ſ� ������
	ID3D11DeviceContext* mContext = nullptr;

	// ������ �ø��� ó���� ������
	IDXGISwapChain* mSwapChain = nullptr;
	
	// Depth : Depth �Ǵ� Stencil�� ������ �� ����.
	//	Stencil		: Ư��ȿ�� ó�� ���
	//	- Depth		: 3 byte
	//	- Stencil	: 1 byte�� ó�� 
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
	// ȭ��, X, Y, ������ ��� (�ּ�ȭ, â���, ��üȭ�� ��)
	bool Init(HWND hWnd, unsigned int Width, unsigned int Height, bool WindowMode);
	void ClearBackBuffer(float ClearColor[4]);
	void ClearDepthStencil(float Depth, unsigned char Stencil);
	void SetTarget();
	void Render();

	DECLARE_SINGLE(CDevice);
};

