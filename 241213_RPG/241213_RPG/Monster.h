#pragma once

#include "GameInfo.h"

class CMonster
{
	friend class CObjectManager;
	friend class CBattle;

private:
	CMonster();
	~CMonster();

private:
	char	mName[32] = {};
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
	int GetAttack()
	{
		return mAttack;
	}

	int GetDefense()
	{
		return mDefense;
	}

	int GetExp()
	{
		return mExp;
	}

	int GetGold()
	{
		return mGold;
	}

	bool Damage(int Dmg)
	{
		mHP -= Dmg;

		if (mHP <= 0)
			return true;

		return false;
	}

public:
	bool Init(FILE* File);
	void Output();

	// 자신을 복제한 새로운 몬스터를 만들어준다.
	CMonster* Clone();
};

