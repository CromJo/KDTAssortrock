#pragma once
#include "GameInfo.h"

class CItem
{
public:
	CItem();
	~CItem();

private:
	char mName[32] = {};
	EItemType::Type mItemType;
	int mOption;
	int mBuy;
	int mSell;

public:
	bool Init(FILE* File);
	void Run();
	void Output();
};

