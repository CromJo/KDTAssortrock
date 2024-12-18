#pragma once
#include "Object.h"

class CCharacter : public CObject
{
public:
	CCharacter();
	CCharacter(const CCharacter& Obj);
	~CCharacter();

protected:
	ECharacterType mType;
	int		mAttack;
	int		mDefense;
	int		mHP;
	int		mHPMax;
	int		mMP;
	int		mMPMax;
	int		mLevel = 1;
	int		mExp = 0;
	int		mGold = 10000;

public:
	void SetCharacterInfo(int Attack, int Defense,
		int HP, int MP)
	{
		mAttack = Attack;
		mDefense = Defense;
		mHP = HP;
		mHPMax = HP;
		mMP = MP;
		mMPMax = MP;
	}

	ECharacterType GetCharacterType()
	{
		return mType;
	}

public:
	bool Init();
	virtual bool Init(FILE* File);
	virtual void Save(FILE* File);
	virtual void Output();
	// final 키워드는 이 클래스를 상속받는 자식
	// 클래스에서 이 키워드가 붙은 함수를
	// 재정의할 수 없게 명시적으로 표현한다.
	virtual void CharacterExclusive()	final;
	virtual CCharacter* Clone() = 0;
};

