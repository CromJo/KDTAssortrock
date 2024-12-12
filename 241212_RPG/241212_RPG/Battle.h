#pragma once

#include "GameInfo.h"

enum class Action
{
	None,
	Attack,
	Defense,
	Consumables,
	Escape
};

class CBattle
{
	friend class CBattleManager;

private:
	CBattle();
	~CBattle();

private:
	EBattleType	mType;

public:
	void SetBattleType(EBattleType Type);
	void Run();
};

