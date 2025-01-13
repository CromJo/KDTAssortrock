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

	std::list<FRect> mBulletList;
	//RECT mRect = { 100, 100, 200, 300 };
	FRect mRect = { 100, 100, 200, 200 };
	


public:
	bool Init(HINSTANCE hInst);
	int Run();

private:
	void Logic();
	void Input(float deltaTime);
	void Update(float deltaTime);
	void PostUpdate(float deltaTime);
	void Collision(float deltaTime);
	void PostCollisionUpdate(float deltaTime);
	void Render(float deltaTime);
	

private:
	void RegisterWindowClass();
	bool Create();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLE(CGameManager)
};