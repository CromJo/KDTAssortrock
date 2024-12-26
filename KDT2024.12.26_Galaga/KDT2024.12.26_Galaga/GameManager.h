#pragma once
#include "GameInfo.h"

enum class EMainMenu
{
	None,
	Stage,
	Score,
	Exit
};

class CGameManager
{
	// ����, ����� ���ϵ��� private ó��.
private:
	EMainMenu Menu();

public:
	bool Init();
	void Run();
	
	DECLARE_SINGLE(CGameManager)
};
