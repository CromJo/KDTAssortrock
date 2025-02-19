#include "GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	// 메모리릭 체크 기능
	// Debug 모드에서만 가능
	// 출력 창에서 확인가능
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// "매개변수1"번호의 메모리릭을 잡아주는 함수.
	// 호출스택에서 확인가능
	// 호출스택에서 내가 만든 기능을 찾아서 
	//	문제를 해결하면 된다.
	// ※ 필요할때 주석을 해제해서 매개변수에 맞는,
	//	메모리릭을 찾아서 해결하면 된다.
	//_CrtSetBreakAlloc(211);

	if (!CGameManager::GetInstance()->Init(hInstance))
	{
		CGameManager::DestroyInstance();

		return 0;
	} 

	int Ret = CGameManager::GetInstance()->Run();

	CGameManager::DestroyInstance();

	return Ret;
}