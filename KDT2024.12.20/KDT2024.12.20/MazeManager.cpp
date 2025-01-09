#include "MazeManager.h"
#include "Maze.h"

DEFINITION_SINGLE(CMazeManager)

CMazeManager::CMazeManager()
{
}

CMazeManager::~CMazeManager()
{
	if (nullptr != mMazeArray)
	{
		for (int i = 0; i < mMazeCount; ++i)
		{
			SAFE_DELETE(mMazeArray[i]);
		}

		delete[] mMazeArray;
	}
}

int CMazeManager::Menu()
{
	system("cls");

	for (int i = 0; i < mMazeCount; ++i)
	{
		std::cout << i + 1 << ". " <<
			mMazeArray[i]->GetName() << std::endl;
	}

	std::cout << mMazeCount + 1 << ". �ڷΰ���" << std::endl;
	std::cout << "�̷θ� �����ϼ��� : ";
	int	Input;
	std::cin >> Input;

	if (Input < 1 || Input > mMazeCount + 1)
		return 0;

	return Input;
}

bool CMazeManager::Init()
{
	// �̷� ��� ������ �о�´�.
	FILE* File = nullptr;

	fopen_s(&File, "MazeList.txt", "rt");

	if (!File)
		return false;

	char	Line[128] = {};

	fgets(Line, 128, File);

	// ���� �� ��� �ִ��� txt�� �ִ� ���ڷ� Ȯ��.
	mMazeCount = atoi(Line);
	mMazeArray = new CMaze * [mMazeCount];

	// �� �� ������ŭ �ݺ�
	for (int i = 0; i < mMazeCount; ++i)
	{
		fgets(Line, 128, File);

		int	Length = strlen(Line);

		if (Line[Length - 1] == '\n')
			Line[Length - 1] = 0;

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
		int	Input = Menu();

		if (Input == 0)
			continue;

		else if (Input == mMazeCount + 1)
			break;

		int	Index = Input - 1;

		mMazeArray[Index]->Run();

		// �̷� �Ϸ��ϴµ� �ɸ� �ð��� ���´�.
		__int64	Time = mMazeArray[Index]->GetTime();
		int	Score = mMazeArray[Index]->GetScore();

		int	ScoreIndex = -1;

		if (mScoreCount == 0)
			ScoreIndex = 0;

		else
		{
			for (int i = 0; i < mScoreCount; ++i)
			{
				// Time���� ū���� ���� ���
				// ScoreIndex�� -1�� ������ ���̴�.
				if (mScoreArray[i].Time > Time)
				{
					ScoreIndex = i;
					break;
				}
			}

			// for���� ū �ð��� ���ٸ�
			if (ScoreIndex == -1)
			{
				ScoreIndex = mScoreCount;

				if (ScoreIndex >= 5)
					ScoreIndex = -1;
			}
		}

		if (ScoreIndex != -1)
		{
			// ���� ������ �� �ε�������
			// ���� �������� 1ĭ�� �о��ش�.
			for (int i = mScoreCount - 1; i >= ScoreIndex; --i)
			{
				if (i == 4)
					break;

				mScoreArray[i + 1] = mScoreArray[i];
			}

			mScoreArray[ScoreIndex].Time = Time;
			mScoreArray[ScoreIndex].Score = Score;
			++mScoreCount;

			if (mScoreCount > 5)
				mScoreCount = 5;
		}
	}
}

void CMazeManager::RunScore()
{
	// ������ �����ش�.
	system("cls");
	std::cout << "�ð�\t����" << std::endl;

	for (int i = 0; i < mScoreCount; ++i)
	{
		__int64 Minute = mScoreArray[i].Time / 60;
		__int64 Second = mScoreArray[i].Time % 60;

		std::cout << Minute << ":" << Second << "\t" <<
			mScoreArray[i].Score << std::endl;
	}

	system("pause");
}
