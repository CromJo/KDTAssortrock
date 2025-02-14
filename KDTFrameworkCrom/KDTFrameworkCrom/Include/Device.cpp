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

	//D3D11CreateDevice();

	return true;
}
