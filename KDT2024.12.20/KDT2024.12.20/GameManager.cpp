#include "GameManager.h"
#include "MazeManager.h"

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
	std::cout << "1. �̷�" << std::endl;
	std::cout << "2. ����" << std::endl;
	std::cout << "3. ����" << std::endl;
	std::cout << "�޴��� �����ϼ��� : ";
	int	Input;
	std::cin >> Input;

	if (Input < (int)EMainMenu::None ||
		Input >(int)EMainMenu::Exit)
		return EMainMenu::None;

	return (EMainMenu)Input;
}

bool CGameManager::Init()
{
	CMazeManager::GetInst()->Init();

	return true;
}

void CGameManager::Run()
{
	while (true)
	{
		switch (Menu())
		{
		case EMainMenu::Maze:
			CMazeManager::GetInst()->Run();
			break;
		case EMainMenu::Score:
			CMazeManager::GetInst()->RunScore();
			break;
		case EMainMenu::Exit:
			return;
		}
	}
}
