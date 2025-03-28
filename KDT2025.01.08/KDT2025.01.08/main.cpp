#include <iostream>
#include "GameManager.h"
#include "BoardManager.h"


/*
	-------------------------- 테트리스 만들기 ----------------------------
	1. 블록들의 모양이 있어야한다.
		txt로 블록 모양을 설정?
		아니면 2차 배열로 모양 하나하나 설정?
			※ 구현 : 2차원 Vector로 모양을 설정해둔 Default 블럭을 생성함.
				문제점 : Custom Block을 추가하려는데 죠낸 어려움.

	2. 블록들은 설정된 시간마다 한칸 씩 아래로 내려와야한다.
		한칸씩 내려오다가 한 블럭이라도 더 이상 내려갈 수 없는 상태 (충돌)가 된다면
			모든 블록은 그 자리에 고정되어야 한다.
	3. 내가 설정한 가로열의 배열이 블록으로 꽉찬 상태라면, 그 가로열이 사라진다.
		사라지고 그 위에 있던 모든 블록들은 고정된 상태에서 한칸씩만 내려온다.
	4. 보드판의 크기를 설정해준다.
		보드판은 진또배기 파일로 크기 설정을 해주자.


	※ 부가선택 : 
		1. 점수를 추가한다.
		2. 오래 버틸수록 블록이 내려오는 속도가 빨라진다.
		3. 가로열에 몇군대씩 이빨이 빠져있는 블록열들을 추가한다.
			기존 아래에 고정되어있던 것들은 한칸씩 위로 올라온다.

	이때 쓸 수 있는 자료구조가 있을까?
	우선 여태껏 사용해본 기능들을 최대한 많이 쓴다는 목적을 두고 기능들을 만들어볼 예정.
	1. 테트리스의 블록모양은 블록에디터로 구현할 예정
		
*/

int main()
{
	if (!CGameManager::GetInstance()->Init())
	{
		CGameManager::DestroyInstance();

		return 0;
	}

	CGameManager::GetInstance()->Run();
	CGameManager::DestroyInstance();
	return 0;
}