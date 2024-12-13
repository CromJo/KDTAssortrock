#pragma once

#include "GameInfo.h"

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

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
	class CItem* mEquip[EEquip::End] = {};

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
		mGold = (int)(mGold * 0.9f);
	}

	class CItem* Equip(class CItem* Item);
	class CItem* GetEquipItem(EEquip::Type Type)
	{
		return mEquip[Type];
	}

public:
	bool Init();
	void Output();
};

