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

	// ���� ������ ���� ����� �ٴ� �� �ִ� ��η� �ϴ� �ʱ�ȭ ��Ŵ.
	for (int i = 0; i < mMapSizeY; i++)
	{
		mMapCollisionType[i] = new ECollisionType[mMapSizeX];

		for (int j = 0; j < mMapSizeX; j++)
		{
			// ���� ����̰ų�, �ǿ����̰ų�, �ǾƷ��ų�, �ǿ������̶�� 
			if (i == 0 || 
				j == 0 || 
				i == mMapSizeX || 
				j == mMapSizeY)
			{
				// ����� �ٴ� �� �ִ� Road(0)�� �ʱ�ȭ. 
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

// �ǽð� ������ �׸���
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

				// ���� ����̰ų�, �ǿ����̰ų�, �ǾƷ��ų�, �ǿ������̶�� 
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
