#pragma once
#include "GameInfo.h"
#include "Player.h"
#include "AI.h"

class CGameManager
{
private:
	CGameManager();				// 헤더에선 선언만
	~CGameManager();

private:
	CPlayer* mPlayer = nullptr;
	CAI* mAI = nullptr;

public:
	bool Init();
	void Run();

private:
	static CGameManager* mInstance;

public:
	static CGameManager* GetInstance()
	{
		if (nullptr == mInstance)
			mInstance = new CGameManager;
		return mInstance;
	}

	static void DestroyInstance()
	{
		SAFE_DELETE(mInstance);
	}
};

