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
/// ������ �д� ��� (������ ����)
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

    // �������� �ι��ڰ� �Ǿ�� �ϱ� ������ 1���� ��
    // �����Ѵ�.
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
    // ������ ������, �������� �����ϱ� ���� ������Ʈ
    // �迭�� ������ش�.
    mObjectList = new CObject * [mObjectCapacity];

    return FileRead(FileName);
}

void CMaze::Reset()
{
    // ���� �÷��̿� �����ִ� ������Ʈ���� �����Ѵ�.
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
                // �������� �����Ѵ�.
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
                // �������� �����Ѵ�.
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
                // �������� �����Ѵ�.
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

        // ������ ������ ���๮�ڸ� �־�д�.
        // ������ �� �ε����� (mCountX + 1) ����ŭ �̱�
        // ������ mCountX�� ������ �� �ε����� �ȴ�.
        int OutIndex = i * (mCountX + 1) + mCountX;
        mOutputBuffer[OutIndex] = '\n';
    }
}

void CMaze::Run()
{
    Reset();

    system("cls");

    __int64 TimeStart = time(0);

    // �÷��̾� ����
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


        if (GetTile(PlayerPos.X, PlayerPos.Y) ==
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
                std::cout << "��";

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

    // ���۰� ���� ������ ����� �ٽ� �����Ѵ�.
    mOutputBuffer[StartIndex] = '#';
    mOutputBuffer[GoalIndex] = '%';

    // �������� ���� ������ش�.
    for (int i = 0; i < mObjectCount; ++i)
    {
        mObjectList[i]->Output(mOutputBuffer,
            mCountX + 1);
    }

    // �÷��̾��� ���� ������ �ε����� �������
    // �ǵ������´�.
    if (mPrevPlayerOutput != 0)
    {
        mOutputBuffer[mPrevPlayerIndex] =
            mPrevPlayerOutput;
    }

    mPrevPlayerIndex = PlayerIndex;
    mPrevPlayerOutput = mOutputBuffer[PlayerIndex];

    mOutputBuffer[PlayerIndex] = '$';

    // �ܼ� Ŀ���� ��ġ�� ó������ �����ش�.
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
            // �� ������Ʈ�� ���������� �Ǵ��Ѵ�.
            if (nullptr != dynamic_cast<CItem*>(mObjectList[i]))
            {
                if (dynamic_cast<CItemScore*>(mObjectList[i]))
                {
                    // �������� ü������ �Ǵ��Ѵ�.
                    mScore++;
                }
                else
                {
                    Player->AddHP(1);
                }

                // �������� �԰ԵǸ� ������ �� ��ġ��
                // ��� �ٲ��ش�.
                mOutputBuffer[PlayerIndex] = ' ';

                // ���� ������ �ε������� ���� ���
                if (i < mObjectCount - 1)
                {
                    // ���� ��ġ�� �����۰� �迭�� ����
                    // ������ ������Ʈ�� ��ġ�� �ٲ��ش�.
                    CObject* Temp = mObjectList[i];
                    mObjectList[i] = mObjectList[mObjectCount - 1];
                    mObjectList[mObjectCount - 1] = Temp;
                }

                // ������ �ε����� �����Ѵ�.
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

                // ���� ������ �ε������� ���� ���
                if (i < mObjectCount - 1)
                {
                    // ���� ��ġ�� �����۰� �迭�� ����
                    // ������ ������Ʈ�� ��ġ�� �ٲ��ش�.
                    CObject* Temp = mObjectList[i];
                    mObjectList[i] = mObjectList[mObjectCount - 1];
                    mObjectList[mObjectCount - 1] = Temp;
                }

                // ������ �ε����� �����Ѵ�.
                delete mObjectList[mObjectCount - 1];
                mObjectList[mObjectCount - 1] = nullptr;
                --mObjectCount;
                break;
            }
        }
    }

}
