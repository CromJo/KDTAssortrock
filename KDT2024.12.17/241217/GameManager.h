#pragma once

#include "GameInfo.h"

namespace EMainMenu
{
	enum Type
	{
		None,
		Battle,
		Store,
		Inventory,
		Exit
	};
}

class CGameManager
{
private:
	EMainMenu::Type Menu();

public:
	bool Init();
	void Run();


	DECLARE_SINGLE(CGameManager)
};

