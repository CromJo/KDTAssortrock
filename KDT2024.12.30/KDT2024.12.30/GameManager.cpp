#include "GameManager.h"
#include "StageManager.h"
#include "ObjectManager.h"

DEFINITION_SINGLE(CGameManager)

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
}

EMainMenu CGameManager::Menu()
{
	system("cls");
	// 여기서 바로 뱀게임 시작되도록 변경

	std::cout << "1. 전투" << std::endl;
	std::cout << "2. 점수" << std::endl;
	std::cout << "3. 종료" << std::endl;
	std::cout << "메뉴를 선택하세요 : ";
	int	Input;
	std::cin >> Input;

	if (Input <= (int)EMainMenu::None ||
		Input > (int)EMainMenu::Exit)
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
