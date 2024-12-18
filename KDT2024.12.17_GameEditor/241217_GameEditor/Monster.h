#pragma once
#include "Character.h"

enum class EMob : unsigned char
{
	None,
	Orc,
	Goblin,
	Taulen,
	Slime
};

class CMonster : public CCharacter
{
public:
	CMonster();
	CMonster(const CMonster& Obj);
	~CMonster();

protected:
	EMob mMob;
	EBattleType mBattleType;

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

