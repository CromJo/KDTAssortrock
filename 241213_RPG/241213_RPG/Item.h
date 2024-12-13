#pragma once

#include "GameInfo.h"

class CItem
{
public:
	CItem();
	~CItem();

private:
	char	mName[32] = {};
	EItemType::Type	mItemType;
	int		mOption;
	int		mBuy;
	int		mSell;

public:
	const char* GetName()
	{
		return mName;
	}

	EItemType::Type GetItemType()
	{
		return mItemType;
	}

	int GetOption()
	{
		return mOption;
	}

	int GetBuy()
	{
		return mBuy;
	}

	int GetSell()
	{
		return mSell;
	}

public:
	bool Init(FILE* File);
	void Output();
	CItem* Clone();
};

