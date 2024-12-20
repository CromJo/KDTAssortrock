
#include "GameManager.h"

int main()
{
	/*int Key = _getch();

	std::cout << Key << std::endl;

	Key = _getch();

	std::cout << Key << std::endl;

	return 0;*/


	/*int	Array[10];

	// 1번인자에 들어가는 메모리 주소로부터
	// 3번인자에 들어가는 메모리 크기만큼을
	// 2번인자에 들어가는 값으로 채워준다.
	// memset은 값을 채울 때 1바이트 단위로 값을
	// 채워준다.
	// 0000 0001 0000 0001 0000 0001 0000 0001
	memset(Array, 2, sizeof(int) * 10);

	for (int i = 0; i < 10; ++i)
	{
		std::cout << Array[i] << std::endl;
	}

	return 0;*/

	if (!CGameManager::GetInst()->Init())
	{
		CGameManager::DestroyInst();
		return 0;
	}

	CGameManager::GetInst()->Run();

	CGameManager::DestroyInst();

	return 0;
}
