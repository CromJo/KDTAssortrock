﻿#include "MazeManager.h"
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
			SAFE_DELETE(mMazeArray[i]);
		}
		delete[] mMazeArray;
	}
}

int CMazeManager::Menu()
{
	system("cls");

	for (int i = 0; i < mMazeCount; i++)
	{
		std::cout << i + 1 << ". " << mMazeArray[i]->GetName() << std::endl;
	}

	std::cout << mMazeCount + 1 << ". 뒤로가기" << std::endl;
	std::cout << "미로를 선택하세요. : ";

	int Input;
	std::cin >> Input;

	if (Input < 1 || Input > mMazeCount + 1)
		return 0;

	return Input;
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
	while (true)
	{
		int Input = Menu();

		if (Input == 0)
			continue;
		else if (Input == mMazeCount + 1)
			break;

		int Index = Input - 1;

		mMazeArray[Index]->Run();

		__int64 Time = mMazeArray[Index]->GetTime();
		int Score = mMazeArray[Index]->GetScore();

		int ScoreIndex = -1;

		if (mScoreCount == 0)
		{
			ScoreIndex = 0;
		}
		else
		{
			for (int i = 0; i < mScoreCount; i++)
			{
				// Time보다 큰값이 없을경우
				// 돌아가지 못하도록
				if (mScoreArray[i].Time > Time)
				{
					ScoreIndex = i;
					break;
				}
			}

			if (ScoreIndex == -1)
			{
				ScoreIndex = mScoreCount;

				if (ScoreIndex >= 5)
				{
					ScoreIndex = -1;
				}
			}

		}

		if (ScoreIndex != -1)
		{
			// 현재 점수가 들어갈 인덱스부터 
			// 뒤의 점수들을 1칸씩 밀어준다.
			for (int i = mScoreCount - 1; i >= ScoreIndex ; i--)
			{
				if (i == 4)
					break;

				mScoreArray[i + 1] = mScoreArray[i];
			}
			
			mScoreArray[ScoreIndex].Time = Time;
			mScoreArray[ScoreIndex].Score = Score;
			mScoreCount++;

			if (mScoreCount > 5)
			{
				mScoreCount = 5;
			}
		}
	}
}

void CMazeManager::RunScore()
{
	// 2. 점수
	std::cout << "시간\t점수" << std::endl;

	for (int i = 0; i < mScoreCount; i++)
	{
		__int64 Minute = mScoreArray[i].Time / 60;
		__int64 Second = mScoreArray[i].Time % 60;

		std::cout << Minute << " : " << Second << std::endl;
	}
	


	system("pause");
}
