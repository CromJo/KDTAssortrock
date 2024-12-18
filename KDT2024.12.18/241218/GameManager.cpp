#include "GameManager.h"
#include "MazeManager.h"

DEFINITION_SINGLE(CGameManager)
/*
	0 : 길
	1 : 벽
	2 : 시작점
	3 : 도착점
*/

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
}

bool CGameManager::Init()
{
	CMazeManager::GetInst()->Init();

	return true;
}

void CGameManager::Run()
{
	CMazeManager::GetInst()->Run();
}
