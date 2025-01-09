#pragma once
#include "GameInfo.h"

enum class EMenuButton
{
	None,
	Tetris,		// 본 게임
	Score,		// 상위 10명 점수
	Setting,	// 설정 (맵크기, 커스텀 블록 등)
	Exit		// 게임 종료
};

static class CGameManager
{
private:
	CGameManager();
	~CGameManager();

private:
	EMenuButton MainMenu();

private:
	static CGameManager* Instance;

public:
	static CGameManager* GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new CGameManager;
		}

		return Instance;
	}

	static void DestroyInstance()
	{
		if (Instance)
		{
			delete Instance;
			Instance = nullptr;
		}
	}

public:
	bool Init();
	void Run();
};

