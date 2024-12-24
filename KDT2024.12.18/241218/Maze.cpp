#include "Maze.h"
#include "Player.h"
#include "ItemScore.h"
#include "ItemHP.h"
#include "Trap.h"

CMaze::CMaze()
{
}

CMaze::~CMaze()
{
	/*if (nullptr != mMazeArray)
	{
		for (int i = 0; i < mCountY; i++)
		{
			delete[] mMazeArray[i];
		}

		delete[] mMazeArray;
	}*/

	// clear함수가 불필요한 이유.
	// RAII패턴과 소멸자의 동작에 기반하기 때문.
	// RAII패턴 : 리소스의 수명을 객체의 수명과 연결.
	//	Vector의 경우 :
	//		1. 생성자 : 벡터 객체가 생성될 때 메모리를 할당합니다.
	//		2. 소멸자 : 벡터 객체가 소멸될 때 자동으로 호출되어 할당된 메모리를 해제.
	//mMazeVector.clear();
	
	if (nullptr != mOutputBuffer)
	{
		delete[] mOutputBuffer;
	}
}

bool CMaze::Init(const char* FileName)
{
	// 생성된 아이템, 함정등을 저장하기 위한 오브젝트 배열을 만들어준다.
	//mObjectList = new CObject * [mObjectCapacity];
	mObjectVectorList.resize(mObjectCapacity);		// 1차원 크기 설정.

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

	// vector.resize로 하면되니 필요없어질 듯?
	mCountX = atoi(Result);
	mCountY = atoi(Context);
	//mMazeArray = new ETileType* [mCountY];

	// 2차원 벡터 자동으로 원하는 크기 초기화.
	mMazeVector.resize(mCountY, std::vector<ETileType>(mCountX));	// 2차원 크기 설정
	
	// 마지막에는 Null문자가 들어와야 하기 때문에 1개를 더 생성해줘야 한다.
	mOutputBuffer = new char[(mCountX + 1) * mCountY + 1];

	memset(mOutputBuffer, 0, sizeof(char) * ((mCountX + 1) * mCountY + 1));

	/*for (int i = 0; i < mCountY; i++)
	{
		mMazeArray[i] = new ETileType[mCountX];
	
		fgets(Line, 128, File);
	
		for (int j = 0; j < mCountX; j++)
		{
			char Number[2] = {};
			Number[0] = Line[j];
			mMazeArray[i][j] = (ETileType)atoi(Number);
		}
		// 한줄이 끝나면 개행문자를 넣어둔다.
		// 가로의 끝 인덱스는 (mCountX + 1) 개만큼 이기
		// 때문에 mCountX가 가로의 끝 인덱스가 된다.
	}*/
	
	int Size = mMazeVector.size();

	for (int i = 0; i < Size; i++)
	{
		//mMazeArray[i] = new ETileType[mCountX];
		
		// 여기서 mMazeVector[i]의 resize를 추가 해줄 필요는 없다.
		// 왜냐하면 첫 resize일때 2차원적으로 재설정을 해주었기 때문.

		fgets(Line, 128, File);
		int Size2Vector = mMazeVector[i].size();	// 2차원 벡터의 사이즈
		for (int j = 0; j < Size2Vector; j++)
		{
			char Number[2] = {};
			Number[0] = Line[j];
			mMazeVector[i][j] = (ETileType)atoi(Number);
		}
	}

	fclose(File);

	return true;
}

