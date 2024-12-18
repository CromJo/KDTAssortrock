#include "MazeManager.h"
#include "Maze.h"

DEFINITION_SINGLE(CMazeManager)

CMazeManager::CMazeManager()
{
}

CMazeManager::~CMazeManager()
{
	// 동적 배열할당을 했으니 필요없는 소멸자는 딜리트부터 하고 시작하는겨
	if (nullptr != mMazeArray)
	{
		for (int i = 0; i < mMazeCount; i++)
		{
			SAFE_DELETE(mMazeArray);
		}
		delete[] mMazeArray;
	}
}

bool CMazeManager::Init()
{
	// 미로 목록 파일을 읽어온다.
	FILE* File = nullptr;

	fopen_s(&File, "MazeList.txt", "rt");

	if (!File)
		return false;

	char Line[128] = {};

	fgets(Line, 128, File);

	mMazeCount = atoi(Line);
	mMazeArray = new CMaze * [mMazeCount];

	for (int i = 0; i < mMazeCount; i++)
	{
		fgets(Line, 128, File);
		// 문자열의 길이를 구하는 함수
		int Length = strlen(Line);

		if (Line[Length - 1] == '\n')
		{
			Line[Length - 1] = 0;
		}

		mMazeArray[i] = new CMaze;
		mMazeArray[i]->Init(Line);
	}

	fclose(File);
	
	return true;
}

void CMazeManager::Run()
{
	mMazeArray[0]->Output();
}
