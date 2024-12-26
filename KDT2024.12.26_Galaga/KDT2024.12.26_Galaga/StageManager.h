#pragma once
#include "Stage.h"

class CStageManager
{
private:
	//std::vector<CStage*> mVectorStage;		// Stage�� ����������Ÿ� �̷�������
	CStage* mStage = nullptr;		// ������ �׶� �׶� ���ִ� ���.
	std::vector<std::string> mVectorFileName;
	std::vector<std::string> mVectorName;
	int mCount = 0;

public:
	bool Init();
	void Run();

	DECLARE_SINGLE(CStageManager)
};

