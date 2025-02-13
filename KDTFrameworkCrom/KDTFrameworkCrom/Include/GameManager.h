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

	std::list<FBullet> mBulletList;
	FVector2D mPlayerPos = { 150.f, 150.f };
	FVector2D mPlayerSize = { 100.f, 100.f };
	
	std::list<FBullet> mEnemyBulletList;
	float mFireTime = 1.f;
	float mFireAccelTime = 0.f;
	float mEnemyDirect = 1.f;
	FRect mEnemyRC = { 1000, 100, 1100, 200 };
	FVector2D mEnemyPos = { 1025.f, 125.f };
	FVector2D mEnemySize = { 50.f, 50.f };

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

