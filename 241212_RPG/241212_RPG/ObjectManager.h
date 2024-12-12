#pragma once

#include "GameInfo.h"
#include "Player.h"
#include "Monster.h"


class CObjectManager
{
private:
	CObjectManager();
	~CObjectManager();

private:
	CPlayer* mPlayer = nullptr;
	CMonster* mMonster[(int)EBattleType::End] = {};
	// 전방선언으로 포인터 변수를 선언한다.
	class CItem* mItem[EItemType::End][3];

public:
	CPlayer* GetPlayer()
	{
		return mPlayer;
	}

public:
	bool Init();
	CMonster* CreateMonster(EBattleType Type);
	CItem* GetItem(EItemType::Type Type, int Index)
	{
		return mItem[Type][Index];
	}

private:
	bool LoadMonster();
	bool LoadItem();

private:
	static CObjectManager* mInst;

public:
	static CObjectManager* GetInst()
	{
		if (nullptr == mInst)
			mInst = new CObjectManager;
		return mInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};

