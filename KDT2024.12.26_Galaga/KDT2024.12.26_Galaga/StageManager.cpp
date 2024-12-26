#include "StageManager.h"

DEFINITION_SINGLE(CStageManager)

CStageManager::CStageManager()
{
}

CStageManager::~CStageManager()
{
}

bool CStageManager::Init()
{
    FILE* File = nullptr;

    fopen_s(&File, "StageList.txt", "rt");

    if (!File)
        return false;

    char Line[128] = {};

    fgets(Line, 128, File);

    mCount = atoi(Line);

    mVectorFileName.resize(mCount);        // ���Ҵ��� �Ͼ�� �ʴ´�.
    mVectorName.resize(mCount);         // emplace_back�� ����ϸ�

    for (int i = 0; i < mCount; i++)
    {
        fgets(Line, 128, File);

        int Length = (int)strlen(Line);

        if (Line[Length - 1] == '\n')
            Line[Length - 1] = 0;

        //mVectorFileName.emplace_back(Line);
        mVectorFileName[i] = Line;          // resize��
        char* Context = nullptr;
        mVectorName[i] = strtok_s(Line, ".", &Context);
    }

    fclose(File);

    return true;

}

void CStageManager::Run()
{
    mStage = nullptr;

    while (true)
    {
        system("cls");
        size_t Size = mVectorName.size();

        for (size_t i = 0; i < Size; i++)
        {
            std::cout << i + 1 << ". " << mVectorName[i] << std::endl;
        }

        std::cout << Size + 1 << ". �ڷΰ���" << std::endl;
        std::cout << "���������� �����ϼ��� : ";
        
        int Input;
        std::cin >> Input;

        if (Input <= 0 || Input > Size + 1)
            continue;
        else if (Input == Size + 1)
            break;

        mStage = new CStage;
        mStage->Init(mVectorFileName[Input - 1].c_str());
        mStage->Run();
    }

    SAFE_DELETE(mStage);
}
