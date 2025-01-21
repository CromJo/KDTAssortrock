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
    // Asset Manager���� ����
    CSceneManager::DestroyInstance();
    
    CAssetManager::DestroyInstance();
    
    CShaderManager::DestroyInstance();

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

    // ����̽� �ʱ�ȭ
    if (!CDevice::GetInstance()->Init(mHandleWindow, 1280, 720, true))
        return false;

    if (!CShaderManager::GetInstance()->Init())
        return false;

    // ���� ������ �ʱ�ȭ
    if (!CAssetManager::GetInstance()->Init())
        return false;

    // Ÿ�̸� �ʱ�ȭ
    CTimer::Init();

    // �������� �ʱ�ȭ
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
    // CreateWindow : ������ â�� �������ִ� �Լ��̴�.
    // WinAPI���� �Լ���ڿ� W�� ������ �����ڵ�, A�� ������ ��Ƽ����Ʈ�̴�.
    // 1������ : ������ Ŭ���� �̸��� �����Ѵ�.
    // 2������ : ������ Ÿ��Ʋ�ٿ� ����� �̸��� �����Ѵ�.
    // 3������ : ������ â�� ����� �����Ѵ�.
    // 4������ : ȭ�鿡�� �����찡 ������ X������ �����Ѵ�.
    // 5������ : ȭ�鿡�� �����찡 ������ Y������ �����Ѵ�.
    // 6������ : ������ â�� ���� ũ�⸦ �����Ѵ�.
    // 7������ : ������ â�� ���� ũ�⸦ �����Ѵ�.
    // 8������ : �θ������찡 ���� ��� �θ��������� �ڵ��� �����Ѵ�.
    // 9������ : �޴� �ڵ��� �����Ѵ�.
    // 10������ : ������ �ν��Ͻ��� �����Ѵ�. WinMain���� ������ ������ �����ؾ� �Ѵ�.
    // 11������ : â ���� �����͸� �����Ѵ�. WM_CREATE�� ������ ������ �߻��ϴ� �޼����ε�
    // �� �޼����� �߻��ϸ� WndProc �Լ��� lParam�� �� ���� ���޵ȴ�.
    // �̷��� �����츦 �����ϸ� ������ �ڵ��� ������ش�.
    // �߸��� ������ ��� 0�� ��ȯ�Ѵ�.
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
    case WM_DESTROY:
        mLoop = false;
        PostQuitMessage(0);

        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}
