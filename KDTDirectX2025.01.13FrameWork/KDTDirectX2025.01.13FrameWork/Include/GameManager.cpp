#include "GameManager.h"
#include "resource.h"
#include "Share/Timer.h"
#include "Device.h"

DEFINITION_SINGLE(CGameManager)

bool CGameManager::mLoop = true;

CGameManager::CGameManager()
{

}

CGameManager::~CGameManager()
{
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

    if (!CDevice::GetInstance()->Init(mHandleWindow, 1280, 720, true))
        return false;

    // 타이머 초기화
    CTimer::Init();

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
    PostUpdate(DeltaTime);
    Collision(DeltaTime);
    PostCollisionUpdate(DeltaTime);
    Render(DeltaTime);

}

void CGameManager::PlayerMoveUpdate(float deltaTime)
{
    FVector2D PlayerMoveDirect;

    // 문자 키 abc,123 등... (문자 1개씩만 대문자로 사용가능)
    if (GetAsyncKeyState('W') & 0x8000)
    {
        PlayerMoveDirect.y -= 1.f;/*
        mRect.Top -= 400 * deltaTime;
        mRect.Bottom -= 400 * deltaTime;*/
    }
    if (GetAsyncKeyState('S') & 0x8000)
    {
        PlayerMoveDirect.y += 1.f;/*
        mRect.Top += 400 * deltaTime;
        mRect.Bottom += 400 * deltaTime;*/
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        PlayerMoveDirect.x -= 1.f;/*
        mRect.Left -= 400 * deltaTime;
        mRect.Right -= 400 * deltaTime;*/
    }
    if (GetAsyncKeyState('D') & 0x8000)
    {
        PlayerMoveDirect.x += 1.f;/*
        mRect.Left += 400 * deltaTime;
        mRect.Right += 400 * deltaTime;*/
    }

    PlayerMoveDirect.Normalize();
    mPlayerPos += PlayerMoveDirect * 400.f * deltaTime;
}

void CGameManager::PlayerAttackUpdate(float deltaTime)
{
    // 특수 키 (Space, Enter 등)
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        FBullet Bullet;
        
        Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
        Bullet.Pos.y = mPlayerPos.y;

        Bullet.Size = FVector2D(50.f, 50.f);
        Bullet.MoveDirect = FVector2D(1.f, 0.f);

        Bullet.Distance = 1200.f;

        mPlayerBulletList.push_back(Bullet);
    }

    if (GetAsyncKeyState('1') & 0x8000)
    {
        for (int i = 0; i < 3; i++)
        {
            FBullet Bullet;

            Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
            Bullet.Pos.y = mPlayerPos.y;

            Bullet.Size = FVector2D(50.f, 50.f);
            Bullet.MoveDirect = FVector2D(1.f, i - 1.f);
            Bullet.MoveDirect.Normalize();

            Bullet.Distance = 800.f;

            mPlayerBulletList.push_back(Bullet);
        }
    }

    if (GetAsyncKeyState('2') & 0x8000)
    {
        FVector2D Direct[8] =
        {
            {1.f, 0.f},
            {1.f, 1.f},
            {0.f, 1.f},
            {-1.f, 1.f},
            {-1.f, 0.f},
            {-1.f, -1.f},
            {0.f, -1.f},
            {1.f, -1.f},
        };

        for (int i = 0; i < 8; i++)
        {
            FBullet Bullet;

            Bullet.Size = FVector2D(50.f, 50.f);
            Bullet.MoveDirect = Direct[i];
            Bullet.MoveDirect.Normalize();

            Bullet.Pos = mPlayerPos + Bullet.MoveDirect * 100.f;
            Bullet.Distance = 600.f;

            mPlayerBulletList.push_back(Bullet);
        }
    }

    if (GetAsyncKeyState('3') & 0x8000)
    {
        FBullet Bullet;

        Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
        Bullet.Pos.y = mPlayerPos.y;

        Bullet.Size = FVector2D(50.f, 50.f);
        Bullet.MoveDirect = FVector2D(1.f, -1.f);

        Bullet.Distance = FLT_MAX;
        Bullet.Option = EBulletOption::Bounce;

        mPlayerBulletList.push_back(Bullet);
    }
}

