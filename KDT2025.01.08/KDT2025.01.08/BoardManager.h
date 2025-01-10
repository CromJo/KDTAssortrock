#pragma once
#include "GameInfo.h"

class CBoardManager
{
private:
	CBoardManager() {}
	~CBoardManager() {}

private:
	static CBoardManager* Instance;

public:
	static CBoardManager* GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new CBoardManager;
		}

		return Instance;
	}

	static void DestroyInstance()
	{
		SAFE_DELETE(Instance);
	}

private:
	CBoardManager* mTetris = nullptr;

	ECollisionType** mMapCollisionType = nullptr;
	char* mOutputBuffer;
	int mMapSizeX = 0;
	int mMapSizeY = 0;

public:
	bool Init(char* FileName);
	bool FileRead(const char* FileName);
	void Run();

	COORD mBoard;
};

