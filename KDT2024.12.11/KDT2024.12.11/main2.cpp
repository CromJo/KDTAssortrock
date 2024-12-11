#include "GameManager.h"

int main()
{
	if (!CGameManager::GetInstance()->Init())
	{
		// 초기화 실패시 생성한 객체를 제거 후 종료
		CGameManager::DestroyInstance();
		
		return 0;
	}

	CGameManager::GetInstance()->Run();

	// 게임이 끝나도 메모리를 제거한다.
	CGameManager::DestroyInstance();

	return 0;
}