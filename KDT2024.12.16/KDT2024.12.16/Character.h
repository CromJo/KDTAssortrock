#pragma once
#include "GameInfo.h"
#include "Object.h"

class CCharacter abstract : public CObject
{
public:
	CCharacter();
	CCharacter(const CCharacter& Obj);
	~CCharacter();

protected:
	//EJob mJob;
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
	virtual void VirtualPure();				// 1 : 함수에 "= 0"을 넣어 추상화하는 방법
	virtual void VirtualPure1();		// 2 : abstract 키워드를 넣어 추상화하는 방법
	virtual void VirtualPure2();	// 3 : 

};

