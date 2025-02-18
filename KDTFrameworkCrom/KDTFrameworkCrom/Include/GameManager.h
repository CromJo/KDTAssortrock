#pragma once
#include "GameInfo.h"

class CGameManager
{
private:
	HINSTANCE mHandleInstance = 0;
	HWND mHandleWindow = 0;
	HDC mHandleDC = 0;
	
	TCHAR	mClassName[256] = {};
	TCHAR	mTitleName[256] = {};

	float mClearColor[4] = {};

	static bool mLoop;

public:
	// 초기화를 하기위한 함수
	bool Init(HINSTANCE hInstance);
	int Run();

private:
	// 순차적으로 돌리기 위한 함수
	void Logic();
	// 키 입력 기능을 처리하기 위한 함수
	// C++ 시 DeltaTime 개념에 대해 배웠음.
	// DeltaTime 개념을 이용하여 만듦
	void Input(float DeltaTime);
	// 데이터 갱신 역할의 함수
	void Update(float DeltaTime);
	// 데이터들이 업데이트 이후 처리할 함수
	void PostUpdate(float DeltaTime);
	// 충돌 처리 함수
	void Collision(float DeltaTime);
	// 충돌 후 갱신을 위한 함수
	void PostCollision(float DeltaTime);
	// 화면에 출력 역할 함수
	void Render(float DeltaTime);
	


private:
	void RegisterWindowClass();
	// 윈도우를 만들고 보여주기 위한 함수
	bool Create();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLE(CGameManager)
};

