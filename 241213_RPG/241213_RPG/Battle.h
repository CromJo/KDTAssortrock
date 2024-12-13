#pragma once

#include "GameInfo.h"

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

