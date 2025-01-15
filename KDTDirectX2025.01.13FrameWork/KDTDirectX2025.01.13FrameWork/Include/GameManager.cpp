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

    // Device Context ����
    ReleaseDC(mHandleWindow, mHandleDC);
}

bool CGameManager::Init(HINSTANCE hInst)
{
	mHandleInstance = hInst;

	// Unicode�� strcpy�Լ�
	// TEXT : define������� Unicode�� ""�տ� L�� �ٿ� ����ؾ�������,
	//		L�� �Ⱥ��̰� ����ϱ� ���� ������ ��ó����
	lstrcpy(mClassName, TEXT("KDTDirectX20250113FrameWork"));
	lstrcpy(mTitleName, TEXT("KDTDirectX20250113FrameWork"));

	RegisterWindowClass();

    if (!Create())
        return false;

    // ���ڷ� �� �����쿡 ����� �� �ִ� DC�� ���������.
    mHandleDC = GetDC(mHandleWindow);

    if (!CDevice::GetInstance()->Init(mHandleWindow, 1280, 720, true))
        return false;

    // Ÿ�̸� �ʱ�ȭ
    CTimer::Init();

	return true;
}

int CGameManager::Run()
{
    MSG msg;

    while (mLoop)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
            // Accelerator�� �����Ѵ�. (���� : ���� ��)
            //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            // TranslateMessage : Ű���� �Է� �޼��� �߻� �� ����ȴ�.
            //      WM_KEYDOWN, WM_KEYUP �� �޼����� �߻��ϸ� ������ ���, 
            //      WM_CHAR �޼����� �ϳ� �� ������ش�.
            TranslateMessage(&msg);

            // DispatchMessage : �޼����� WndProc���� �������ش�.
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

    // ���� Ű abc,123 ��... (���� 1������ �빮�ڷ� ��밡��)
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
    // Ư�� Ű (Space, Enter ��)
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
        // Top�� 0���� �۾����ٴ� ���� ��� ȭ���� �Ѿ�ٴ� ��.
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
        // Bottom�� 720���� Ŀ���ٴ� ����, �ϴ� ȭ���� �Ѿ�ٴ� ��.
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
    // N�ʴ� 1�� ����
    mAttackSpeed += deltaTime;

    if (mAttackSpeed > 1.f)
    {
        //mAttackSpeed = 0.f  �̷������� �ҽ� �Ҽ��� ������ �ҽǵǾ� �ᱹ �յ����� ���ϰ� �ȴ�+.
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

            // �� �浹 üũ
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
                // �ٿ
                (*iter).MoveDirect = (*iter).MoveDirect - Normal * 2.f * Normal.Dot((*iter).MoveDirect);
                // �����̵�
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

    // ������Ŭ���� ����ü�� ũ�⸦ ��Ÿ����.
    // �ݵ�� �����Ǿ�� �Ѵ�.
    wcex.cbSize = sizeof(WNDCLASSEX);

    // Ŭ���̾�Ʈ ���� : Windowâ Ʋ ���� ��� ������ ��� �κ�.
    // Ŭ�� ������ ũ��(����/����)�� ����� �� ���� �ٽ� �׸���.
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    // �޼���ť���� ���� �޼����� ���ڷ� �־ ȣ������ �Լ��� �ּҸ� �Ѱ��ش�.
    wcex.lpfnWndProc = WndProc;
    // Cls | Wnd Extra : ����� �޼��� (���� ����)
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    // �ü������ �ο����� HInstance�� �����Ѵ�.
    wcex.hInstance = mHandleInstance;
    // Icon : �������� �������� �����Ѵ�.
    // �Ӽ�->�ϹݼӼ�->��� �̸��� _Debug�� �Ⱥ��̴� ������ ��� �� �׷��� ���庸��.
    wcex.hIcon = LoadIcon(mHandleInstance, MAKEINTRESOURCE(IDI_ICON1));
    // Cursor : ������ ���α׷� �� â������ Ŀ�� ����� ��Ÿ����.
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    // Ŭ���̾�Ʈ ������ ������ �����Ѵ�.
    // 1 : Ⱥ�� | 2 : ȸ�� | 3 : ������
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    // MenuName : ������ �޴��� �����Ѵ�.
    // 0�� �־��� �� �޴�â�� �������.
    wcex.lpszMenuName = 0;
    // ClassName : ����� ������Ŭ������ �̸��� �����Ѵ�.
    wcex.lpszClassName = mClassName;
    // IconSm : ���� �ֻ���� Small Icon�� �����Ѵ�.
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    // ������ ������ ������ Ŭ������ ����Ѵ�.
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

    // ������ Ŭ�� ������ ũ�⸦ ���ϴ� ũ��� ����.
    // ������ ������ ������ ũ��� Ÿ��Ʋ�� ���� ũ�Ⱑ ��� ������ ũ��� ����.
    RECT WindowRect = { 0, 0, 1280, 720 };

    // Ŭ�� ������ 1280, 720�� �Ǳ� ���� �ʿ��� ������ ��ü ũ�⸦ ���´�.
    // (ThickFrame, Menu, TitleBar ���� ���Ե� ��üũ��)
    AdjustWindowRect(&WindowRect, WS_OVERLAPPEDWINDOW, FALSE);

    SetWindowPos(mHandleWindow, HWND_TOPMOST, 100, 100, 
        WindowRect.right - WindowRect.left, 
        WindowRect.bottom - WindowRect.top, 
        SWP_NOMOVE | SWP_NOZORDER);

    // ShowWindow : â�� ����� �� ������ �����Ѵ�.
    ShowWindow(mHandleWindow, SW_SHOW);
    // UpdateWindow : Ŭ���̾�Ʈ ������ ������ �ٽ� ũ���� ��û���ش�.
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
