#include "Device.h"

DEFINITION_SINGLE(CDevice)

CDevice::CDevice()
{

}

CDevice::~CDevice()
{
	SAFE_RELEASE(mSwapChain)

	if (mContext)
		mContext->ClearState();

	SAFE_RELEASE(mContext)
		SAFE_RELEASE(mDevice)
}

bool CDevice::Init(HWND hWnd, unsigned int Width, unsigned int Height, bool WindowMode)
{
	mHandleWindow = hWnd;
	mRS.Width = Width;
	mRS.Height = Height;

	unsigned int Flag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG
	// Flag�� or������ �߰����ش�.
	// (Debug����� �� BGRA_SUPPORT �� DEVICE_DEBUG��嵵 ���� �־��ش�.
	Flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif _DEBUG

	// ��ǻ�Ͱ� �� ������ �������� �� ���и� ��ȯ
	D3D_FEATURE_LEVEL FLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FLevelResult;

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0,
		Flag, &FLevel, 1, D3D11_SDK_VERSION, &mDevice,
		&FLevelResult, &mContext)))
	{
		return false;
	}

	unsigned int SampleCount = 4;
	unsigned int Check = 0;

	// ������ Device�� �̿��Ͽ� �����Ǵ� 
	// ��Ƽ ���ø� ���� ������ �´�.
	// 
	mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4,
		&Check);

	if (Check < 1)
		SampleCount = 1;

	// Swap Chain�� ����
	DXGI_SWAP_CHAIN_DESC SwapDesc = {};

	// BufferDesc : Back Buffer�� ���� ����.
	// Back Buffer�� ���� �ػ󵵸� ����.
	SwapDesc.BufferDesc.Width = Width;

	// Back Buffer�� ���� �ػ󵵸� ����.
	SwapDesc.BufferDesc.Height = Height;

	// Back Buffer�� Pixel Format�� ����.
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// ȭ�� Hz ����.
	SwapDesc.BufferDesc.RefreshRate.Numerator = 1;
	SwapDesc.BufferDesc.RefreshRate.Denominator = 60;

	SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	SwapDesc.BufferDesc.ScanlineOrdering =
		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	// Back Buffer ���� ����.
	SwapDesc.BufferCount = 1;

	// Buffer �뵵�� ����.
	// RENDER_TARGET : ȭ�鿡 Pixel ������ ������� Buffer�� Surface(ǥ��)�̶�� �θ�
	//	�̷� Surface Buffer���� ����ϱ� ���� ����̴�.
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// ����� Window Handle�� ����
	SwapDesc.OutputWindow = hWnd;

	// Multi Sampling (MSAA : Multi Sample Anti Aliasing)
	// ��� ���� ����
	SwapDesc.SampleDesc.Quality = 0;
	SwapDesc.SampleDesc.Count = SampleCount;

	// â������� Ǯ��ũ�� ������� ����.
	SwapDesc.Windowed = WindowMode;

	// SwapChain�� Buffer�� ��ȯ�� �� ����� ���� ����.
	// DXGI_SWAP_EFFECT_DISCARD : ���� ���� ���� �� ��ȯ.
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	IDXGIDevice* DXGIDevice = nullptr;
	mDevice->QueryInterface(__uuidof(IDXGIDevice),
		(void**)&DXGIDevice);

	IDXGIAdapter* Adapter = nullptr;
	DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&Adapter);

	IDXGIFactory* Factory = nullptr;
	Adapter->GetParent(__uuidof(IDXGIFactory), (void**)&Factory);

	if(FAILED(Factory->CreateSwapChain(mDevice, &SwapDesc, &mSwapChain)))
	{
		SAFE_RELEASE(Factory);
		SAFE_RELEASE(Adapter);
		SAFE_RELEASE(DXGIDevice);
	
		return false;
	}

	SAFE_RELEASE(Factory);
	SAFE_RELEASE(Adapter);
	SAFE_RELEASE(DXGIDevice);

	// SwapChain�� ������ BackBuffer�� ���´�.
	ID3D11Texture2D* BackBuffer = nullptr;

	if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer)))
		return false;

	// Back Buffer�� ����ϱ� ���� Render Target �����.
	if (FAILED(mDevice->CreateRenderTargetView(BackBuffer, nullptr, &mTargetView)))
		return false;

	// RefCount�� ����.
	SAFE_RELEASE(BackBuffer);

	D3D11_TEXTURE2D_DESC DepthDesc = {};

	// Dpeth, Stencil Buffer�� ������ֱ� ���� Texture ����
	DepthDesc.Width = Width;
	DepthDesc.Height = Height;
	DepthDesc.ArraySize = 1;


	// D24 : Depth 24Bit�� UNORM(0 ~ 1) �λ��
	// S8 : Stencil 8Bit�� UINT(0 ~ 255) �λ��
	DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthDesc.Usage = D3D11_USAGE_DEFAULT;

	DepthDesc.SampleDesc.Count = SampleCount;
	DepthDesc.SampleDesc.Quality = 0;
	DepthDesc.MipLevels = 1;

	ID3D11Texture2D* DepthBuffer = nullptr;

	// ������ ������ Depth Buffer�� Texture�� �����.
	if (FAILED(mDevice->CreateTexture2D(&DepthDesc, nullptr, &DepthBuffer)))
		return false;

	// Depth Buffer�� �����.
	if (FAILED(mDevice->CreateDepthStencilView(DepthBuffer, nullptr, &mDepthView)))
		return false;

	SAFE_RELEASE(DepthBuffer);

	D3D11_VIEWPORT VP = {};

	VP.Width = (float)Width;
	VP.Height = (float)Height;
	VP.MaxDepth = 1.f;

	mContext->RSSetViewports(1, &VP);

	return true;
}

void CDevice::ClearBackBuffer(float ClearColor[4])
{
	// Back Buffer�� ClearColor�� �� Frame���� �ʱ�ȭ�� �����ش�.
	mContext->ClearRenderTargetView(mTargetView, ClearColor);
}

void CDevice::ClearDepthStencil(float Depth, unsigned char Stencil)
{
	mContext->ClearDepthStencilView(mDepthView, 
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		Depth, Stencil);
}

void CDevice::SetTarget()
{
	// Dx11�� RenderTarget�� �ִ� 8������ �����س���,
	// �ѹ� ������� 8���� RenderTarget�� ���� �� �ִ�.
	// �Ű�����1 : Target View�� ����
	// �Ű�����2 : Render Target View�� ���� ������
	// �Ű�����3 : Depth Stencil View
	// ��� : ��½� ���� Render Target�� Depth View�� ����.
	mContext->OMSetRenderTargets(1, &mTargetView, mDepthView);
}

void CDevice::Render()
{
	// Present : �Ϲ����� Page Flipping ������� ����.
	//		Back Buffer�� ��ǥ���� �ȴ�. 
	//		��ǥ���� Back Buffer���ȴ�.
	mSwapChain->Present(0, 0);
}
