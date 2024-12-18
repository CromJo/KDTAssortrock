#include "GameManager.h"

int main()
{
	// CMD의 좌표를 설정한다.
	// COORD Pos;
	// Pos.X = 5;
	// Pos.Y = 3;

	// 콘솔창에서 좌표를 지정하여 해당좌표에
	// 출력할 수 있게 만들어주는 함수이다.
	//SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	//std::cout << "ㅁ" << std::endl;

	if (!CGameManager::GetInst()->Init())
	{
		CGameManager::DestroyInst();
		return 0;
	}

	CGameManager::GetInst()->Run();
	CGameManager::DestroyInst();

	return 0;
}