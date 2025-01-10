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
    if (nullptr != mMazeArray)
    {
        for (int i = 0; i < mCountY; ++i)
        {
            delete[] mMazeArray[i];
        }

        delete[] mMazeArray;
    }

    if (nullptr != mOutputBuffer)
        delete[] mOutputBuffer;
}

/// <summary>
/// 파일을 읽는 기능 (없으면 생성)
/// </summary>
/// <param name="FileName"></param>
/// <returns></returns>
bool CMaze::FileRead(const char* FileName)
{
    FILE* File = nullptr;

    fopen_s(&File, FileName, "rt");

    if (!File)
        return false;

    char    Buffer[128] = {};

    strcpy_s(Buffer, FileName);

    char* Context = nullptr;

    char* Result = strtok_s(Buffer, ".", &Context);

    strcpy_s(mName, Result);

    char    Line[128] = {};

    fgets(Line, 128, File);

    Result = strtok_s(Line, ", ", &Context);

    mCountX = atoi(Result);
    mCountY = atoi(Context);

    mMazeArray = new ETileType * [mCountY];

    // 마지막이 널문자가 되어야 하기 때문에 1개를 더
    // 생성한다.
    mOutputBuffer = new char[(mCountX + 1) * mCountY + 1];

    memset(mOutputBuffer, 0,
        sizeof(char) * ((mCountX + 1) * mCountY + 1));

    for (int i = 0; i < mCountY; ++i)
    {
        mMazeArray[i] = new ETileType[mCountX];

        fgets(Line, 128, File);

        for (int j = 0; j < mCountX; ++j)
        {
            char    Number[2] = {};
            Number[0] = Line[j];
            mMazeArray[i][j] = (ETileType)atoi(Number);
        }
    }

    fclose(File);

    return true;
}

bool CMaze::Init(const char* FileName)
{
    // 생성된 아이템, 함정등을 저장하기 위한 오브젝트
    // 배열을 만들어준다.
    mObjectList = new CObject * [mObjectCapacity];

    return FileRead(FileName);
}

