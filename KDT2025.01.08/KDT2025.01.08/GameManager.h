#pragma once
#include "GameInfo.h"

enum class EMenuButton
{
	None,
	Tetris,		// �� ����
	Score,		// ���� 10�� ����
	Setting,	// ���� (��ũ��, Ŀ���� ��� ��)
	Exit		// ���� ����
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

