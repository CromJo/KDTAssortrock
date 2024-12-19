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
	
	/*
	int Array[10] = {};

	// 1번 인자에 들어가는 메모리 주소로 부터
	// 3번 인자에 들어가는 메모리 크기만큼을
	// 2번 인자에 들어가는 값으로 채워준다.
	// memset은 값을 채울 때 1byte 단위로 값을 채워준다.
	memset(Array, 1, sizeof(int) * 5);

	for (int i = 0; i < 5; i++)
	{
		std::cout << Array[i] << std::endl;
	}
	return 0;
	*/


	if (!CGameManager::GetInst()->Init())
	{
		CGameManager::DestroyInst();
		return 0;
	}

	CGameManager::GetInst()->Run();
	CGameManager::DestroyInst();

	return 0;
}