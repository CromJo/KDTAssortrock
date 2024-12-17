#include "GameManager.h"
#include "ObjectManager.h"
#include "BattleManager.h"
#include "StoreManager.h"

DEFINITION_SINGLE(CGameManager)

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
	CObjectManager::DestroyInst();

	CBattleManager::DestroyInst();

	CStoreManager::DestroyInst();
}

bool CGameManager::Init()
{
	CObjectManager::GetInst()->Init();

	CBattleManager::GetInst()->Init();

	CStoreManager::GetInst()->Init();

	return true;
}

EMainMenu::Type CGameManager::Menu()
{
	system("cls");
	std::cout << "1. 전투" << std::endl;
	std::cout << "2. 상점" << std::endl;
	std::cout << "3. 가방" << std::endl;
	std::cout << "4. 종료" << std::endl;
	std::cout << "메뉴 선택 : ";

	int SelectMenu = 0;

	std::cin >> SelectMenu;

	// 잘못된 메뉴를 선택했을 경우
	if (SelectMenu <= EMainMenu::None ||
		SelectMenu > EMainMenu::Exit)
		return EMainMenu::None;

	return (EMainMenu::Type)SelectMenu;
}

void CGameManager::Run()
{
	while (true)
	{
		switch (Menu())
		{
		case EMainMenu::Battle:
			break;
		case EMainMenu::Store:
			CStoreManager::GetInst()->Run();
			break;
		case EMainMenu::Inventory:
			break;
		case EMainMenu::Exit:
			return;
		}
	}
}
