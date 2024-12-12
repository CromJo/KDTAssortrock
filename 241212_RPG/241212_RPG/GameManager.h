#pragma once

#include "GameInfo.h"
#include "BattleManager.h"

namespace EMainMenu
{
	enum Type
	{
		None,
		Battle,
		Store,
		Inventory,
		Exit
	};
}

/*
	전방선언 : 어딘가에 지정하는 타입의 클래스가 있다라는
			약속을 하고 포인터 변수를 선언할 수 있게
			해주는 기능이다.
			  실제 사용부분에서 include를 한다.
*/
class CStoreManager;
class CGameManager
{
private:
	CGameManager();
	~CGameManager();

private:
	CBattleManager* mBattleMgr = nullptr;
	CStoreManager* mStoreMgr = nullptr;

public:
	bool Init();
	void Run();

private:
	EMainMenu::Type Menu();

private:
	static CGameManager* mInst;

public:
	static CGameManager* GetInst()
	{
		if (nullptr == mInst)
			mInst = new CGameManager;
		return mInst;
	}

	static void DestroyInst()
	{
		SAFE_DELETE(mInst);
	}
};