void CMaze::Run()
{
	Reset();

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

		/*for (int i = 0; i < mObjectCount; i++)
		{
			mObjectList[i]->Update();
		}*/

		int mObjectVectorCount = mObjectVectorList.size();
		for (int i = 0; i < mObjectVectorCount; i++)
		{
			int mObjectVector2Count = mObjectVectorList[i].size();

			for (int j = 0; j < mObjectVector2Count; j++)
			{
				mObjectVectorList[i][j].Update();
			}
		}


		COORD PlayerPos = Player->GetPos();
		int PlayerIndex = PlayerPos.Y * (mCountX + 1) + PlayerPos.X;


		for (int i = 0; i < mObjectCount; ++i)
		{
			if (PlayerPos.X == mObjectList[i]->GetPos().X &&
				PlayerPos.Y == mObjectList[i]->GetPos().Y)
			{
				// 이 오브젝트가 아이템인지 판단한다.
				if (nullptr != dynamic_cast<CItem*>(mObjectList[i]))
				{
					if (dynamic_cast<CItemScore*>(mObjectList[i]))
					{
						// 점수인지 체력인지 판단한다.
						mScore += 10;
					}

					else
					{
						Player->AddHP(1);
					}

					// 아이템을 먹게되면 버퍼의 이 위치를
					// 길로 바꿔준다.
					mOutputBuffer[PlayerIndex] = ' ';

					// 가장 마지막 인덱스보다 작을 경우
					if (i < mObjectCount - 1)
					{
						// 현재 위치의 아이템과 배열의 가장
						// 마지막 오브젝트와 위치를 바꿔준다.
						CObject* Temp = mObjectList[i];
						mObjectList[i] = mObjectList[mObjectCount - 1];
						mObjectList[mObjectCount - 1] = Temp;
					}

					// 마지막 인덱스를 제거한다.
					delete mObjectList[mObjectCount - 1];
					mObjectList[mObjectCount - 1] = nullptr;
					--mObjectCount;
					break;
				}

				else if (nullptr != dynamic_cast<CTrap*>(mObjectList[i]))
				{
					mOutputBuffer[PlayerIndex] = ' ';
					if (Player->AddHP(-1))
					{
						SAFE_DELETE(Player);
						return;
					}

					// 가장 마지막 인덱스보다 작을 경우
					if (i < mObjectCount - 1)
					{
						// 현재 위치의 아이템과 배열의 가장
						// 마지막 오브젝트와 위치를 바꿔준다.
						CObject* Temp = mObjectList[i];
						mObjectList[i] = mObjectList[mObjectCount - 1];
						mObjectList[mObjectCount - 1] = Temp;
					}

					// 마지막 인덱스를 제거한다.
					delete mObjectList[mObjectCount - 1];
					mObjectList[mObjectCount - 1] = nullptr;
					--mObjectCount;
					break;
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

		__int64 Minute = mTime / 60;
		__int64 Second = mTime % 60;

		std::cout << Minute << " : " << Second << std::endl;

		COORD ScorePos;
		ScorePos.X = mCountX + 2;
		ScorePos.Y = 2;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ScorePos);
		std::cout << "Score : " << mScore;

		COORD HPPos;
		HPPos.X = mCountX + 2;
		HPPos.Y = 5;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), HPPos);
		std::cout << "HP : ";

		int HP = Player->GetHP();

		for (int i = 0; i < HP; i++)
		{
			if (i < HP)
			{
				std::cout << "♥";
			}
			else
			{
				std::cout << " ";
			}
		}
		//Player->Output();
	}

	SAFE_DELETE(Player);
}

void CMaze::Reset()
{
	// 이전 플레이에 남아있던 오브젝트들을 제거.
	for (int i = 0; i < mObjectCount; i++)
	{
		SAFE_DELETE(mObjectList[i]);
	}

	mObjectCount = 0;

	mTime = 0;
	mScore = 0;

	memset(mOutputBuffer, 0, sizeof(char) * ((mCountX + 1) * mCountY + 1));

	for (int i = 0; i < mCountY; i++)
	{
		for (int j = 0; j < mCountX; j++)
		{
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
			{
				CItem* Item = new CItemScore;

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
			}
				break;
			case ETileType::Trap:
			{
				CTrap* Trap = new CTrap;

				Trap->Init();
				Trap->SetPos(j, i);

				if (mObjectCount == mObjectCapacity)
				{
					mObjectCapacity *= 2;

					CObject** Array = new CObject * [mObjectCapacity];

					memcpy(Array, mObjectList, sizeof(CObject*) * mObjectCount);

					delete[] mObjectList;

					mObjectList = Array;
				}

				mObjectList[mObjectCount] = Trap;
				mObjectCount++;

				mOutputBuffer[OutIndex] = 'X';

			}
				break;
			case ETileType::HP:
			{
				CItem* Item = new CItemHP;

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
			}
				break;
			}
		}

		// 한줄이 끝나면 개행문자를 넣어둔다.
		// 가로의 끝 인덱스는 (mCountX + 1) 개만큼 이기
		// 때문에 mCountX가 가로의 끝 인덱스가 된다.
		int OutIndex = i * (mCountX + 1) + mCountX;
		mOutputBuffer[OutIndex] = '\n';
	}
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
				break;\
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
