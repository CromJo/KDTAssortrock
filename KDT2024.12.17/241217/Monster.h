#pragma once
#include "Character.h"
class CMonster :
    public CCharacter
{
public:
	CMonster();
	CMonster(const CMonster& Obj);
	~CMonster();

private:
	EBattleType	mBattleType;

public:
	void SetBattleType(EBattleType Type)
	{
		mBattleType = Type;
	}

	EBattleType GetBattleType()
	{
		return mBattleType;
	}

public:
	bool Init();
	virtual bool Init(FILE* File);
	virtual CMonster* Clone();
};

