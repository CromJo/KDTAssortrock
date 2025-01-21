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
	mWindowMode = WindowMode;

	unsigned int Flag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#ifdef _DEBUG	// 현재 비주얼스튜디오가 Debug로 처리 될때만 실행될 구문이다.
	Flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif	// _DEBUG

	D3D_FEATURE_LEVEL FLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FLevelResult;

	// 1번째 인자 : 기본 Adapter로 처리된다. (첫번째 그래픽카드로)
	// 2번째 인자 : 그래픽카드가 없을 경우 CPU로 처리하도록 갱신해주는 기능
	// 3번째 인자 :
	// 4번째 인자 : 
	// 5번째 인자 : 지원하지 않으면 실패
	// 기능 : Device와 DeviceContext를 생성한다.
	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, Flag,
		&FLevel, 1, D3D11_SDK_VERSION, &mDevice, &FLevelResult, &mContext)))
	{
		return false;
	}

	unsigned int SampleCount = 4;
	unsigned int Check = 0;
	// 생성된 Device를 이용하여 지원되는 멀티샘플링 수를 얻어온다.
	mDevice->CheckMultisampleQualityLevels
	(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &Check);

	if (Check < 1)
		SampleCount = 1;

	// SwapChain을 생성한다.
	DXGI_SWAP_CHAIN_DESC SwapDesc = {};

	// BufferDesc : 백버퍼에 대한 정의.
	// 백버퍼의 가로 해상도를 지정.
	SwapDesc.BufferDesc.Width = Width;

	// 백버퍼의 세로 해상도를 지정.
	SwapDesc.BufferDesc.Height = Height;

	// 백버퍼의 픽셀 포맷을 지정.
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// 화면 주사율(Hz) 지정.
	SwapDesc.BufferDesc.RefreshRate.Numerator = 1;
	SwapDesc.BufferDesc.RefreshRate.Denominator = 60;

	// 화면 길이 조정 시 스케일링 처리.
	SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	// BackBuffer의 한줄을 처리하는 기능 무언가.
	SwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	// BackBuffer 수를 지정.
	SwapDesc.BufferCount = 1;

	// 버퍼의 용도를 지정.
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// 출력할 윈도우 핸들을 지정.
	SwapDesc.OutputWindow = hWnd;

	// 멀티샘플링(MSAA : Multi Sample Anti Alliasing)
	// Alliasing : 확대 시 생기는 자글거리는 현상
	// Anti Alliasing : 색깔의 끝부분에 대비값을 줘서 자글거리지 않게 함.
	SwapDesc.SampleDesc.Quality = 0;
	SwapDesc.SampleDesc.Count = SampleCount;

	// 창모드 / 풀스크린 모드 지정.
	SwapDesc.Windowed = WindowMode;

	// SwapChain이 Buffer를 전환할 때 사용하는 동작을 지정.
	// DXGI_SWAP_EFFECT_DISCARD : 이전 내용을 무시하고 전환.
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	IDXGIDevice* DXGIDevice = nullptr;

	// 객체를 얻어오면 내부에서 AddRef를 해둔다.
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

	// SwapChain에 생성된 Back Buffer를 얻어온다.
	ID3D11Texture2D* BackBuffer = nullptr;

	if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer)))
	{
		return false;
	}

	// Back Buffer에 출력하기 위한 Render Target을 만든다.
	if (FAILED(mDevice->CreateRenderTargetView(BackBuffer, nullptr, &mTargetView)))
	{
		return false;
	}

	// RefCount를 감소.
	SAFE_RELEASE(BackBuffer);

	// Depth, Stencil Buffer를 만들어주기 위한 Texture를 생성.
	D3D11_TEXTURE2D_DESC	DepthDesc = {};
	DepthDesc.Width = Width;
	DepthDesc.Height = Height;
	DepthDesc.ArraySize = 1;
	// D24	: Depth에 24bit를 UNORM(0 ~ 1)로 쓰겠다.
	// S8	: Stencil에 8bit를 UINT(0 ~ 255)로 쓰겠다.
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

	// Depth Buffer를 만든다.
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
	// 출력시 값을 저장할 RenderTarget 및 DepthView를 지정한다.
	mContext->OMSetRenderTargets(1, &mTargetView, mDepthView);
}

void CDevice::Render()
{
	mSwapChain->Present(0, 0);
}
