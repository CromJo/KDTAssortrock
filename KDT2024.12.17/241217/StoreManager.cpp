#include "StoreManager.h"
#include "StoreWeapon.h"
#include "StoreArmor.h"

DEFINITION_SINGLE(CStoreManager)

CStoreManager::CStoreManager()
{
}

CStoreManager::~CStoreManager()
{
}

bool CStoreManager::Init()
{
	mStoreList[0] = new CStoreWeapon;
	mStoreList[0]->Init();

	mStoreList[1] = new CStoreArmor;
	mStoreList[1]->Init();

	return true;
}

EStoreMenu::Type CStoreManager::Menu()
{
	system("cls");
	std::cout << "1. 무기" << std::endl;
	std::cout << "2. 방어구" << std::endl;
	std::cout << "3. 뒤로가기" << std::endl;
	std::cout << "메뉴 선택 : ";

	int SelectMenu = 0;

	std::cin >> SelectMenu;

	// 잘못된 메뉴를 선택했을 경우
	if (SelectMenu <= EStoreMenu::None ||
		SelectMenu > EStoreMenu::Back)
		return EStoreMenu::None;

	return (EStoreMenu::Type)SelectMenu;
}

void CStoreManager::Run()
{
	while (true)
	{
		switch (Menu())
		{
		case EStoreMenu::Weapon:
			mStoreList[EStoreType::Weapon]->Run();
			break;
		case EStoreMenu::Armor:
			mStoreList[EStoreType::Armor]->Run();
			break;
		case EStoreMenu::Back:
			return;
		}
	}
}
