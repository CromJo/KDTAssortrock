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

DEFINITION_SINGLE(CGameManager)

bool CGameManager::mLoop = true;

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
	CAssetManager::DestroyInstance();

	CShaderManager::DestroyInstance();

	CDevice::DestroyInstance();

	ReleaseDC(mHandleWindow, mHandleDC);
}

bool CGameManager::Init(HINSTANCE hInstance)
{
	mHandleInstance = hInstance;

	lstrcpy(mClassName, TEXT("ClassName"));
	lstrcpy(mTitleName, TEXT("TitleName"));
	
	RegisterWindowClass();

 	if (!Create())
		return false;

	// �Ű������� �� �����쿡 ����� �� �ִ� DC��
	// ���������.
	// GetDC�� ���� DC�� ��� �ݵ�� �Ҹ��ڿ��� ����
	// ��������Ѵ�.
	mHandleDC = GetDC(mHandleWindow);

	// ����̽� �ʱ�ȭ
	if(!CDevice::GetInstance()->Init(mHandleWindow, 1280, 720, true))
		return false;
	
	// Shader �Ŵ��� �ʱ�ȭ
	if(!CShaderManager::GetInstance()->Init())
		return false;
	
	// ���¸Ŵ��� �ʱ�ȭ
	if (!CAssetManager::GetInstance()->Init())
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
		{
			// Ű���� �Է� �޼��� �߻� �� �����Ѵ�.
			// WM_KEYDOWN, WM_KEYUP �� �޼��� �߻��ϸ� ������ ���
			// WM_CHAR �޼����� �ϳ��� ������ִ� ����.
			TranslateMessage(&msg);

			// �޼����� WndProc�� �����Ѵ�.
			DispatchMessage(&msg);
		}
		// ������ ����Ÿ���� ��� ����.
		// (�޼��� ť�� �޼����� ���� ��� ����)
		else
		{
			Logic();
		}
	}

	return (int)msg.wParam; 
}

void CGameManager::Logic()
{
	// �ð� �帣�� ��� 
	float DeltaTime = CTimer::Update();

	Input(DeltaTime);
	Update(DeltaTime);
	PostUpdate(DeltaTime);
	Collision(DeltaTime);
	PostCollision (DeltaTime);
	Render(DeltaTime);
	//PostRender(DeltaTime);
}

void CGameManager::Input(float DeltaTime)
{
}

void CGameManager::Update(float DeltaTime)
{
}

void CGameManager::PostUpdate(float DeltaTime)
{
}

void CGameManager::Collision(float DeltaTime)
{ 
	/*
		�浹 (�� ������ ������ ã��)
		1. A�� Left�� B�� Right���� Ŀ���Ѵ�.
		2. B�� Left�� A�� Right���� �۾ƾ��Ѵ�.
		3. A�� Top�� B�� Bottom���� �۰ų� ���ƾ��Ѵ�.
		4. B�� Top�� A�� Bottom���� �۰ų� ���ƾ��Ѵ�.
	*/
}

void CGameManager::PostCollision(float DeltaTime)
{
	/*
		Mesh ����)
			1. Animation�� �������� �ʴ� Static Mesh
				���� �޽���� �Ҹ���.
				Ex) ��, Ű����, ���콺 ��
			2. Mesh�� Skeleton������ ������ �����鼭,
				Animation�� ���۵Ǵ� Mesh��,
				Animation Mesh��� �Ѵ�.

			���) ���������� ���� Static Mesh��
				�������� �� ���븦 ���� Animation Mesh�� �ִ�.
	*/
}

void CGameManager::Render(float DeltaTime)
{
	CDevice::GetInstance()->ClearBackBuffer(mClearColor);
	CDevice::GetInstance()->ClearDepthStencil(1.f, 0);
	CDevice::GetInstance()->SetTarget();

	// ���
	static CTransformCBuffer buffer;

	buffer.Init();

	FMatrix matrixWorld, matrixProjection;
	FMatrix matrixScale, matrixRotation, matrixTranslate;

	matrixScale.Scaling(5.f, 5.f, 1.f);
	matrixRotation.Rotation(0.f, 0.f, 0.f);
	matrixTranslate.Translation(2.f, 0.5f, 5.f);

	// ���� : ũ�� * ���� * �̵� * ���� * �θ�
	matrixWorld = matrixScale * matrixRotation * matrixTranslate;
	matrixProjection = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(90.f),
		/*���μ��� ����*/ 1280.f / 720.f,
		/*ī�޶� ��� ��/��Ÿ� ����*/ 0.5f, 1000.f);

	buffer.SetWorldMatrix(matrixWorld);
	buffer.SetProjectionMatrix(matrixProjection);

	buffer.UpdateBuffer();

	CSharedPointer<CShader> Shader = CShaderManager::GetInstance()->FindShader("ColorMeshShader");
	CSharedPointer<CMesh> Mesh = CAssetManager::GetInstance()->GetMeshManager()->FindMesh("CenterRect");

	Shader->SetShader();
	Mesh->Render();

	// ��� ���� �� Page Flipping�� �ѹ� ���ش�.
	CDevice::GetInstance()->Render();

	/*
		- 6��ü�� �����ϴ� ���� 3D���� Vertex��� �Ѵ�.
		- ������ �����ؼ� ���� ����µ� ���� �ﰢ������
			ǥ���Ѵ�.
			�̸� Polygon�̶�� �θ���.
		- Vertex(����)�� 3�� �𿩼� Polygon�� �����.
		- DirectX�� ���� ������ �����ϴ� 
			Vertex Buffer�� �����Ѵ�.
		- Vertex �迭�� Index������ �����ϰ� �ִ�
			Index Buffer�� �ִ�.
		- Index Buffer�� �̿��ؼ� �ﰢ������ �����.
		
		��� :
			Vertex Buffer�� Index Buffer�� ������ �����.

	*/
}

