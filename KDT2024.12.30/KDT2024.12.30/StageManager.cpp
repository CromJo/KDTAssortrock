#include "StageManager.h"

DEFINITION_SINGLE(CStageManager)

CStageManager::CStageManager()
{
}

CStageManager::~CStageManager()
{
}

bool CStageManager::Init()
{
	FILE* File = nullptr;

	fopen_s(&File, "Stage.txt", "rt");

	if (!File)
		return false;

	char	Line[128] = {};

	fgets(Line, 128, File);

	mCount = atoi(Line);

	//mvecFileName.reserve(mCount);
	mvecFileName.resize(mCount);
	mvecName.resize(mCount);

	for (int i = 0; i < mCount; ++i)
	{
		fgets(Line, 128, File);

		int	Length = (int)strlen(Line);

		if (Line[Length - 1] == '\n')
			Line[Length - 1] = 0;

		//mvecFileName.emplace_back(Line);
		mvecFileName[i] = Line;

		char* Context = nullptr;
		mvecName[i] = strtok_s(Line, ".", &Context);
	}

	fclose(File);

	return true;
}

void CStageManager::Run()
{
	mStage = nullptr;

	while (true)
	{
		system("cls");
		mStage = new CStage;

		mStage->Init("Stage.txt");
		mStage->Run();
	}

	SAFE_DELETE(mStage);
}
