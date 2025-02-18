#pragma once

#include "GameInfo.h"

class CDevice
{
private:
	// IUnknown�̶� ���� ��ӹް� �ִ� �ڷ����ε�,
	// 1. IUnknown�� Com��ü�� ���Ѵ�.
	// 2. �����Ҵ��� �ݵ�� Delete�� �ؾ��ϴµ�,
	//	IUnknown�� SmartPointer�� �̿��ؼ� �˾Ƽ� ó���ϵ���
	//	������� �ִ�.
	// 3. IUnknown�� ��ӹ��� �ڷ����� ���� �̸� �տ� I�� �پ��ִ�.
	// 4. I�� ���� �ڷ����� �޸� ���Ž� �ݵ�� �����ϴ� �Լ��� 
	//	����� �����ؾ� �Ѵ�.
	// 5. �޸� ���� �Լ� : Release() �Լ�
	ID3D11Device* mDevice = nullptr;
	// 6. Device Context��� ���� �ִµ� �̰������� ������ ���ӹ޾�
	//	����� �� �ְ� �ȴ�.
	// 7. ��κ��� ����� Device�� �ƴ� DeviceContext���� �̷������.
	ID3D11DeviceContext* mContext = nullptr;

	/*
		0. Buffer��?
			- �ӽ� ���� ������ �ǹ�
			- ȭ�鿡 1280 x 720 �ȼ�(��)���� �̷�����ִµ�,
				���� �����ϱ� ���� ������ �ǹ��Ѵ�.
			- �� ǥ�� ����
		1. Double Buffer
			- Back Buffer�� �̸� �׸��� �׷��ְ�,
				Main Buffer�� ��Ӻ��縦 �������ν�,
				�����̴� ������ �����ϴ� ����̴�.

		2. Flipping Buffer (Page Flipping)
			- DirectX���� ����ϴ� ��Ӻ��� ���
			- Back Buffer�� �̸� �׸��� �׷��ְ�,
				Back Buffer�� Main Buffer�� ������ش�.
				�� Back Buffer -> Main Buffer�� �ǰ�,
				Main Buffer -> Back Buffer�� �ȴ�.
	*/

	// Page Flipping ó���� ���� ���.
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
