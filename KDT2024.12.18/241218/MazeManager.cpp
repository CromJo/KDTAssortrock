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

		if (mScoreCount < 5)
		{
			mScoreArray[mScoreCount] = Time;
			int ArrCount = 5;
			
			for (int i = 0; i < ArrCount; i++)
			{
				for (int j = i + 1; j < ArrCount; j++)
				{
					// 만약 i 숫자가 i+1보다 더 크다면 값 바꾸기
					if (mScoreArray[i] > mScoreArray[j])
					{
						int Temp = mScoreArray[i];	// 위치 바꿀때 쓸 변수.
						mScoreArray[i] = mScoreArray[i + 1];
						mScoreArray[i + 1] = Temp;
					}
				}
			}

			// 시간을 넣어주고 시간을 작은 시간에서
			// 큰 시간 순서로 정렬해야 한다.
		}

		else
		{
			// 5개의 시간중 가장 큰 시간을 얻어와서
			// 그 시간보다 현재 걸린 시간이 더 작다면
			// 교체해준다.

			// 5개의 시간을 반복하며 현재 걸린 시간과 비교
			// 하여 현재 걸린시간이 더 작으면 한칸씩 뒤로
			// 밀고 그 자리에 현재 시간을 넣어준다.
		}
		
	}

}

void CMazeManager::RunScore()
{
	//system("pause");

	// 2. 점수

}
