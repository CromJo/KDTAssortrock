#pragma once
#include "GameInfo.h"

class CInventory
{
public:
	static CInventory* mInst;


public:
	CInventory();
	~CInventory();

private:
	char mName[32] = {};
	EItemType::Type mItemType;
	int mItem[10] = {};
	int mOption = 0;
	int mSell = 0;

public:
	bool Init();
	void Run();
	void Output();

public:
	int* GetInventoryItem() { return mItem; }
};

