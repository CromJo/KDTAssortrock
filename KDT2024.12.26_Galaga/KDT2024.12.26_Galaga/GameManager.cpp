#include "GameManager.h"
#include "StageManager.h"
#include "ObjectManager.h"

DEFINITION_SINGLE(CGameManager)

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
    CStageManager::DestroyInst();
    CObjectManager::DestroyInst();
}

EMainMenu CGameManager::Menu()
{
    system("cls");
    std::cout << "1. ����" << std::endl;
    std::cout << "2. ����" << std::endl;
    std::cout << "3. ����" << std::endl;
    std::cout << "�޴��� �����ϼ���. : ";

    int Input;
    std::cin >> Input;

    if (Input <= (int)EMainMenu::None || Input > (int)EMainMenu::Exit)
        return EMainMenu::None;

    return (EMainMenu)Input;
}

bool CGameManager::Init()
{
    if (!CStageManager::GetInst()->Init())
        return false;
    if (!CObjectManager::GetInst()->Init())
        return false;

    return true;
}

void CGameManager::Run()
{
    while (true)
    {
        switch (Menu())
        {
        case EMainMenu::Stage:
            CStageManager::GetInst()->Run();
            break;
        case EMainMenu::Score:
            break;
        case EMainMenu::Exit:
            return;
        }
    }
}
