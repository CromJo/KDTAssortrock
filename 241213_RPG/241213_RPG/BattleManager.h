#pragma once

#include "GameInfo.h"

namespace EBattleMenu
{
	enum Type
	{
		None,
		Easy,
		Normal,
		Hard,
		Back
	};
}

class CBattleManager
{
	// friend : 지정하는 클래스에서 이 클래스의
	// private에 접근할 수 있게 한다.
	friend class CGameManager;

private:
	CBattleManager();
	~CBattleManager();

private:
	EBattleMenu::Type Menu();

public:
	bool Init();
	void Run();
};

