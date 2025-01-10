#pragma once
#include "GameInfo.h"

class CObjectManager
{
private:
	CObjectManager();
	~CObjectManager();

private:
	static CObjectManager* Instance;

public:
	static CObjectManager* GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new CObjectManager;
		}
		
		return Instance;
	}

	static void DestroyInstance()
	{
		SAFE_DELETE(Instance);
	}

public:
	bool Init();
	void Run();
	void Output(char* OutputBuffer);

	template <typename T>
	T* CreateObject()
	{

	}

};

