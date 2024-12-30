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

    // 파일의 끝인지 판단해주는 함수이다.
    // 파일 끝에 도달하면 0이 아닌 값을 반환
    // 파일 끝이 아니면 0을 반환.
    //while (!feof(File))
    //{
    //}

    char    Line[128] = {};
    fgets(Line, 128, File);

    // 데이터 분리
    char* Context = nullptr;

    FStageInfo  Info;

    char* Result = strtok_s(Line, ", ", &Context);
    Info.x = atoi(Result);

    Result = strtok_s(nullptr, ", ", &Context);
    Info.y = atoi(Result);

    Info.Dir = (ESpawnDir)atoi(Context);

    mInfoList.emplace_back(Info);

    fclose(File);

    // 윈도우 고해상도 타이머가 1초당 몇이 흐르는지
    // 얻어올 수 있다.
    QueryPerformanceFrequency(&mSecond);

    mStageTime = 0.f;

    mOutputBuffer = new char[(mCountX + 1) * mCountY + 1];
    memset(mOutputBuffer, 0, (mCountX + 1) * mCountY + 1);

    return true;
}

void CStage::Run()
{
    system("cls");

    // 현재 윈도우 고해상도 타이머의 값을 얻어온다.
    QueryPerformanceCounter(&mTime);

    mStageTime = 0.f;

    while (true)
    {
        // (현재 값 - 이전값) / 초당값 = 흐른시간
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

        // 버퍼 출력
        std::cout << mOutputBuffer;

    }
}
