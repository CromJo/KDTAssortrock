#pragma once
#include "Stage.h"


class CStageManager
{
private:
	CStage* mStage = nullptr;
	std::vector<std::string>	mvecFileName;
	std::vector<std::string>	mvecName;
	int		mCount = 0;

public:
	CStage* GetStage()
	{
		return mStage;
	}
	
	std::vector<std::string> GetVectorFileName()
	{
		return mvecFileName;
	}

public:
	bool Init();
	void Run();

	DECLARE_SINGLE(CStageManager)
};