void CGameManager::Input(float deltaTime)
{
    PlayerMoveUpdate(deltaTime);
    
    PlayerAttackUpdate(deltaTime);
}

//FRect Enemy = { 1000, 100, 1100, 200 };

void CGameManager::EnemyMoveUpdate(float deltaTime)
{
    if (isTopCollision)
    {
        // Top이 0보다 작아졌다는 것은 상단 화면을 넘어간다는 뜻.
        if(mEnemyPos.y - mEnemySize.y / 2.f <= 0.f)
        {
            isTopCollision = false;
        }
        //Enemy.Top -= 600 * deltaTime;
        //Enemy.Bottom -= 600 * deltaTime;
        mEnemyDirect = -1.f;
    }
    else
    {
        // Bottom이 720보다 커졌다는 것은, 하단 화면을 넘어간다는 뜻.
        if (mEnemyPos.y + mEnemyPos.y / 2.f >= 720)
        {
            isTopCollision = true;
        }
        //Enemy.Top += 600 * deltaTime;
        //Enemy.Bottom += 600 * deltaTime;
        mEnemyDirect = 1.f;
    }

    mEnemyPos.y += mEnemyDirect * 300.f * deltaTime;
}

void CGameManager::EnemyAttackUpdate(std::list<FBullet>& BulletList, float deltaTime)
{
    // N초당 1번 공격
    mAttackSpeed += deltaTime;

    if (mAttackSpeed > 1.f)
    {
        //mAttackSpeed = 0.f  이런식으로 할시 소수점 단위가 소실되어 결국 균등하지 못하게 된다+.
        mAttackSpeed -= 1.f;

        FBullet Bullet;

        Bullet.Pos.x = mEnemyPos.x - mEnemySize.x / 2.f - 25.f;
        Bullet.Pos.y = mEnemyPos.y;

        Bullet.Size = FVector2D(50.f, 50.f);
        
        // Normalize
        Bullet.MoveDirect = mPlayerPos - Bullet.Pos;
        Bullet.MoveDirect.Normalize();

        //Bullet.Left = Enemy.Left - 100.f;
        //Bullet.Top = Enemy.Top + 25.f;
        //Bullet.Right = Bullet.Left + 50.f;
        //Bullet.Bottom = Bullet.Top + 50.f;

        BulletList.push_back(Bullet);
    }
}

void CGameManager::EnemyBulletUpdate(std::list<FBullet>& BulletList, float deltaTime)
{
    std::list<FBullet>::iterator iter = BulletList.begin();
    std::list<FBullet>::iterator iterEnd = BulletList.end();

    for (; iter != iterEnd; iter++)
    {
        (*iter).Pos += (*iter).MoveDirect * 500.f * deltaTime;
        /*(*iter).Left -= 500.f * deltaTime;
        (*iter).Right -= 500.f * deltaTime;
        */
    }
}

void PlayerBulletUpdate(std::list<FBullet> &BulletList, float deltaTime)
{
    std::list<FBullet>::iterator iter = BulletList.begin();
    std::list<FBullet>::iterator iterEnd = BulletList.end();

    for (; iter != iterEnd;)
    {
        FVector2D Move = (*iter).MoveDirect * 500.f * deltaTime;
        (*iter).Pos += Move;

        float Dist = Move.Length();
        (*iter).Distance -= Dist;

        if ((*iter).Distance <= 0.f)
        {
            iter = BulletList.erase(iter);
            iterEnd = BulletList.end();

            continue;
        }
        else if (((*iter).Pos.x - (*iter).Size.x / 2.f >= 1280.f ||
            (*iter).Pos.y - (*iter).Size.y / 2.f >= 720.f || 
            (*iter).Pos.x - (*iter).Size.x / 2.f <= 0.f || 
            (*iter).Pos.y - (*iter).Size.y / 2.f <= 0.f) &&
            (*iter).Option == EBulletOption::Normal)
        {
            iter = BulletList.erase(iter);
            iterEnd = BulletList.end();
            
            continue;
        }
        else if ((*iter).Option == EBulletOption::Bounce)
        {
            FVector2D Normal;

            // 벽 충돌 체크
            if ((*iter).Pos.x - (*iter).Size.x / 2.f <= 0.f)
            {
                Normal.x = 1.f;
                (*iter).Pos.x = 25.f;
            }
            else if ((*iter).Pos.x + (*iter).Size.x / 2.f >= 1280.f)
            {
                Normal.x = -1.f;
                (*iter).Pos.x = 1255.f;
            }
            else if ((*iter).Pos.y + (*iter).Size.y / 2.f >= 720.f)
            {
                Normal.y = -1.f;
                (*iter).Pos.y = 695.f;
            }
            else if ((*iter).Pos.y - (*iter).Size.y / 2.f <= 0.f)
            {
                Normal.y = 1.f;
                (*iter).Pos.y = 25.f;
            }

            if (Normal.Length() > 0.f)
            {
                // 바운스
                (*iter).MoveDirect = (*iter).MoveDirect - Normal * 2.f * Normal.Dot((*iter).MoveDirect);
                // 슬라이드
                //(*iter).MoveDirect = (*iter).MoveDirect - Normal * Normal.Dot((*iter).MoveDirect);
                //(*iter).MoveDirect = (*iter).MoveDirect - Normal * 0.3f* Normal.Dot((*iter).MoveDirect);
                (*iter).MoveDirect.Normalize();
            }
        }

        iter++;
    }
}

