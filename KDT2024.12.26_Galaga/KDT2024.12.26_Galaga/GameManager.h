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
	// 복사, 상속을 못하도록 private 처리.
private:
	EMainMenu Menu();


public:
	bool Init();
	void Run();
	
	DECLARE_SINGLE(CGameManager)
};
