#include "GameManager.h"
#include "resource.h"
#include "Share/Timer.h"
#include "Device.h"
#include "Asset/AssetManager.h"

DEFINITION_SINGLE(CGameManager)

bool CGameManager::mLoop = true;

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
	CAssetManager::DestroyInstance();

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

	// 매개변수에 들어간 윈도우에 출력할 수 있는 DC가
	// 만들어진다.
	// GetDC로 얻어온 DC의 경우 반드시 소멸자에서 해제
	// 시켜줘야한다.
	mHandleDC = GetDC(mHandleWindow);

	// 디바이스 초기화
	if(!CDevice::GetInstance()->Init(mHandleWindow, 1280, 720, true))
		return false;
	 
	// 에셋매니저 초기화
	if (!CAssetManager::GetInstance()->Init())
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
		{
			// 키보드 입력 메세지 발생 시 동작한다.
			// WM_KEYDOWN, WM_KEYUP 등 메세지 발생하면 문자일 경우
			// WM_CHAR 메세지를 하나더 만들어주는 역할.
			TranslateMessage(&msg);

			// 메세지를 WndProc로 전달한다.
			DispatchMessage(&msg);
		}
		// 윈도우 데드타임일 경우 동작.
		// (메세지 큐에 메세지가 없는 경우 동작)
		else
		{
			Logic();
		}
	}

	return (int)msg.wParam; 
}

void CGameManager::Logic()
{
	// 시간 흐르는 기능 
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
		충돌 (두 도형의 교집합 찾기)
		1. A의 Left는 B의 Right보다 커야한다.
		2. B의 Left는 A의 Right보다 작아야한다.
		3. A의 Top은 B의 Bottom보다 작거나 같아야한다.
		4. B의 Top은 A의 Bottom보다 작거나 같아야한다.
	*/
}

void CGameManager::PostCollision(float DeltaTime)
{
	/*
		Mesh 종류)
			1. Animation이 동작하지 않는 Static Mesh
				정적 메쉬라고도 불린다.
				Ex) 벽, 키보드, 마우스 등
			2. Mesh가 Skeleton정보를 가지고 있으면서,
				Animation이 동작되는 Mesh를,
				Animation Mesh라고 한다.

			요약) 기하정보만 가진 Static Mesh와
				기하정보 및 뼈대를 가진 Animation Mesh가 있다.
	*/


}

void CGameManager::Render(float DeltaTime)
{
	CDevice::GetInstance()->ClearBackBuffer(mClearColor);
	CDevice::GetInstance()->ClearDepthStencil(1.f, 0);
	CDevice::GetInstance()->SetTarget();

	// 출력 끝난 후 Page Flipping을 한번 해준다.
	CDevice::GetInstance()->Render();

	/*
		- 6면체를 구성하는 점을 3D에서 Vertex라고 한다.
		- 점들을 연결해서 면을 만드는데 보통 삼각형으로
			표현한다.
			이를 Polygon이라고 부른다.
		- Vertex(정점)가 3개 모여서 Polygon을 만든다.
		- DirectX는 정점 정보를 저장하는 
			Vertex Buffer를 제공한다.
		- Vertex 배열의 Index정보를 저장하고 있는
			Index Buffer가 있다.
		- Index Buffer를 이용해서 삼각형들을 만든다.
		
		요약 :
			Vertex Buffer와 Index Buffer로 도형을 만든다.

	*/
}

