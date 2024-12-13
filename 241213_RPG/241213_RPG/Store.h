#pragma once

#include "GameInfo.h"

class CStore
{
public:
	CStore();
	~CStore();

private:
	class CItem* mItem[3] = {};
	EStoreType::Type	mType;

public:
	bool Init(EStoreType::Type Type);
	void Run();
};

