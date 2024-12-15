#include "StoreManager.h"
#include "Store.h"

CStoreManager::CStoreManager()
{
}

CStoreManager::~CStoreManager()
{
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

bool CStoreManager::Init()
{
	mStore[EStoreType::Weapon] = new CStore;

	mStore[EStoreType::Weapon]->Init(EStoreType::Weapon);

	mStore[EStoreType::Armor] = new CStore;

	mStore[EStoreType::Armor]->Init(EStoreType::Armor);

    return true;
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
