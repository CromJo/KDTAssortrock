#include "GameManager.h"
#include "Vector2D.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    if (!CGameManager::GetInstance()->Init(hInstance))
    {
        CGameManager::DestroyInstance();

        return 0;
    }

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetBreakAlloc(215);

    int Ret = CGameManager::GetInstance()->Run();

    CGameManager::DestroyInstance();
    

    return Ret;
}