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
	friend class CGameManager;

private:
	CStoreManager();
	~CStoreManager();

private:
	class CStore* mStore[EStoreType::End] = {};

private:
	EStoreMenu::Type Menu();

public:
	bool Init();
	void Run();
};

