#include "Function.h"
#include "GameManager.h"

int main()
{
	FPlayer Player;

	//OutputFunction();
	//현재 게임을 초기화한다.

	if (!Init(&Player))
		return 0;
	
	// 초기화 성공시 게임을 실행시킨다.
	Run(); 

	return 0;
}