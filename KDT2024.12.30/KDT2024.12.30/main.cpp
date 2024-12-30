#include "GameManager.h"

/*
	뱀게임 만들기.
	1. 플레이어는 처음 네모 1개로 시작한다.
	2. Stage 파일을 이용하여 가로 15, 세로 15개의 Stage를 만들고 벽, 아이템, 플레이어 시작을 만든다.
	3. 플레이어는 처음 시작 위치에 생성되며 자동으로 한 방향으로 계속 이동을 하게 된다.
	4. 이때 방향키를 이용하여 플레이어는 방향을 변경할 수 있다.
	5. 방향을 변경하면 해당 방향으로 이동하는 방식이다.
	6. 플레이어는 벽에 부딪히면 죽게되고 이전 메뉴로 이동한다.
	7. 아이템을 먹을 경우 플레이어의 이동방향 뒤에 꼬리가 1개 생성되며 모든 아이템을 먹게되면 플레이어가 승리하게 된다.
*/


int main()
{
	if (!CGameManager::GetInst()->Init())
	{
		CGameManager::DestroyInst();
		return 0;
	}

	CGameManager::GetInst()->Run();

	CGameManager::DestroyInst();

	return 0;

}
