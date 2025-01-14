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

	// FRect (±¸) | FVector2D (½Å)
	//FRect mRect = { 100, 100, 200, 200 };
	FVector2D mPlayerPos = { 150.f, 150.f };
	FVector2D mPlayerSize = { 100.f, 100.f };
	std::list<FBullet> mPlayerBulletList;

	std::list<FBullet> mEnemyBulletList;
	FVector2D mEnemyPos = { 1050.f, 100.f };
	FVector2D mEnemySize = { 100.f, 100.f };
	bool isTopCollision = true;
	float mAttackSpeed = 0.f;
	float mEnemyDirect = 1.f;



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
	void PlayerMoveUpdate(float deltaTime);
	void PlayerAttackUpdate(float deltaTime);

	void EnemyMoveUpdate(float deltaTime);
	void EnemyAttackUpdate(std::list<FBullet>& BulletList, float deltaTime);
	void EnemyBulletUpdate(std::list<FBullet>& BulletList, float deltaTime);

private:
	void RegisterWindowClass();
	bool Create();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_SINGLE(CGameManager)
};