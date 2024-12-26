#include "Stage.h"
#include "ObjectManager.h"
#include "Enemy.h"
#include "Player.h"

CStage::CStage()
{
}

CStage::~CStage()
{
}

bool CStage::Init(const char* FileName)
{
	FILE* File = nullptr;

	fopen_s(&File, FileName, "rt");

	if (!File)
		return false;

	// 파일의 끝인지 판단해주는 함수.
	// 파일의 끝에 도달하면 0이 아닌 값을 반환
	// 파일 끝이 아니면 0을 반환
	while (!feof(File))
	{
		char Line[128] = {};
		fgets(Line, 128, File);

		// 데이터 분리
		char* Context = nullptr;
		char* Result = strtok_s(Line, ", ", &Context);
		FStageInfo Info;
		Info.Time = atoi(Result);

		Result = strtok_s(nullptr, ", ", &Context);
		Info.Type = (EObjectType)atoi(Result);
		
		Result = strtok_s(nullptr, ", ", &Context);
		Info.X = atoi(Result);

		Result = strtok_s(nullptr, ", ", &Context);
		Info.Y = atoi(Result);

		Info.Direct = (ESpawnDirect)atoi(Context);
		mInfoList.emplace_back(Info);
	}

	fclose(File);

	// 윈도우 고해상도 타이머가 1초당 몇이 흐르는지 얻어온다.
	QueryPerformanceFrequency(&mSecond);

	return true;
}

void CStage::Run()
{
	system("cls");

	// (현재 값 -  이전값) / 초당값 = 흐른시간 
	QueryPerformanceCounter(&mTime);

	mStageTime = 0;

	// 현재 윈도우 고해상도 타이머 값을 받아온다.
	QueryPerformanceCounter(&mTime);

	while (true)
	{
		LARGE_INTEGER Time;
		QueryPerformanceCounter(&Time);

		mDeltaTime = (Time.QuadPart - mTime.QuadPart) / (float)mSecond.QuadPart;
		mStageTime += mDeltaTime;

		mTime = Time;

		ComputeStageInfo();

		CObjectManager::GetInst()->Update(mDeltaTime);

		COORD Start = {};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Start);

		for (int i = 0; i < mCountY; i++)
		{
			for (int j = 0; j < mCountX; j++)
			{
				if (i == 0 ||
					j == 0 ||
					i == mCountY - 1 ||
					j == mCountX - 1)
				{
					std::cout << "■";
				}
				else
				{
					std::cout << " ";
				}
			}
			std::cout << std::endl;
		}

		//CObjectManager::GetInst()->Update(mDeltaTime);
		CObjectManager::GetInst()->Output();

	}
}

void CStage::ComputeStageInfo()
{
	if (!mInfoList.empty())
	{
		// 리스트에 있는 첫번째 요소를 가져온다.
		const FStageInfo& Info = mInfoList.front();

		if (mStageTime >= Info.Time)
		{
			CEnemy* Enemy = nullptr;

			switch (Info.Type)
			{
			case EObjectType::EnemyEasy:
				Enemy = CObjectManager::GetInst()->CreateObj<CEnemy>();
				break;
			case EObjectType::EnemyNormal:
				Enemy = CObjectManager::GetInst()->CreateObj<CEnemy>();
				break;
			case EObjectType::EnemyHard:
				Enemy = CObjectManager::GetInst()->CreateObj<CEnemy>();
				break;
			case EObjectType::Boss:
				Enemy = CObjectManager::GetInst()->CreateObj<CEnemy>();
				break;
			}

			Enemy->SetPos(Info.X, Info.Y);
			mInfoList.pop_front();
		}
	}
}
