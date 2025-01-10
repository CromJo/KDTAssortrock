#include "GameManager.h"
#include "BoardManager.h"

CGameManager* CGameManager::Instance = nullptr;


CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
	// ��� �̱��� ��ü�� ���⼭ ����x
	CBoardManager::DestroyInstance();
}

/// <summary>
/// ��� �� �Է� �Լ�
/// </summary>
/// <returns></returns>
EMenuButton CGameManager::MainMenu()
{
	system("cls");
	std::cout << "1. ��Ʈ���� ���ӽ���" << std::endl;
	std::cout << "2. Top 10" << std::endl;
	std::cout << "3. ���� (��ũ��, Ŀ���� ��� �߰�)" << std::endl;
	std::cout << "4. ���� ����" << std::endl;
	std::cout << "�Է� : ";

	int Input = 0;
	std::cin >> Input;

	if (Input < (int)EMenuButton::None ||
		Input >(int)EMenuButton::Exit)
		return EMenuButton::None;

	return (EMenuButton)Input;
}

bool CGameManager::Init()
{
	FILE* File = nullptr;

	fopen_s(&File, "Board.txt", "rb");

	if (!File)
		return false;

	char Line[128] = {};
	fgets(Line, 128, File);

	CBoardManager::GetInstance()->Init(Line);

	fclose(File);

	return true;
}

void CGameManager::Run()
{
	while (true)
	{
		switch (MainMenu())
		{
			case EMenuButton::Tetris:
				CBoardManager::GetInstance()->Run();
				break;
			case EMenuButton::Score:
				break;

			case EMenuButton::Setting:
				break;

			case EMenuButton::Exit:
				break;
		}
	}
}