void CGameManager::Update(float deltaTime)
{
    PlayerBulletUpdate(mPlayerBulletList, deltaTime);

    EnemyMoveUpdate(deltaTime);
    EnemyAttackUpdate(mEnemyBulletList, deltaTime);
    EnemyBulletUpdate(mEnemyBulletList, deltaTime);
}

void CGameManager::PostUpdate(float deltaTime)
{
}

void CGameManager::Collision(float deltaTime)
{
}

void CGameManager::PostCollisionUpdate(float deltaTime)
{
}

void BulletRender(std::list<FRect> &Bullet, HDC &handleDC , float deltaTime)
{
    std::list<FRect>::iterator iter = Bullet.begin();
    std::list<FRect>::iterator iterEnd = Bullet.end();

    for (; iter != iterEnd; iter++)
    {
        Ellipse(handleDC, 
            (int)(*iter).Left, (int)(*iter).Top,
            (int)(*iter).Right, (int)(*iter).Bottom);
    }
}

void BulletRender(std::list<FBullet>& Bullet, HDC& handleDC, float deltaTime)
{
    std::list<FBullet>::iterator iter = Bullet.begin();
    std::list<FBullet>::iterator iterEnd = Bullet.end();

    for (; iter != iterEnd; iter++)
    {
        Ellipse(handleDC,
            (int)((*iter).Pos.x - (*iter).Size.x / 2.f), 
            (int)((*iter).Pos.y - (*iter).Size.y / 2.f),
            (int)((*iter).Pos.x + (*iter).Size.x / 2.f),
            (int)((*iter).Pos.y + (*iter).Size.y / 2.f));
    }
}

void CGameManager::Render(float deltaTime)
{
    //Rectangle(mHandleDC, 100, 200, 300, 400);
    //Rectangle(mHandleDC, mRect.left, mRect.top, mRect.right, mRect.bottom);
    Rectangle(mHandleDC, 
        (int)(mPlayerPos.x - mPlayerSize.x / 2.f), 
        (int)(mPlayerPos.y - mPlayerSize.y / 2.f), 
        (int)(mPlayerPos.x + mPlayerSize.x / 2.f), 
        (int)(mPlayerPos.y + mPlayerSize.y / 2.f));
    
    BulletRender(mPlayerBulletList, mHandleDC, deltaTime);

    Rectangle(mHandleDC,
        (int)(mEnemyPos.x - mEnemySize.x / 2.f),
        (int)(mEnemyPos.y - mEnemySize.y / 2.f),
        (int)(mEnemyPos.x + mEnemySize.x / 2.f),
        (int)(mEnemyPos.y + mEnemySize.y / 2.f));

    BulletRender(mEnemyBulletList, mHandleDC, deltaTime);
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
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            EndPaint(hWnd, &ps);
        }
    break;
    case WM_DESTROY:
        mLoop = false;
        PostQuitMessage(0);

        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return LRESULT();
}
