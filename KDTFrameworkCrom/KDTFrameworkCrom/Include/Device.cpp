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
	// Flag에 or연산을 추가해준다.
	// (Debug모드일 때 BGRA_SUPPORT 및 DEVICE_DEBUG모드도 같이 넣어준다.
	Flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif _DEBUG

	// 컴퓨터가 이 레벨을 지원안할 시 실패를 반환
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

	// 생성된 Device를 이용하여 지원되는 
	// 멀티 샘플링 수를 가지고 온다.
	// 
	mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4,
		&Check);

	if (Check < 1)
		SampleCount = 1;

	// Swap Chain을 생성
	DXGI_SWAP_CHAIN_DESC SwapDesc = {};

	// BufferDesc : Back Buffer에 대한 정의.
	// Back Buffer의 가로 해상도를 지정.
	SwapDesc.BufferDesc.Width = Width;

	// Back Buffer의 새로 해상도를 지정.
	SwapDesc.BufferDesc.Height = Height;

	// Back Buffer의 Pixel Format을 지정.
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// 화면 Hz 지정.
	SwapDesc.BufferDesc.RefreshRate.Numerator = 1;
	SwapDesc.BufferDesc.RefreshRate.Denominator = 60;

	SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	SwapDesc.BufferDesc.ScanlineOrdering =
		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	// Back Buffer 수를 지정.
	SwapDesc.BufferCount = 1;

	// Buffer 용도를 지정.
	// RENDER_TARGET : 화면에 Pixel 정보를 담기위한 Buffer를 Surface(표면)이라고 부름
	//	이런 Surface Buffer들을 출력하기 위한 기능이다.
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// 출력할 Window Handle을 지정
	SwapDesc.OutputWindow = hWnd;

	// Multi Sampling (MSAA : Multi Sample Anti Aliasing)
	// 계단 현상 막기
	SwapDesc.SampleDesc.Quality = 0;
	SwapDesc.SampleDesc.Count = SampleCount;

	// 창모드인지 풀스크린 모드인지 지정.
	SwapDesc.Windowed = WindowMode;

	// SwapChain이 Buffer를 전환할 때 사용할 동작 지정.
	// DXGI_SWAP_EFFECT_DISCARD : 이전 내용 무시 후 전환.
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

	// SwapChain에 생성된 BackBuffer를 얻어온다.
	ID3D11Texture2D* BackBuffer = nullptr;

	if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer)))
		return false;

	// Back Buffer에 출력하기 위한 Render Target 만든다.
	if (FAILED(mDevice->CreateRenderTargetView(BackBuffer, nullptr, &mTargetView)))
		return false;

	// RefCount를 감소.
	SAFE_RELEASE(BackBuffer);

	D3D11_TEXTURE2D_DESC DepthDesc = {};

	// Dpeth, Stencil Buffer를 만들어주기 위한 Texture 생성
	DepthDesc.Width = Width;
	DepthDesc.Height = Height;
	DepthDesc.ArraySize = 1;


	// D24 : Depth 24Bit를 UNORM(0 ~ 1) 로사용
	// S8 : Stencil 8Bit를 UINT(0 ~ 255) 로사용
	DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthDesc.Usage = D3D11_USAGE_DEFAULT;

	DepthDesc.SampleDesc.Count = SampleCount;
	DepthDesc.SampleDesc.Quality = 0;
	DepthDesc.MipLevels = 1;

	ID3D11Texture2D* DepthBuffer = nullptr;

	// 위에서 정의한 Depth Buffer용 Texture를 만든다.
	if (FAILED(mDevice->CreateTexture2D(&DepthDesc, nullptr, &DepthBuffer)))
		return false;

	// Depth Buffer를 만든다.
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
	// Back Buffer를 ClearColor로 매 Frame마다 초기화를 시켜준다.
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
	// Dx11은 RenderTarget이 최대 8개까지 지정해놓고,
	// 한번 출력으로 8개의 RenderTarget을 만들 수 있다.
	// 매개변수1 : Target View의 갯수
	// 매개변수2 : Render Target View의 이중 포인터
	// 매개변수3 : Depth Stencil View
	// 기능 : 출력시 값을 Render Target과 Depth View를 지정.
	mContext->OMSetRenderTargets(1, &mTargetView, mDepthView);
}

void CDevice::Render()
{
	// Present : 일반적인 Page Flipping 방식으로 실행.
	//		Back Buffer가 주표면이 된다. 
	//		주표면이 Back Buffer가된다.
	mSwapChain->Present(0, 0);
}