void CGameManager::RegisterWindowClass()
{
	WNDCLASSEXW wcex;

	// ������ Ŭ���� ����ü�� ũ�⸦ ��Ÿ����. �ݵ�� �����ؾ���.
	wcex.cbSize = sizeof(WNDCLASSEX);
	
	// Ŭ���̾�Ʈ ���� : ȭ�鿡 ��°����� ����
	// Ŭ���̾�Ʈ ������ ����/���ΰ� ����� �� ���� �ٽ� �׷��ش�.
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	// �޼���ť���� ���� �޼����� ���ڷ� �־ ȣ������ �Լ��� �ּҸ� �ѱ��.
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	// �ü������ �ο����� HINSTANCE�� �����Ѵ�.
	wcex.hInstance = mHandleInstance;

	// �������� ������ ����
	wcex.hIcon = LoadIcon(mHandleInstance, MAKEINTRESOURCE(IDI_ICON1));

	// ������ â���� Ŀ�� ����� ��Ÿ����.
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

	// Ŭ���̾�Ʈ ������ ������ �����Ѵ�.
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	// ������ �޴��� ����.
	// wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_asdasdas);
	// 0 ���� �� �޴��� ���ش�.
	wcex.lpszMenuName = 0;

	// ����� ������ Ŭ������ �̸��� ����
	wcex.lpszClassName = mClassName;

	// ������â ���� ����� ���� �������� �����Ѵ�.
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	// ������ ������ ������ Ŭ������ ����Ѵ�.
	RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
	/*
		CreateWindow : ������ â ���� �Լ�
		WinAPI���� �Լ���ڿ� 
		W : Unicode, 
		A : MultiByte
		�� �ǹ��Ѵ�.

		1������  : ������ Ŭ���� �̸��� ����.
		2������  : ������ Ÿ��Ʋ�� ����� �̸� ����.
		3������  : ������ â ��� ����
		4������  : ȭ�鿡�� �����찡 ������ X����
		5������  : ȭ�鿡�� �����찡 ������ Y����
		6������  : ������ â�� ���� ũ�⸦ ����. 
		7������  : ������ â�� ���� ũ�⸦ ����.
		8������  : �θ� �����찡 ���� ��� �θ� �������� �ڵ� ����.
		9������  : �޴� �ڵ��� ����.
		10������	: ������ �ν��Ͻ� ����. WinMain���� ������ ������ �ؾ��Ѵ�.
		11������	: â ���� ������ ����. WM_CREATE�� ������ ������ �߻��ϴ� �޼����ε�,
				�� �޼����� �߻� �ϸ� WndProc �Լ��� lParam�� 11�� ���� ���� ���޵ȴ�.

		�̷��� ������ ���� �� ������ �ڵ��� ������ش�.
		�߸� ����� 0�� ��ȯ�Ѵ�.
	*/
	mHandleWindow = CreateWindowW(mClassName, mTitleName, WS_OVERLAPPEDWINDOW,
		200, 100, 1280, 720, nullptr, nullptr, mHandleInstance, nullptr);

	if (!mHandleWindow)
		return false;

	// ������ Ŭ���̾�Ʈ ������ ũ�⸦ ���ϴ� ũ��� ����
	// ������ ������ ������ ũ��� Ÿ��Ʋ�� �� â�� ��� ������
	// ������ ũ��� �����ȴ�.
	RECT WindowRC = { 0, 0, 1280, 720 };

	// Ŭ�� ���� 1280, 720�� �Ǳ� ���� ������ ��üũ�⸦ �޾ƿ´�.
	// (ThickFrame, Menu, TitleBar ���� ���Ե� ��üũ��)
	AdjustWindowRect(&WindowRC, WS_OVERLAPPEDWINDOW, FALSE);

	// ������ - ���� = ���� ũ��
	// �Ʒ�	- �� = ���� ũ��
	SetWindowPos(mHandleWindow, HWND_TOPMOST, 400, 100, WindowRC.right - WindowRC.left,
		WindowRC.bottom - WindowRC.top, SWP_NOMOVE | SWP_NOZORDER);
	

	// ������ ������ â ������ٸ� ShowWIndow �Լ��� �̿��� â�� �������� ������ ����.
	ShowWindow(mHandleWindow, SW_SHOW);

	// Ŭ���̾�Ʈ ������ ������ �ٽ� �׸��� ��û���ִ� �Լ�.
	// ó�� �����ó� Ư����Ȳ�� â�� ���ΰ�ħ �ؾ� �� ��� ���.
	UpdateWindow(mHandleWindow);

	//return true;
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
		// ������ ������ �޼��� �� �ٸ� �޼��� �߻� �� ������ �⺻ �������� ó��.
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
