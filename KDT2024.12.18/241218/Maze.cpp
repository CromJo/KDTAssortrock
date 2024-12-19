#include "Maze.h"
#include "Player.h"
#include "Item.h"

CMaze::CMaze()
{
}

CMaze::~CMaze()
{
	if (nullptr != mMazeArray)
	{
		for (int i = 0; i < mCountY; i++)
		{
			delete[] mMazeArray[i];
		}

		delete[] mMazeArray;
	}

	if (nullptr != mOutputBuffer)
	{
		delete[] mOutputBuffer;
	}
}

bool CMaze::Init(const char* FileName)
{
	// 생성된 아이템, 함정등을 저장하기 위한 오브젝트 배열을 만들어준다.
	mObjectList = new CObject * [mObjectCapacity];

	FILE* File = nullptr;

	fopen_s(&File, FileName, "rt");

	if (!File)
		return false;

	char Buffer[128] = {};
	strcpy_s(Buffer, FileName);

	char* Context = nullptr;
	//char* Result = strtok_s(Line, ", ", &Context);
	char* Result = strtok_s(Buffer, ".", &Context);
	strcpy_s(mName, Result);

	char Line[128] = {};
	fgets(Line, 128, File);

	Result = strtok_s(Line, ", ", &Context);

	mCountX = atoi(Result);
	mCountY = atoi(Context);

	mMazeArray = new ETileType* [mCountY];
	// 마지막에는 Null문자가 들어와야 하기 때문에 1개를 더 생성해줘야 한다.
	mOutputBuffer = new char[(mCountX + 1) * mCountY + 1];

	memset(mOutputBuffer, 0, sizeof(char) * ((mCountX + 1) * mCountY + 1));

	for (int i = 0; i < mCountY; i++)
	{
		mMazeArray[i] = new ETileType[mCountX];

		fgets(Line, 128, File);

		for (int j = 0; j < mCountX; j++)
		{
			char Number[2] = {};
			Number[0] = Line[j];
			//이거는 atoi(const char* c)
			//-->const char* 
			//Line[j]주소 -----> Line[xCountX -1]
			//이거를 --> 숫자로 형변환 한거에요.
			mMazeArray[i][j] = (ETileType)atoi(Number);

			int OutIndex = i * (mCountX + 1) + j;

			switch (mMazeArray[i][j])
			{
			case ETileType::Road:
				mOutputBuffer[OutIndex] = ' ';
				break;
			case ETileType::Wall:
				mOutputBuffer[OutIndex] = 'O';
				break;
			case ETileType::Start:
				mStartPos.X = j;
				mStartPos.Y = i;
				mOutputBuffer[OutIndex] = 'S';
				break;
			case ETileType::Goal:
				mGoalPos.X = j;
				mGoalPos.Y = i;
				mOutputBuffer[OutIndex] = 'F';
				break;
			case ETileType::Item:
				CItem* Item = new CItem;
				
				Item->Init();
				Item->SetPos(j, i);

				if (mObjectCount == mObjectCapacity)
				{
					mObjectCapacity *= 2;

					CObject** Array = new CObject * [mObjectCapacity];
					
					memcpy(Array, mObjectList, sizeof(CObject*) * mObjectCount);
				
					delete[] mObjectList;

					mObjectList = Array;
				}

				mObjectList[mObjectCount] = Item;
				mObjectCount++;

				mOutputBuffer[OutIndex] = ' ';
				break;
			}
		}

		// 한줄이 끝나면 개행문자를 넣어둔다.
		// 가로의 끝 인덱스는 (mCountX + 1) 개만큼 이기
		// 때문에 mCountX가 가로의 끝 인덱스가 된다.
		int OutIndex = i * (mCountX + 1) + mCountX;
		mOutputBuffer[OutIndex] = '\n';
	}

	fclose(File);

	return true;
}

