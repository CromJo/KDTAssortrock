
#include "GameManager.h"
#include "Share/SharedPtr.h"
#include "Share/Object.h"

/*
4번을 누르면 플레이어 주변을 돌고 있는 위성 2개가 더 넓은 간격으로 더 빠르게 회전하게 만들고 5초 뒤 원래대로 돌아오게 한다.

5번을 누르면 플레이어 주변 8방향에 8개의 물체를 생성하고 8방향으로 일정 거리만큼 이동시킨다. 일정거리만큼 이동시킨 후에 2초동안 8개의 물체가 자전한다.
2초 뒤 8개의 물체가 플레이어쪽으로 돌아온다.
*/

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    //int Size = sizeof(Test);

    /*CObject* Obj = nullptr;

    CSharedPtr  ptr = Obj;

    CObject* Obj1 = ptr;*/

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(215);

    if (!CGameManager::GetInst()->Init(hInstance))
    {
        CGameManager::DestroyInst();
        return 0;
    }

    int Ret = CGameManager::GetInst()->Run();

    CGameManager::DestroyInst();

    return Ret;
}