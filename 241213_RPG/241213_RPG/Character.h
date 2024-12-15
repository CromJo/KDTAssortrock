#pragma once
#include "GameInfo.h"
#include "Object.h"


class CCharacter : public CObject
{
public:
	CCharacter();
	~CCharacter();

protected:
	EJob mJob;
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
	void SetCharacterInfo(int Attack, int Defense, int HP, int MP)
	{
		mAttack = Attack;
		mDefense = Defense;
		mHP = HP;
		mHPMax = mHP;
		mMP = MP;
		mMPMax = mMP;
	}

	bool Damage(int Dmg)
	{
		mHP -= Dmg;

		if (mHP <= 0)
			return true;

		return false;
	}


public:
	bool Init();
	virtual void Output();
	virtual void CharacterExclusive() final;

};

