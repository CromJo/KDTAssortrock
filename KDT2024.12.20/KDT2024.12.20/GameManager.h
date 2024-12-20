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
private:
	EMainMenu Menu();

public:
	bool Init();
	void Run();

	DECLARE_SINGLE(CGameManager)
};

