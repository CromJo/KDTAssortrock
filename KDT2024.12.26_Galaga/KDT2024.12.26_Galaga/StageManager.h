#pragma once
#include "Stage.h"

class CStageManager
{
private:
	//std::vector<CStage*> mVectorStage;		// Stage를 여러개만들거면 이런식으로
	CStage* mStage = nullptr;		// 생성을 그때 그때 해주는 방식.
	std::vector<std::string> mVectorFileName;
	std::vector<std::string> mVectorName;
	int mCount = 0;

public:
	CStage* GetStage()
	{
		return mStage;
	}

public:
	bool Init();
	void Run();

	DECLARE_SINGLE(CStageManager)
};

