#include "Stage.h"
#include "ObjectManager.h"
#include "Player.h"
#include "StageManager.h"

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

    // ������ ������ �Ǵ����ִ� �Լ��̴�.
    // ���� ���� �����ϸ� 0�� �ƴ� ���� ��ȯ
    // ���� ���� �ƴϸ� 0�� ��ȯ.
    //while (!feof(File))
    //{
    //}

    char    Line[128] = {};
    fgets(Line, 128, File);

    // ������ �и�
    char* Context = nullptr;

    FStageInfo  Info;

    char* Result = strtok_s(Line, ", ", &Context);
    Info.x = atoi(Result);

    Result = strtok_s(nullptr, ", ", &Context);
    Info.y = atoi(Result);

    Info.Dir = (ESpawnDir)atoi(Context);

    mInfoList.emplace_back(Info);

    fclose(File);

    // ������ ���ػ� Ÿ�̸Ӱ� 1�ʴ� ���� �帣����
    // ���� �� �ִ�.
    QueryPerformanceFrequency(&mSecond);

    mStageTime = 0.f;

    mOutputBuffer = new char[(mCountX + 1) * mCountY + 1];
    memset(mOutputBuffer, 0, (mCountX + 1) * mCountY + 1);

    return true;
}

void CStage::Run()
{
    system("cls");

    // ���� ������ ���ػ� Ÿ�̸��� ���� ���´�.
    QueryPerformanceCounter(&mTime);

    mStageTime = 0.f;

    while (true)
    {
        // (���� �� - ������) / �ʴ簪 = �帥�ð�
        LARGE_INTEGER   Time;
        QueryPerformanceCounter(&Time);

        mDeltaTime = (Time.QuadPart - mTime.QuadPart) /
            (float)mSecond.QuadPart;

        mStageTime += mDeltaTime;

        mTime = Time;

        CObjectManager::GetInst()->Update(mDeltaTime);

        COORD   Start = {};
        SetConsoleCursorPosition(
            GetStdHandle(STD_OUTPUT_HANDLE), Start);

        std::vector<std::string> mapSize = CStageManager::GetInst()->GetVectorFileName();

        for (int i = 0; i < mCountY; ++i)
        {
            for (int j = 0; j < mCountX; ++j)
            {
                int Index = i * (mCountX + 1) + j;
                
                int value = mapSize[i][j] - '0';

                switch (value)
                {
                case (int)EObjectState::Road:
                    mOutputBuffer[Index] = ' ';
                    break;
                case (int)EObjectState::Wall:
                    mOutputBuffer[Index] = '!';
                    break;
                case (int)EObjectState::Tail:
                    mOutputBuffer[Index] = '+';
                    break;
                case (int)EObjectState::Item:
                    mOutputBuffer[Index] = '*';
                    break;
                //case (int)EObjectState::Player:
                //    mOutputBuffer[Index] = '!';
                //    break;
                }
            }

            mOutputBuffer[i * (mCountX + 1) + mCountX] = '\n';
        }

        CObjectManager::GetInst()->Output(mOutputBuffer);

        // ���� ���
        std::cout << mOutputBuffer;

    }
}
