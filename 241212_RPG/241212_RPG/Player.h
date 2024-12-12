#pragma once

#include "GameInfo.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

public:
	int mInput = 0 ;

private:
	char	mName[32] = {};
	EJob	mJob = EJob::None;
	int		mAttack = 0;
	int		mDefense = 0;
	int		mHP = 0;
	int		mHPMax = 0;
	int		mMP = 0;
	int		mMPMax = 0;
	int		mLevel = 0;
	int		mExp = 0;
	int		mGold = 10000;

public:
	bool Init();
	void Output();

public:
	int SelectInput();
	int TargetAttack();

// 선생님께서 만드는 전투에 쓰이는 함수
public:
	int GetAttack();
	int GetDefense();
	int GetExp();
	int GetGold();
	void AddExp(int Exp)
	{
		mExp += Exp;
	}
	void AddGold(int Gold)
	{
		mGold += Gold;
	}
	
	bool Damage(int Dmg)
	{
		mHP -= Dmg;

		if (mHP <= 0)
			return true;

		return false;
	}

	void Resurrection()
	{
		mHP = mHPMax;
		mMP = mMPMax;
		mExp = (int)(mExp * 0.9f);
		mGold *= (int)(mGold * 0.9f);
	}
};

