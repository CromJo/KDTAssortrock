#pragma once
#include "Object.h"

class CCharacter :public CObject
{
public:
	CCharacter();
	virtual ~CCharacter();

protected:
	char mName[32] = {};
	int mAttack = 0;
	int mDefense = 0;
	int mHP = 0;
	int mHPMax = 0;
	int mMP = 0;
	int mMPMax = 0;
	int mLevel = 0;
	int mExp = 0;
	int mGold = 10000;

public:
	void SetCharacterInfo(int aTtack, int Defense, int HP, int MP)
	{

	}

public:
	bool Init();
	virtual void Output();
	virtual void CharacterExclusive() final;
};

