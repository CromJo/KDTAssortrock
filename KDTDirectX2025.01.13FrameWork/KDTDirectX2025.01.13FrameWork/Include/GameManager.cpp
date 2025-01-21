#include "GameManager.h"
#include "resource.h"
#include "Share/Timer.h"
#include "Device.h"
#include "Asset/AssetManager.h"
#include "Shader/ShaderManager.h"
#include "Asset/Mesh/MeshManager.h"
#include "Asset/Mesh/Mesh.h"
#include "Shader/Shader.h"
#include "Shader/TransformCBuffer.h"
#include "Scene/SceneManager.h"

DEFINITION_SINGLE(CGameManager)

bool CGameManager::mLoop = true;

CGameManager::CGameManager()
{

}

CGameManager::~CGameManager()
{
    // Asset Manager먼저 제거
    CSceneManager::DestroyInstance();
    
    CAssetManager::DestroyInstance();
    
    CShaderManager::DestroyInstance();

    CDevice::DestroyInstance();

    // Device Context 해제
    ReleaseDC(mHandleWindow, mHandleDC);
}

bool CGameManager::Init(HINSTANCE hInst)
{
	mHandleInstance = hInst;

	// Unicode용 strcpy함수
	// TEXT : define기능으로 Unicode는 ""앞에 L을 붙여 사용해야하지만,
	//		L을 안붙이고 사용하기 위한 가독성 전처리기
	lstrcpy(mClassName, TEXT("KDTDirectX20250113FrameWork"));
	lstrcpy(mTitleName, TEXT("KDTDirectX20250113FrameWork"));

	RegisterWindowClass();

    if (!Create())
        return false;

    // 인자로 들어간 윈도우에 출력할 수 있는 DC가 만들어진다.
    mHandleDC = GetDC(mHandleWindow);

    // 디바이스 초기화
    if (!CDevice::GetInstance()->Init(mHandleWindow, 1280, 720, true))
        return false;

    if (!CShaderManager::GetInstance()->Init())
        return false;

    // 에셋 관리자 초기화
    if (!CAssetManager::GetInstance()->Init())
        return false;

    // 타이머 초기화
    CTimer::Init();

    // 장면관리자 초기화
    if (!CSceneManager::GetInstance()->Init())
        return false;

	return true;
}

int CGameManager::Run()
{
    MSG msg;

    while (mLoop)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            // Accelerator는 무시한다. (이유 : 나도 모름)
            //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            // TranslateMessage : 키보드 입력 메세지 발생 시 실행된다.
            //      WM_KEYDOWN, WM_KEYUP 등 메세지가 발생하면 문자일 경우, 
            //      WM_CHAR 메세지를 하나 더 만들어준다.
            TranslateMessage(&msg);

            // DispatchMessage : 메세지를 WndProc으로 전달해준다.
            DispatchMessage(&msg);
        }
        else
        {
            Logic();
        }
    }

    return (int)msg.wParam;
}

void CGameManager::Logic()
{
    float DeltaTime = CTimer::Update();

    Input(DeltaTime);
    Update(DeltaTime);
    Collision(DeltaTime);
    Render(DeltaTime);
}

void CGameManager::Input(float deltaTime)
{
    CSceneManager::GetInstance()->Input(deltaTime);
}

void CGameManager::Update(float deltaTime)
{
    CSceneManager::GetInstance()->Update(deltaTime);
}

void CGameManager::Collision(float deltaTime)
{
    CSceneManager::GetInstance()->Collision(deltaTime);
}

void CGameManager::Render(float deltaTime)
{
    CDevice::GetInstance()->ClearBackBuffer(mClearColor);
    CDevice::GetInstance()->ClearDepthStencil(1.f, 0);
    CDevice::GetInstance()->SetTarget();

    CSceneManager::GetInstance()->Render();
    CDevice::GetInstance()->Render();
}