void CMaze::Run()
{
	system("cls");

	__int64 TimeStart = time(0);

	// 플레이어 생성
	CPlayer* Player = new CPlayer;

	Player->Init();
	Player->SetPos(mStartPos);
	Player->SetMaze(this);

	int StartIndex = mStartPos.Y * (mCountX + 1) + mStartPos.Y;
	int GoalIndex = mGoalPos.Y * (mCountX + 1) + mGoalPos.X;
	
	mPrevPlayerIndex = StartIndex;
	mPrevPlayerOutput = 0;

	while (true)
	{
		Player->Update();

		for (int i = 0; i < mObjectCount; i++)
		{
			mObjectList[i]->Update();
		}

		COORD PlayerPos = Player->GetPos();
		int PlayerIndex = PlayerPos.Y * (mCountX + 1) + PlayerPos.X;

		for (int i = 0; i < mObjectCount; i++)
		{
			// 아이템인지를 판단
			// 1. 오브젝트 종류를 열거형으로 체크
			// 2. 동적할당을 이용해서 판단

			// 동적할당 판단 기능
			CItem* Item = dynamic_cast<CItem*>(mObjectList[i]);
			
			if (nullptr != Item)
			{
				if (PlayerPos.X == Item->GetPos().X && PlayerPos.Y == Item->GetPos().Y)
				{
					mScore++;

					// 아이템을 먹게 되면 이전 출력은
					// 아이템이 아닌 길로 변경해야한다.
					mOutputBuffer[PlayerIndex] = ' ';

					if (i < mObjectCount - 1)
					{
						// 현재 위치의 아이템과 배열의 가장 마지막 오브젝트의 위치를 바꿔준다.
						CObject* Temp = mObjectList[i];
						mObjectList[i] = mObjectList[mObjectCount - 1];
						mObjectList[mObjectCount - 1] = Temp;
					}

					// 마지막 인덱스를 제거
					delete mObjectList[mObjectCount - 1];
					mObjectList[mObjectCount - 1] = nullptr;
					mObjectCount--;
				}
			}
		}

		mOutputBuffer[StartIndex] = '#';
		mOutputBuffer[GoalIndex] = '%';

		// 아이템 출력 기능
		for (int i = 0; i < mObjectCount; i++)
		{
			mObjectList[i]->Output(mOutputBuffer, mCountX + 1);
		}

		// 플레이어 이전 프레임 인덱스를 원래대로 되돌리는 기능
		if (mPrevPlayerOutput != 0)
		{
			mOutputBuffer[mPrevPlayerIndex] = mPrevPlayerOutput;
		}
		
		mPrevPlayerIndex = PlayerIndex;
		mPrevPlayerOutput = mOutputBuffer[PlayerIndex];

		mOutputBuffer[PlayerIndex] = '$';

		COORD Cursor = {};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cursor);

		// 미로 찾기 출력 기능
		Output();

		// 골대에 들어가면 종료
		if (GetTile(PlayerPos.X, PlayerPos.Y) == ETileType::Goal)
			break;

		__int64 Time = time(0);
		mTime = Time - TimeStart;

		COORD TimePos;
		TimePos.X = mCountX + 2;
		TimePos.Y = 1;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), TimePos);

		int Minute = mTime / 60;
		int Second = mTime % 60;

		std::cout << Minute << " : " << Second << std::endl;

		COORD ScorePos;
		ScorePos.X = mCountX + 2;
		ScorePos.Y = 2;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ScorePos);
		std::cout << "Score : " << mScore;
		//Player->Output();
	}

	SAFE_DELETE(Player);
}

void CMaze::Output()
{
	std::cout << mOutputBuffer;

	/*for (int i = 0; i < mCountY; i++)
	{
		for (int j = 0; j < mCountX; j++)
		{
			switch (mMazeArray[i][j])
			{
			case ETileType::Road:
				std::cout << " ";
				break;
			case ETileType::Wall:
				std::cout << "●";
				break;
			case ETileType::Start:
				std::cout << "◇";
			case ETileType::Goal:
				std::cout << "◆";
			}
		}

		std::cout << std::endl;
	}
	*/
}
