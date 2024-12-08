#include "GameManager.h"
#include "Battle.h"

enum EMainMenu
{
	Menu_None = 0,
	Battle,
	Store,
	Inventory,
	Exit,
	
	Max				// �ݺ���üũ��
};

// Ȥ�� �ʱ�ȭ �ϸ鼭 ���� ���� ���� ��츦 üũ�ϱ� ���� bool �Լ�
bool Init(FPlayer* Player)
{
	std::cout << "�г��� : ";
	std::cin >> Player->Name;

	while (true)
	{
		std::cout << "1. ����" << std::endl;
		std::cout << "2. �ü�" << std::endl;
		std::cout << "3. ����" << std::endl;
		std::cout << "4. ����" << std::endl;
		std::cout << "������ �����ϼ��� : " << std::endl;

		int Class = 0;
		std::cin >> Class;

		if (Class <= (int)EClass::None || Class >= (int)EClass::Back)
			continue;

		Player->Class = (EClass)Class;
		break;
	}

	if (!InitBattle())
		return false;

	// ���� �ʱ�ȭ ���н� ���� ����
	return true;
}

EMainMenu Menu()
{
	system("cls");
	std::cout << "1. ����" << std::endl;
	std::cout << "2. ����" << std::endl;
	std::cout << "3. ����" << std::endl;
	std::cout << "4. ����" << std::endl;
	std::cout << "�޴� ���� : " << std::endl;

	int SelectMenu = 0;
	
	std::cin >> SelectMenu;
	
	if (SelectMenu <= EMainMenu::Menu_None || SelectMenu > EMainMenu::Exit)
		return EMainMenu::Menu_None;

	// ���������� ������ �ߴٸ�,
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