void CGameManager::RegisterWindowClass()
{
    WNDCLASSEXW wcex;

    // 윈도우클래스 구조체의 크기를 나타낸다.
    // 반드시 지정되어야 한다.
    wcex.cbSize = sizeof(WNDCLASSEX);

    // 클라이언트 영역 : Window창 틀 안의 출력 가능한 모든 부분.
    // 클라 영역의 크기(가로/세로)가 변경될 시 전부 다시 그린다.
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    // 메세지큐에서 얻어온 메세지를 인자로 넣어서 호출해줄 함수의 주소를 넘겨준다.
    wcex.lpfnWndProc = WndProc;
    // Cls | Wnd Extra : 예약된 메세지 (쓸대 없음)
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    // 운영체제에서 부여해준 HInstance를 전달한다.
    wcex.hInstance = mHandleInstance;
    // Icon : 실행파일 아이콘을 지정한다.
    // 속성->일반속성->대상 이름의 _Debug를 안붙이니 오류가 뜬다 왜 그런지 여쭤보기.
    wcex.hIcon = LoadIcon(mHandleInstance, MAKEINTRESOURCE(IDI_ICON1));
    // Cursor : 윈도우 프로그램 내 창에서의 커서 모양을 나타낸다.
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    // 클라이언트 영역의 색상을 지정한다.
    // 1 : 횐색 | 2 : 회색 | 3 : 검은색
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    // MenuName : 윈도우 메뉴를 지정한다.
    // 0을 넣어줄 시 메뉴창이 사라진다.
    wcex.lpszMenuName = 0;
    // ClassName : 등록할 윈도우클래스의 이름을 지정한다.
    wcex.lpszClassName = mClassName;
    // IconSm : 왼쪽 최상단의 Small Icon을 지정한다.
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    // 위에서 설정한 윈도우 클래스를 등록한다.
    RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
    // CreateWindow : 윈도우 창을 생성해주는 함수이다.
    // WinAPI에서 함수명뒤에 W가 붙으면 유니코드, A가 붙으면 멀티바이트이다.
    // 1번인자 : 윈도우 클래스 이름을 지정한다.
    // 2번인자 : 윈도우 타이틀바에 출력할 이름을 지정한다.
    // 3번인자 : 윈도우 창의 모양을 결정한다.
    // 4번인자 : 화면에서 윈도우가 시작할 X지점을 지정한다.
    // 5번인자 : 화면에서 윈도우가 시작할 Y지점을 지정한다.
    // 6번인자 : 윈도우 창의 가로 크기를 지정한다.
    // 7번인자 : 윈도우 창의 세로 크기를 지정한다.
    // 8번인자 : 부모윈도우가 있을 경우 부모윈도우의 핸들을 지정한다.
    // 9번인자 : 메뉴 핸들을 전달한다.
    // 10번인자 : 윈도우 인스턴스를 전달한다. WinMain에서 전달은 값으로 전달해야 한다.
    // 11번인자 : 창 생성 데이터를 지정한다. WM_CREATE는 윈도우 생성시 발생하는 메세지인데
    // 이 메세지가 발생하면 WndProc 함수의 lParam에 이 값이 전달된다.
    // 이렇게 윈도우를 생성하면 윈도우 핸들을 만들어준다.
    // 잘못된 생성일 경우 0을 반환한다.
    mHandleWindow = CreateWindowW(mClassName, mTitleName, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, mHandleInstance, nullptr);

    if (!mHandleWindow)
    {
        return false;
    }

    // 윈도우 클라 영역의 크기를 원하는 크기로 지정.
    // 위에서 지정한 윈도우 크기는 타이틀바 등의 크기가 모두 합쳐진 크기로 지정.
    RECT WindowRect = { 0, 0, 1280, 720 };

    // 클라 영역이 1280, 720이 되기 위해 필요한 윈도우 전체 크기를 얻어온다.
    // (ThickFrame, Menu, TitleBar 등이 포함된 전체크기)
    AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW, FALSE);

    SetWindowPos(mHandleWindow, HWND_TOPMOST, 100, 100, 
        WindowRect.right - WindowRect.left, 
        WindowRect.bottom - WindowRect.top, 
        SWP_NOMOVE | SWP_NOZORDER);

    // ShowWindow : 창을 출력할 지 숨길지 결정한다.
    ShowWindow(mHandleWindow, SW_SHOW);
    // UpdateWindow : 클라이언트 영역을 강제로 다시 크리게 요청해준다.
    UpdateWindow(mHandleWindow);

    return true;
}

LRESULT CGameManager::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        mLoop = false;
        PostQuitMessage(0);

        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
