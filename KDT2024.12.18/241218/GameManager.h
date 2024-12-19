#pragma once
#include "GameInfo.h"

enum class EMainMenu
{
	None,
	Maze,
	Score,
	Exit
};

class CGameManager
{
public:
	EMainMenu Menu();

public:
	bool Init();
	void Run();

	DECLARE_SINGLE(CGameManager);
};

