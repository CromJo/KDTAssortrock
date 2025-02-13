#include "GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	if (!CGameManager::GetInstance()->Init(hInstance))
	{
		CGameManager::DestroyInstance();

		return 0;
	} 

	int Ret = CGameManager::GetInstance()->Run();

	CGameManager::DestroyInstance();

	return Ret;
}