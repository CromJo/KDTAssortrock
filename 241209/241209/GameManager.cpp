﻿
#include "GameManager.h"
#include "Battle.h"
#include "StoreManager.h"
#include "Inventory.h"

enum EMainMenu
{
	None,
	Battle,
	Store,
	Inventory,
	Exit
};

bool Init(FPlayer* Player)
{
	// 플레이어 초기화
	std::cout << "이름 : ";
	std::cin >> Player->Name;

	while (true)
	{
		std::cout << "1. 기사" << std::endl;
		std::cout << "2. 궁수" << std::endl;
		std::cout << "3. 마법사" << std::endl;
		std::cout << "직업을 선택하세요 : ";
		int	Job = 0;
		std::cin >> Job;

		if (Job <= (int)EJob::None ||
			Job >= (int)EJob::End)
			continue;

		Player->Job = (EJob)Job;
		break;
	}

	switch (Player->Job)
	{
	case EJob::Knight:
		Player->Attack = 40;
		Player->Defense = 20;
		Player->HP = 500;
		Player->HPMax = 500;
		Player->MP = 100;
		Player->MPMax = 100;
		break;
	case EJob::Archer:
		Player->Attack = 50;
		Player->Defense = 15;
		Player->HP = 400;
		Player->HPMax = 400;
		Player->MP = 200;
		Player->MPMax = 200;
		break;
	case EJob::Magicion:
		Player->Attack = 60;
		Player->Defense = 10;
		Player->HP = 300;
		Player->HPMax = 300;
		Player->MP = 300;
		Player->MPMax = 300;
		break;
	}

	Player->Level = 1;
	Player->Exp = 0;
	Player->Gold = 10000;


	// 전투 초기화
	if (InitBattle() == false)
		return false;

	// 상점 초기화
	if (InitStoreManager() == false)
		return false;

	return true;
}

void Destroy()
{
	DestroyStoreManager();

	DestroyInventory();
}

EMainMenu Menu()
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

	return (EMainMenu)SelectMenu;
}

void Run(FPlayer* Player)
{
	while (true)
	{
		switch (Menu())
		{
		case Battle:
			RunBattle(Player);
			break;
		case Store:
			RunStoreManager(Player);
			break;
		case Inventory:
			RunInventory(Player);
			break;
		case Exit:
			return;
		}
	}
}
