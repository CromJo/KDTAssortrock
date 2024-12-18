#pragma once
#include "Character.h"
class CMonster :
    public CCharacter
{
public:
	CMonster();
	CMonster(const CMonster& Obj);
	~CMonster();

protected:
	EBattleType	mBattleType;

public:
	EBattleType GetBattleType()
	{
		return mBattleType;
	}

public:
	bool Init();
	virtual bool Init(FILE* File);
	virtual void Save(FILE* File);
	virtual void Output();
	virtual CMonster* Clone();
};

