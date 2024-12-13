#pragma once

#include "GameInfo.h"

#define	INVENTORY_MAX	10

class CInventory
{
private:
	CInventory();
	~CInventory();

private:
	class CItem* mItem[INVENTORY_MAX] = {};
	int		mCount = 0;

public:
	int GetCount()
	{
		return mCount;
	}

	bool IsFull()
	{
		return mCount == INVENTORY_MAX;
	}

public:
	void AddItem(class CItem* Item);
	void Run();

private:
	void EquipFunction(class CPlayer* Player, int Index);
	void ItemSell(class CPlayer* Player, int Index);

private:
	static CInventory* mInst;

public:
	static CInventory* GetInst()
	{
		if (!mInst)
			mInst = new CInventory;
		return mInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};

