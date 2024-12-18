#pragma once

#include "GameInfo.h"

class CBattle
{
public:
	CBattle();
	virtual ~CBattle();

protected:
	EBattleType	mType;

public:
	void Run();
};

