#pragma once

static class CGameManager
{
private:
	CGameManager();
	~CGameManager();

private:
	static CGameManager* Instance;

public:
	static CGameManager* GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new CGameManager;
		}

		return Instance;
	}

	static void DestroyInstance()
	{
		if (Instance)
		{
			delete Instance;
			Instance = nullptr;
		}
	}
};

