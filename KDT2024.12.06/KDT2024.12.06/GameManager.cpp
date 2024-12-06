#include "GameManager.h"
#include "Battle.h"

enum EMainMenu : unsigned char
{
	None = 0,
	Battle,
	Store,
	Inventory,
	Exit,
	
	Max				// 반복문체크용
};

// 혹시 초기화 하면서 실패 했을 때의 경우를 체크하기 위한 bool 함수
bool Init(FPlayer* Player)
{
	std::cout << "닉네임 : ";
	std::cin >> Player->Name;
	std::cin >> Player->Name;

	while (true)
	{
		std::cout << "1. 전사" << std::endl;
		std::cout << "2. 궁수" << std::endl;
		std::cout << "3. 법사" << std::endl;
		std::cout << "4. 도적" << std::endl;
		std::cout << "직업을 선택하세요 : " << std::endl;

		int Class = 0;
		std::cin >> Class;

		if (Class <= (int)EClass::None || Class >= (int)EClass::Back)
			continue;

		Player->Class = (EClass)Class;
		break;
	}

	if (!InitBattle())
		return false;

	// 성공시 배틀기능 초기화
	InitBattle();

	// 전투 초기화 실패시 게임 종료

	return true;
}

EMainMenu Menu()
{
	system("cls");
	std::cout << "1. 전투" << std::endl;
	std::cout << "2. 상점" << std::endl;
	std::cout << "3. 가방" << std::endl;
	std::cout << "4. 종료" << std::endl;
	std::cout << "메뉴 선택 : " << std::endl;

	int SelectMenu = 0;
	
	std::cin >> SelectMenu;
	
	if (SelectMenu <= EMainMenu::None || SelectMenu > EMainMenu::Exit)
		return EMainMenu::None;

	// 정상적으로 선택을 했다면,
	return (EMainMenu)SelectMenu;
}

void Run()
{
	while (true)
	{
		switch (Menu())
		{
		case Battle:
			RunBattle();
			break;
		case Store:
			break;
		case Inventory:
			break;
		case Exit:
			return;
		}
	}
}