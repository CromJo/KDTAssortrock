#pragma once

#include "GameInfo.h"
#include "Character.h"


class CPlayer : public CCharacter
{
public:
	CPlayer();
	CPlayer(const CPlayer& Obj);
	~CPlayer();

private:
	EJob	mJob = EJob::None;
	class CItem* mEquip[EEquip::End] = {};
	class CSkillActive* mSkillArray[2] = {};

public:
	int GetAttack();
	int GetDefense();

	int GetGold()
	{
		return mGold;
	}

	void AddExp(int Exp)
	{
		mExp += Exp;
	}

	void AddGold(int Gold)
	{
		mGold += Gold;
	}

	void Resurrection()
	{
		mHP = mHPMax;
		mMP = mMPMax;
		mExp = (int)(mExp * 0.9f);
		mGold = (int)(mGold * 0.9f);
	}

	class CItem* Equip(class CItem* Item);
	class CItem* GetEquipItem(EEquip::Type Type)
	{
		return mEquip[Type];
	}

public:
	bool Init();
	virtual	void Output();
	virtual CPlayer* Clone();
};

