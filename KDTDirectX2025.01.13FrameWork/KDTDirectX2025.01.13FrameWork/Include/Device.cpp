#include "Device.h"

DEFINITION_SINGLE(CDevice)

CDevice::CDevice()
{

}

CDevice::~CDevice()
{
	SAFE_DELETE(mTargetView);
	SAFE_DELETE(mDepthView);
	SAFE_RELEASE(mSwapChain);

	if (mContext)
		mContext->ClearState();

	SAFE_DELETE(mContext);
	SAFE_DELETE(mDevice);
}

bool CDevice::Init(HWND hWnd, unsigned int Width, unsigned int Height, bool WindowMode)
{
	mHandleWindow = hWnd;
	mResolution.Width = Width;
	mResolution.Height = Height;

	unsigned int Flag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG	// ���� ���־�Ʃ����� Debug�� ó�� �ɶ��� ����� �����̴�.
	Flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif	// _DEBUG

	D3D_FEATURE_LEVEL FLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FLevelResult;

	// 1��° ���� : �⺻ Adapter�� ó���ȴ�. (ù��° �׷���ī���)
	// 2��° ���� : �׷���ī�尡 ���� ��� CPU�� ó���ϵ��� �������ִ� ���
	// 3��° ���� :
	// 4��° ���� : 
	// 5��° ���� : �������� ������ ����
	// ��� : Device�� DeviceContext�� �����Ѵ�.
	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, Flag,
		&FLevel, 1, D3D11_SDK_VERSION, &mDevice, &FLevelResult, &mContext)))
	{
		return false;
	}

	unsigned int SampleCount = 4;
	unsigned int Check = 0;
	// ������ Device�� �̿��Ͽ� �����Ǵ� ��Ƽ���ø� ���� ���´�.
	mDevice->CheckMultisampleQualityLevels
	(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &Check);

	if (Check < 1)
		SampleCount = 1;

	// SwapChain�� �����Ѵ�.
	DXGI_SWAP_CHAIN_DESC SwapDesc = {};

	// BufferDesc : ����ۿ� ���� ����.
	// ������� ���� �ػ󵵸� ����.
	SwapDesc.BufferDesc.Width = Width;

	// ������� ���� �ػ󵵸� ����.
	SwapDesc.BufferDesc.Height = Height;

	// ������� �ȼ� ������ ����.
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// ȭ�� �ֻ���(Hz) ����.
	SwapDesc.BufferDesc.RefreshRate.Numerator = 1;
	SwapDesc.BufferDesc.RefreshRate.Denominator = 60;

	// ȭ�� ���� ���� �� �����ϸ� ó��.
	SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// BackBuffer�� ������ ó���ϴ� ��� ����.
	SwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	// BackBuffer ���� ����.
	SwapDesc.BufferCount = 1;

	// ������ �뵵�� ����.
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// ����� ������ �ڵ��� ����.
	SwapDesc.OutputWindow = hWnd;

	// ��Ƽ���ø�(MSAA : Multi Sample Anti Alliasing)
	// Alliasing : Ȯ�� �� ����� �ڱ۰Ÿ��� ����
	// Anti Alliasing : ������ ���κп� ����� �༭ �ڱ۰Ÿ��� �ʰ� ��.
	SwapDesc.SampleDesc.Quality = 0;
	SwapDesc.SampleDesc.Count = SampleCount;

	// â��� / Ǯ��ũ�� ��� ����.
	SwapDesc.Windowed = WindowMode;

	// SwapChain�� Buffer�� ��ȯ�� �� ����ϴ� ������ ����.
	// DXGI_SWAP_EFFECT_DISCARD : ���� ������ �����ϰ� ��ȯ.
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	IDXGIDevice* DXGIDevice = nullptr;

	// ��ü�� ������ ���ο��� AddRef�� �صд�.
	mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&DXGIDevice);

	IDXGIAdapter* Adapter = nullptr;
	DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&Adapter);

	IDXGIFactory* Factory = nullptr;
	Adapter->GetParent(__uuidof(IDXGIFactory), (void**)&Factory);

	if (FAILED(Factory->CreateSwapChain(mDevice, &SwapDesc, &mSwapChain)))
	{
		SAFE_RELEASE(Factory);
		SAFE_RELEASE(Adapter);
		SAFE_RELEASE(DXGIDevice);

		return false;
	}

	SAFE_RELEASE(Factory);
	SAFE_RELEASE(Adapter);
	SAFE_RELEASE(DXGIDevice);

	// SwapChain�� ������ Back Buffer�� ���´�.
	ID3D11Texture2D* BackBuffer = nullptr;

	if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer)))
	{
		return false;
	}

	// Back Buffer�� ����ϱ� ���� Render Target�� �����.
	if (FAILED(mDevice->CreateRenderTargetView(BackBuffer, nullptr, &mTargetView)))
	{
		return false;
	}

	// RefCount�� ����.
	SAFE_RELEASE(BackBuffer);

	// Depth, Stencil Buffer�� ������ֱ� ���� Texture�� ����.
	D3D11_TEXTURE2D_DESC	DepthDesc = {};
	DepthDesc.Width = Width;
	DepthDesc.Height = Height;
	DepthDesc.ArraySize = 1;
	// D24	: Depth�� 24bit�� UNORM(0 ~ 1)�� ���ڴ�.
	// S8	: Stencil�� 8bit�� UINT(0 ~ 255)�� ���ڴ�.
	DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthDesc.Usage = D3D11_USAGE_DEFAULT;

	DepthDesc.SampleDesc.Count = SampleCount;
	DepthDesc.SampleDesc.Quality = 0;
	DepthDesc.MipLevels = 1;

	ID3D11Texture2D* DepthBuffer = nullptr;

	if (FAILED(mDevice->CreateTexture2D(&DepthDesc, nullptr, &DepthBuffer)))
	{
		return false;
	}

	// Depth Buffer�� �����.
	if (FAILED(mDevice->CreateDepthStencilView(DepthBuffer, nullptr, &mDepthView)))
	{
		return false;
	}

	SAFE_RELEASE(DepthBuffer);

	D3D11_VIEWPORT ViewPort = {};
	ViewPort.Width = (float)Width;
	ViewPort.Height = (float)Height;
	ViewPort.MaxDepth = 1.f;

	mContext->RSSetViewports(1, &ViewPort);

	return true;
}

void CDevice::ClearBackBuffer(float ClearColor[4])
{
	mContext->ClearRenderTargetView(mTargetView, ClearColor);
}

void CDevice::ClearDepthStencil(float Depth, unsigned char Stencil)
{
	mContext->ClearDepthStencilView(mDepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, Depth, Stencil);
}

void CDevice::SetTarget()
{
	// ��½� ���� ������ RenderTarget �� DepthView�� �����Ѵ�.
	mContext->OMSetRenderTargets(1, &mTargetView, mDepthView);
}

void CDevice::Render()
{
	mSwapChain->Present(0, 0);
}
