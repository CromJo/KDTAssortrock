#pragma once
#include "GameInfo.h"

class CObjectManager
{
private:
	class CObject* mObjectList[10];
	class CPlayer* mPlayer = nullptr;
	int mObjectCount = 0;

public:
	class CObject* GetObject(int Index)
	{
		return mObjectList[Index];
	}

public:
	bool Init();
	void Output();
	void Run();
	void CreateMonsterList();
	void CreateItemList();

	DECLARE_SINGLE(CObjectManager);
};

