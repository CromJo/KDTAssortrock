﻿
#include "StoreManager.h"
#include "Store.h"

enum EStoreMenu
{
	None,
	Weapon,
	Armor,
	Back
};

bool InitStoreManager()
{
	if (InitStore() == false)
		return false;

	return true;
}

void DestroyStoreManager()
{
	DestroyStore();
}

EStoreMenu Menu()
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

	return (EStoreMenu)SelectMenu;
}

void RunStoreManager(FPlayer* Player)
{
	while (true)
	{
		switch (Menu())
		{
		case Weapon:
			RunStore(Player, Item_Weapon);
			break;
		case Armor:
			RunStore(Player, Item_Armor);
			break;
		case Back:
			return;
		}
	}
}

