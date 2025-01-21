#pragma once
#include "GameInfo.h"

class CGameManager
{
private:
	static bool mLoop;
	HINSTANCE mHandleInstance = 0;
	HWND mHandleWindow = 0;
	HDC mHandleDC = 0;
	
	TCHAR mClassName[256] = {};
	TCHAR mTitleName[256] = {};

	float mClearColor[4] = {};

public:
	HINSTANCE GetWindowInstance()	const
	{
		return mHandleInstance;
	}

	HWND GetWindowHandle()	const
	{
		return mHandleWindow;
	}

public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	void Logic();
	void Input(float deltaTime);
	void Update(float deltaTime);
	void Collision(float deltaTime);
	void Render(float deltaTime);
	
private:
	void RegisterWindowClass();
	bool Create();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLE(CGameManager)
};