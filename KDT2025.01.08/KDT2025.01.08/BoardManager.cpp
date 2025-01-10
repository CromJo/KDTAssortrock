#include "BoardManager.h"
#include "ObjectManager.h"

CBoardManager* CBoardManager::Instance = nullptr;

bool CBoardManager::Init(char* FileName)
{
	char* Line = FileName;

	char* Context = nullptr;
	char* Result = strtok_s(Line, ", ", &Context);

	mMapSizeX = atoi(Result);		// 15
	mMapSizeY = atoi(Context);		// 20

	mMapCollisionType = new ECollisionType * [mMapSizeX];

	mOutputBuffer = new char[(mMapSizeX + 1) * mMapSizeY + 1];
	
	memset(mOutputBuffer, 0, sizeof(char) * ((mMapSizeX + 1) * mMapSizeY + 1));

	// 양쪽 벽으로 막고 블록이 다닐 수 있는 경로로 싹다 초기화 시킴.
	for (int i = 0; i < mMapSizeY; i++)
	{
		mMapCollisionType[i] = new ECollisionType[mMapSizeX];

		for (int j = 0; j < mMapSizeX; j++)
		{
			// 맨위 상단이거나, 맨왼쪽이거나, 맨아래거나, 맨오른쪽이라면 
			if (i == 0 || 
				j == 0 || 
				i == mMapSizeX || 
				j == mMapSizeY)
			{
				// 블록이 다닐 수 있는 Road(0)로 초기화. 
				mMapCollisionType[i][j] = ECollisionType::Road;
			}
		}
	}

	return true;
}

bool CBoardManager::FileRead(const char* FileName)
{
	return false;
}

// 실시간 보드판 그리기
void CBoardManager::Run()
{
	while(true)
	{
		system("cls");

		COORD Start = {};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Start);

		for (int i = 0; i < mMapSizeX; i++)
		{
			for (int j = 0; j < mMapSizeX; j++)
			{
				int Index = i * (mMapSizeX + 1) + j;

				// 맨위 상단이거나, 맨왼쪽이거나, 맨아래거나, 맨오른쪽이라면 
				if (i == 0 ||
					j == 0 ||
					i == mMapSizeX ||
					j == mMapSizeY)
				{
					mOutputBuffer[Index] = '@';
				}
				else
				{
					mOutputBuffer[Index] = ' ';
				}
			}

			mOutputBuffer[i * (mMapSizeY + 1) + mMapSizeX] = '\n';
		}
		
		CObject
	}
}
