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

	// ������ ������ �Ǵ����ִ� �Լ�.
	// ������ ���� �����ϸ� 0�� �ƴ� ���� ��ȯ
	// ���� ���� �ƴϸ� 0�� ��ȯ
	while (!feof(File))
	{
		char Line[128] = {};
		fgets(Line, 128, File);

		// ������ �и�
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

	// ������ ���ػ� Ÿ�̸Ӱ� 1�ʴ� ���� �帣���� ���´�.
	QueryPerformanceFrequency(&mSecond);

	return true;
}

void CStage::Run()
{
	system("cls");

	// (���� �� -  ������) / �ʴ簪 = �帥�ð� 
	QueryPerformanceCounter(&mTime);

	mStageTime = 0;

	// ���� ������ ���ػ� Ÿ�̸� ���� �޾ƿ´�.
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
					std::cout << "��";
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
		// ����Ʈ�� �ִ� ù��° ��Ҹ� �����´�.
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
