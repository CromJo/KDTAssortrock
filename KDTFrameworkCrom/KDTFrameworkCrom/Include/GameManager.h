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
	// �ʱ�ȭ�� �ϱ����� �Լ�
	bool Init(HINSTANCE hInstance);
	int Run();

private:
	// ���������� ������ ���� �Լ�
	void Logic();
	// Ű �Է� ����� ó���ϱ� ���� �Լ�
	// C++ �� DeltaTime ���信 ���� �����.
	// DeltaTime ������ �̿��Ͽ� ����
	void Input(float DeltaTime);
	// ������ ���� ������ �Լ�
	void Update(float DeltaTime);
	// �����͵��� ������Ʈ ���� ó���� �Լ�
	void PostUpdate(float DeltaTime);
	// �浹 ó�� �Լ�
	void Collision(float DeltaTime);
	// �浹 �� ������ ���� �Լ�
	void PostCollision(float DeltaTime);
	// ȭ�鿡 ��� ���� �Լ�
	void Render(float DeltaTime);
	


private:
	void RegisterWindowClass();
	// �����츦 ����� �����ֱ� ���� �Լ�
	bool Create();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLE(CGameManager)
};

