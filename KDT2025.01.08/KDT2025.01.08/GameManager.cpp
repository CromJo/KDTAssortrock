#include "GameManager.h"
#include "Board.h"

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
	// 모든 싱글톤 객체는 여기서 해제

}

/// <summary>
/// 출력 및 입력 함수
/// </summary>
/// <returns></returns>
EMenuButton CGameManager::MainMenu()
{
	system("cls");
	std::cout << "1. 테트리스 게임시작" << std::endl;
	std::cout << "2. Top 10" << std::endl;
	std::cout << "3. 설정 (맵크기, 커스텀 블록 추가)" << std::endl;
	std::cout << "4. 게임 종료" << std::endl;
	std::cout << "입력 : ";

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

	CBoard::GetInstance()->Init(Line);

	return true;
}

void CGameManager::Run()
{

}
