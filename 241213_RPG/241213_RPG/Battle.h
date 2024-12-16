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
	EBattleState mState;

public:
	void SetBattleType(EBattleType Type);
	void SetBattleState(EBattleState State);
	void Run();
};