void CGameManager::RegisterWindowClass()
{
	WNDCLASSEXW wcex;

	// 윈도우 클래스 구조체의 크기를 나타낸다. 반드시 지정해야함.
	wcex.cbSize = sizeof(WNDCLASSEX);
	
	// 클라이언트 영역 : 화면에 출력가능한 영역
	// 클라이언트 영역의 가로/세로가 변경될 시 전부 다시 그려준다.
	wcex.style = CS_HREDRAW | CS_VREDRAW;

	// 메세지큐에서 얻어온 메세지를 인자로 넣어서 호출해줄 함수의 주소를 넘긴다.
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;

	// 운영체제에서 부여해준 HINSTANCE를 전달한다.
	wcex.hInstance = mHandleInstance;

	// 실행파일 아이콘 지정
	wcex.hIcon = LoadIcon(mHandleInstance, MAKEINTRESOURCE(IDI_ICON1));

	// 윈도우 창에서 커서 모양을 나타낸다.
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);

	// 클라이언트 영역의 색상을 지정한다.
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	// 윈도우 메뉴를 지정.
	// wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_asdasdas);
	// 0 대입 시 메뉴를 없앤다.
	wcex.lpszMenuName = 0;

	// 등록할 윈도우 클래스의 이름을 지정
	wcex.lpszClassName = mClassName;

	// 윈도우창 좌측 상단의 작은 아이콘을 지정한다.
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	// 위에서 설정한 윈도우 클래스를 등록한다.
	RegisterClassExW(&wcex);
}

bool CGameManager::Create()
{
	/*
		CreateWindow : 윈도우 창 생성 함수
		WinAPI에서 함수명뒤에 
		W : Unicode, 
		A : MultiByte
		를 의미한다.

		1번인자  : 윈도우 클래스 이름을 지정.
		2번인자  : 윈도우 타이틀바 출력할 이름 지정.
		3번인자  : 윈도우 창 모양 결정
		4번인자  : 화면에서 윈도우가 시작할 X지점
		5번인자  : 화면에서 윈도우가 시작할 Y지점
		6번인자  : 윈도우 창의 가로 크기를 지정. 
		7번인자  : 윈도우 창의 세로 크기를 지정.
		8번인자  : 부모 윈도우가 있을 경우 부모 윈도우의 핸들 지정.
		9번인자  : 메뉴 핸들을 전달.
		10번인자	: 윈도우 인스턴스 전달. WinMain에서 전달은 값으로 해야한다.
		11번인자	: 창 생성 데이터 지정. WM_CREATE는 윈도우 생성시 발생하는 메세지인데,
				이 메세지가 발생 하면 WndProc 함수의 lParam에 11번 인자 값이 전달된다.

		이렇게 윈도우 생성 시 윈도우 핸들을 만들어준다.
		잘못 만들면 0을 반환한다.
	*/
	mHandleWindow = CreateWindowW(mClassName, mTitleName, WS_OVERLAPPEDWINDOW,
		200, 100, 1280, 720, nullptr, nullptr, mHandleInstance, nullptr);

	if (!mHandleWindow)
		return false;

	// 윈도우 클라이언트 영역의 크기를 원하는 크기로 지정
	// 위에서 지정한 윈도우 크기는 타이틀바 등 창의 모든 부위가
	// 합쳐진 크기로 지정된다.
	RECT WindowRC = { 0, 0, 1280, 720 };

	// 클라 영역 1280, 720이 되기 위한 윈도우 전체크기를 받아온다.
	// (ThickFrame, Menu, TitleBar 등이 포함된 전체크기)
	AdjustWindowRect(&WindowRC, WS_OVERLAPPEDWINDOW, FALSE);

	// 오른쪽 - 왼쪽 = 가로 크기
	// 아래	- 위 = 세로 크기
	SetWindowPos(mHandleWindow, HWND_TOPMOST, 400, 100, WindowRC.right - WindowRC.left,
		WindowRC.bottom - WindowRC.top, SWP_NOMOVE | SWP_NOZORDER);
	

	// 위에서 윈도우 창 만들었다면 ShowWIndow 함수를 이용해 창을 보여줄지 숨길지 결정.
	ShowWindow(mHandleWindow, SW_SHOW);

	// 클라이언트 영역을 강제로 다시 그리게 요청해주는 함수.
	// 처음 생성시나 특정상황에 창을 새로고침 해야 할 경우 사용.
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
		// 위에서 지정한 메세지 외 다른 메세지 발생 시 윈도우 기본 동작으로 처리.
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
