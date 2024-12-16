#pragma once
#include "GameInfo.h"
#include "Player.h"

class CSkill : public CPlayer
{
public:
	bool Init();
	void Run();

private:
	int mConsume = 0;
protected:
	int GetConsume()
	{
		return mConsume;
	}
	int SetConsume(int value)
	{
		mConsume = value;
	}

	int ConsumeCost(CPlayer* Player, int Cost)
	{
		if (Player->GetMP() < Cost)
			return Player->GetMP() - Cost;
		
		return Cost;
	}

public:
	DECLARE_SINGLE(CSkill)
};

