
#include "GameManager.h"
#include "Share/SharedPtr.h"
#include "Share/Object.h"

/*
총알 생성 위치 : 플레이어 위쪽에서 생성.
총알이 회전되었기 때문에 총알의 방향대로 이동할 수 있게 코드 수정.

2번을 누르면 2개의 서브에서 3초동안 0.2초에 1번씩 총알 발사.

3번을 누르면 회전하며 앞으로 나아가는 총알 생성.
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