#pragma once

#include "GameInfo.h"

namespace EStoreMenu
{
	enum Type
	{
		None,
		Weapon,
		Armor,
		Back
	};
}

class CStoreManager
{
private:
	class CStore* mStoreList[2];

private:
	EStoreMenu::Type Menu();

public:
	bool Init();
	void Run();

	DECLARE_SINGLE(CStoreManager)
};

