#include "GameManager.h"
#include "resource.h"
#include "Share/Timer.h"

DEFINITION_SINGLE(CGameManager)

bool CGameManager::mLoop = true;

CGameManager::CGameManager()
{

}

CGameManager::~CGameManager()
{
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

void CGameManager::Input(float deltaTime)
{
    // ���� Ű abc,123 ��... (���� 1������ �빮�ڷ� ��밡��)
    if (GetAsyncKeyState('W') & 0x8000)
    {
        mRect.Top -= 400 * deltaTime;
        mRect.Bottom -= 400 * deltaTime;
    }
    if (GetAsyncKeyState('S') & 0x8000)
    {
        mRect.Top += 400 * deltaTime;
        mRect.Bottom += 400 * deltaTime;
    }
    if (GetAsyncKeyState('A') & 0x8000)
    {
        mRect.Left -= 400 * deltaTime;
        mRect.Right -= 400 * deltaTime;
    }
    if (GetAsyncKeyState('D') & 0x8000)
    {
        mRect.Left += 400 * deltaTime;
        mRect.Right += 400 * deltaTime;
    }

    // Ư�� Ű (Space, Enter ��)
    if (GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        FRect Bullet;

        Bullet.Left = mRect.Left + 100.f;
        Bullet.Top = mRect.Top + 25.f;
        Bullet.Right = Bullet.Left + 50.f;
        Bullet.Bottom = Bullet.Top + 50.f;

        mBulletList.push_back(Bullet);
    }
}

FRect Enemy = { 1000, 100, 1100, 200 };
std::list<FRect> mEnemyBulletList;
bool Top = true;
float attack = 0;

void EnemyMoveUpdate(float deltaTime)
{
    if (Top)
    {
        // Top�� 0���� �۾����ٴ� ���� ��� ȭ���� �Ѿ�ٴ� ��.
        if(Enemy.Top <= 0)
        {
            Top = false;
        }
        Enemy.Top -= 600 * deltaTime;
        Enemy.Bottom -= 600 * deltaTime;
    }
    else
    {
        // Bottom�� 720���� Ŀ���ٴ� ����, �ϴ� ȭ���� �Ѿ�ٴ� ��.
        if (Enemy.Bottom >= 720)
        {
            Top = true;
        }
        Enemy.Top += 600 * deltaTime;
        Enemy.Bottom += 600 * deltaTime;
    }
}

void EnemyAttackUpdate(std::list<FRect>& BulletList, float deltaTime)
{
    // N�ʴ� 1�� ����
    attack += deltaTime;

    if (attack > 1.f)
    {
        attack = 0.f;

        FRect Bullet;

        Bullet.Left = Enemy.Left - 100.f;
        Bullet.Top = Enemy.Top + 25.f;
        Bullet.Right = Bullet.Left + 50.f;
        Bullet.Bottom = Bullet.Top + 50.f;

        BulletList.push_back(Bullet);
    }
}

void EnemyBulletUpdate(std::list<FRect>& BulletList, float deltaTime)
{
    std::list<FRect>::iterator iter = BulletList.begin();
    std::list<FRect>::iterator iterEnd = BulletList.end();

    for (; iter != iterEnd; iter++)
    {
        (*iter).Left -= 500.f * deltaTime;
        (*iter).Right -= 500.f * deltaTime;
    }
}


void PlayerUpdate(std::list<FRect> &BulletList, float deltaTime)
{
    std::list<FRect>::iterator iter = BulletList.begin();
    std::list<FRect>::iterator iterEnd = BulletList.end();

    for (; iter != iterEnd; iter++)
    {
        (*iter).Left += 500.f * deltaTime;
        (*iter).Right += 500.f * deltaTime;
    }
}

void CGameManager::Update(float deltaTime)
{
    PlayerUpdate(mBulletList, deltaTime);

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
        Ellipse(handleDC, (int)(*iter).Left, (int)(*iter).Top,
            (int)(*iter).Right, (int)(*iter).Bottom);
    }
}

void CGameManager::Render(float deltaTime)
{
    //Rectangle(mHandleDC, 100, 200, 300, 400);
    //Rectangle(mHandleDC, mRect.left, mRect.top, mRect.right, mRect.bottom);
    Rectangle(mHandleDC, (int)mRect.Left, (int)mRect.Top, (int)mRect.Right, (int)mRect.Bottom);
    
    BulletRender(mBulletList, mHandleDC, deltaTime);

    Rectangle(mHandleDC, (int)Enemy.Left, (int)Enemy.Top, (int)Enemy.Right, (int)Enemy.Bottom);

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
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
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
