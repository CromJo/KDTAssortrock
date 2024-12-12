#include "StoreManager.h"
#include "Store.h"

EStoreMenu::Type CStoreManager::Menu()
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
	if (SelectMenu <= EStoreMenu::None ||
		SelectMenu > EStoreMenu::Back)
		return EStoreMenu::None;

	return (EStoreMenu::Type)SelectMenu;
}

bool CStoreManager::Init()
{
	mStore[EStoreType::Weapon] = new CStore;
	mStore[EStoreType::Weapon]->Init(EStoreType::Weapon);
	mStore[EStoreType::Armor] = new CStore;
	mStore[EStoreType::Armor] = new CStore;

	return false;
}

void CStoreManager::Run()
{
	while (true)
	{
		switch (Menu())
		{
		case EStoreMenu::Weapon:
			mStore[EStoreType::Weapon]->Run();
			break;
		case EStoreMenu::Armor:
			mStore[EStoreType::Armor]->Run();
			break;
		case EStoreMenu::Back:
			return;
		}
	}
}
