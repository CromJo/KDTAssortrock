
#include "GameManager.h"

//#define	TEST	std::cout << "Test" << std::endl

int main()
{
	// 아래처럼 코드를 붙여주고 컴파일한다.
	//TEST;
	//std::cout << "Test" << std::endl;

	FPlayer	Player;

	//OutputFunction();
	// 게임을 초기화 한다.
	if (Init(&Player) == false)
		return 0;

	// 초기화에 성공했을 경우 게임을 동작시킨다.
	Run(&Player);

	Destroy();


	return 0;
}