void CMaze::Reset()
{
    // 이전 플레이에 남아있던 오브젝트들을 제거한다.
    for (int i = 0; i < mObjectCount; ++i)
    {
        SAFE_DELETE(mObjectList[i]);
    }

    mObjectCount = 0;

    mTime = 0;
    mScore = 0;

    memset(mOutputBuffer, 0,
        sizeof(char) * ((mCountX + 1) * mCountY + 1));

    for (int i = 0; i < mCountY; ++i)
    {
        for (int j = 0; j < mCountX; ++j)
        {
            int OutIndex = i * (mCountX + 1) + j;

            switch (mMazeArray[i][j])
            {
            case ETileType::Road:
                SetOutputBuffer(OutIndex, ' ');
                //mOutputBuffer[OutIndex] = ' ';
                break;
            case ETileType::Wall:
                SetOutputBuffer(OutIndex, '@');
                //mOutputBuffer[OutIndex] = '@';
                break;
            case ETileType::Start:
                SetStartPosition(j, i);
                SetOutputBuffer(OutIndex, '#');
                //mOutputBuffer[OutIndex] = '#';
                break;
            case ETileType::Goal:
                SetGoalPosition(j, i);
                SetOutputBuffer(OutIndex, '%');
                //mOutputBuffer[OutIndex] = '%';
                break;
            case ETileType::Item:
            {
                // 아이템을 생성한다.
                CItem* Item = new CItemScore;

                Item->Init();
                Item->SetPos(j, i);

                if (mObjectCount == mObjectCapacity)
                {
                    mObjectCapacity *= 2;

                    CObject** Array = new CObject * [mObjectCapacity];

                    memcpy(Array, mObjectList,
                        sizeof(CObject*) * mObjectCount);

                    delete[] mObjectList;

                    mObjectList = Array;
                }

                mObjectList[mObjectCount] =
                    Item;
                ++mObjectCount;

                mOutputBuffer[OutIndex] = ' ';
            }
            break;
            case ETileType::Trap:
            {
                // 아이템을 생성한다.
                CTrap* Trap = new CTrap;

                Trap->Init();
                Trap->SetPos(j, i);
                
                AddObject(Trap);

                mObjectList[mObjectCount] = Trap;
                ++mObjectCount;

                mOutputBuffer[OutIndex] = ' ';
            }
            break;
            case ETileType::HP:
            {
                // 아이템을 생성한다.
                CItem* Item = new CItemHP;

                Item->Init();
                Item->SetPos(j, i);

                AddObject(Item);

                mObjectList[mObjectCount] =
                    Item;
                ++mObjectCount;

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

    int StartIndex = mStartPos.Y * (mCountX + 1) +
        mStartPos.X;

    mPrevPlayerIndex = StartIndex;
    mPrevPlayerOutput = 0;

    int GoalIndex = mGoalPos.Y * (mCountX + 1) +
        mGoalPos.X;

    while (true)
    {
        Update(Player);

        Output();

        std::cout << mOutputBuffer;


        if (GetTile(Player->GetPos().X, Player->GetPos().Y) ==
            ETileType::Goal)
            break;


        __int64 Time = time(0);

        mTime = Time - TimeStart;

        COORD   TimePos;
        TimePos.X = mCountX + 2;
        TimePos.Y = 2;

        SetConsoleCursorPosition(
            GetStdHandle(STD_OUTPUT_HANDLE),
            TimePos);

        __int64 Minute = mTime / 60;
        __int64 Second = mTime % 60;

        std::cout << Minute << ":" << Second << std::endl;

        COORD   ScorePos;
        ScorePos.X = mCountX + 2;
        ScorePos.Y = 3;

        SetConsoleCursorPosition(
            GetStdHandle(STD_OUTPUT_HANDLE),
            ScorePos);
        std::cout << "Score : " << mScore;

        COORD   HPPos;
        HPPos.X = mCountX + 2;
        HPPos.Y = 1;

        SetConsoleCursorPosition(
            GetStdHandle(STD_OUTPUT_HANDLE),
            HPPos);
        std::cout << "HP : ";

        int HP = Player->GetHP();

        for (int i = 0; i < 5; ++i)
        {
            if (i < HP)
                std::cout << "♥";

            else
                std::cout << "  ";
        }
    }

    SAFE_DELETE(Player);
}

void CMaze::Output(CPlayer* Player)
{
    COORD   PlayerPos = Player->GetPos();

    int PlayerIndex = PlayerPos.Y * (mCountX + 1) +
        PlayerPos.X;

    // 시작과 도착 지점의 출력을 다시 저장한다.
    mOutputBuffer[StartIndex] = '#';
    mOutputBuffer[GoalIndex] = '%';

    // 아이템을 먼저 출력해준다.
    for (int i = 0; i < mObjectCount; ++i)
    {
        mObjectList[i]->Output(mOutputBuffer,
            mCountX + 1);
    }

    // 플레이어의 이전 프레임 인덱스를 원래대로
    // 되돌려놓는다.
    if (mPrevPlayerOutput != 0)
    {
        mOutputBuffer[mPrevPlayerIndex] =
            mPrevPlayerOutput;
    }

    mPrevPlayerIndex = PlayerIndex;
    mPrevPlayerOutput = mOutputBuffer[PlayerIndex];

    mOutputBuffer[PlayerIndex] = '$';

    // 콘솔 커서의 위치를 처음으로 돌려준다.
    COORD   Cursor = {};
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), Cursor);
}

void CMaze::AddObject(CObject* Obj)
{
    if (mObjectCount == mObjectCapacity)
    {
        mObjectCapacity *= 2;

        CObject** Array = new CObject * [mObjectCapacity];

        memcpy(Array, mObjectList,
            sizeof(CObject*) * mObjectCount);

        delete[] mObjectList;

        mObjectList = Array;
    }
}

void CMaze::Update(class CPlayer* Player)
{
    Player->Update();

    for (int i = 0; i < mObjectCount; ++i)
    {
        mObjectList[i]->Update();
    }

    COORD   PlayerPos = Player->GetPos();

    int PlayerIndex = PlayerPos.Y * (mCountX + 1) +
        PlayerPos.X;


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
                    mScore++;
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

}
