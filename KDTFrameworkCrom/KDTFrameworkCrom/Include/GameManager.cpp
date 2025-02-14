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
	FVector2D PlayerMoveDirect;

	// 키 입력 기능 추가
	if (GetAsyncKeyState('W') & 0x8000)
	{
		//mRC.Top		-= 400 * DeltaTime;
		//mRC.Bottom	-= 400 * DeltaTime;
		
		PlayerMoveDirect.y -= 1.f;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{/*
		mRC.Top		+= 400 * DeltaTime;
		mRC.Bottom	+= 400 * DeltaTime;*/
	
		PlayerMoveDirect.y += 1.f;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{/*
		mRC.Left	-= 400 * DeltaTime;
		mRC.Right	-= 400 * DeltaTime;*/

		PlayerMoveDirect.x -= 1.f;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{/*
		mRC.Left	+= 400 * DeltaTime;
		mRC.Right	+= 400 * DeltaTime;*/

		PlayerMoveDirect.x += 1.f;
	}
	// 대각선 3개의 총알 발사 기능
	// 1. x는 +방향이 고정되어있음 (오른쪽으로만 공격한다는 가정하에)
	// 2. y는 -1, 0, 1이 되어야한다. 
	if (GetAsyncKeyState('1') & 0x8000)
	{
		for (int i = 0; i < 3; ++i)
		{
			FBullet Bullet;

			Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
			Bullet.Pos.y = mPlayerPos.y;

			Bullet.Size = FVector2D(50.f, 50.f);
			// 타겟 중앙 포지션 값 - 총알의 중앙포지션 값 = 타겟 방향의 총알 벡터값
			// 3방향 위, 중앙, 아래로 오른쪽 방향을 향해 가야하니 
			// 코드를 균일하게 하기 위해 i (0 - 1) (1 - 0) (2 - 1)한 값을 넣어준다.
			// 그러면 -1, 0, 1이나오게 되고,
			// WINAPI에서는 y의 -1은 위, 
			// 0은 현재 y위치 고정, 
			// 1은 아래를 의미하므로 3방향으로 발사되게 된다.
			Bullet.MoveDirect = FVector2D(1.f, i - 1.f);
			Bullet.MoveDirect.Normalize();
			
			Bullet.Distance = 600.f;

			mBulletList.push_back(Bullet);
		}
	}
	
	// 8방향 총알 발사 기능
	if (GetAsyncKeyState('2') & 0x8000)
	{
		FVector2D Direct[8] =
		{	// 방향			// 넘패드 기준
			{1.f, 0.f},		// 6
			{1.f, 1.f},		// 3
			{0.f, 1.f},		// 2
			{-1.f, 1.f},		// 1
			{-1.f, 0.f},		// 4
			{-1.f,-1.f},		// 7
			{0.f, -1.f},		// 8
			{1.f, -1.f},		// 9
		};

		for (int i = 0; i < 8; ++i)
		{
			FBullet Bullet;

			// 여기 위치에서 PlayerPos를 넣어주면 
			// 플레이어의 몸에서 총알이 8방향으로 발사하게 된다.
			//Bullet.Pos = mPlayerPos;

			Bullet.Size = FVector2D(50.f, 50.f);
			// 타겟 중앙 포지션 값 - 총알의 중앙포지션 값 = 타겟 방향의 총알 벡터값
			// 3방향 위, 중앙, 아래로 오른쪽 방향을 향해 가야하니 
			// 코드를 균일하게 하기 위해 i (0 - 1) (1 - 0) (2 - 1)한 값을 넣어준다.
			// 그러면 -1, 0, 1이나오게 되고,
			// WINAPI에서는 y의 -1은 위, 
			// 0은 현재 y위치 고정, 
			// 1은 아래를 의미하므로 3방향으로 발사되게 된다.
			Bullet.MoveDirect = Direct[i];
			Bullet.MoveDirect.Normalize();
			
			// 여기서는 Bullet의 MoveDirect값이 결정된 상태이기 때문에,
			// MoveDirect에서 특정 범위만큼 띄워놓을 위치를 지정해준다 (곱한다)
			Bullet.Pos = mPlayerPos + Bullet.MoveDirect * 100.f;

			Bullet.Distance = 600.f;

			mBulletList.push_back(Bullet);
		}
	}

	if (GetAsyncKeyState('3') & 0x8000)
	{
		FBullet Bullet;

		Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
		Bullet.Pos.y = mPlayerPos.y;

		Bullet.Size = FVector2D(50.f, 50.f);
		// 타겟 중앙 포지션 값 - 총알의 중앙포지션 값 = 타겟 방향의 총알 벡터값
		// x값만 변경시 : 1 frame마다 +1씩 x축으로 이동
		// y값만 변경시 : 1 frame마다 +1씩 y축으로 이동
		Bullet.MoveDirect = FVector2D(1.f, -1.f);
		Bullet.MoveDirect.Normalize();

		// float타입으로 표현할 수 있는 최댓값
		Bullet.Distance = FLT_MAX;
		Bullet.Option = EBulletOption::Bounce;


		mBulletList.push_back(Bullet);
	}

	// 대각선 이동 정규화시켜서 속도를 일정하게 맞춤.
	PlayerMoveDirect.Normalize();

	mPlayerPos += PlayerMoveDirect * 400.f * DeltaTime;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		FBullet Bullet;

		Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
		Bullet.Pos.y = mPlayerPos.y;

		Bullet.Size = FVector2D(50.f, 50.f);
		// 타겟 중앙 포지션 값 - 총알의 중앙포지션 값 = 타겟 방향의 총알 벡터값
		// x값만 변경시 : 1 frame마다 +1씩 x축으로 이동
		// y값만 변경시 : 1 frame마다 +1씩 y축으로 이동
		Bullet.MoveDirect = FVector2D(1.f, 0.f);
		Bullet.MoveDirect.Normalize();

		Bullet.Distance = 600.f;

		mBulletList.push_back(Bullet);
	}
}

void CGameManager::Update(float DeltaTime)
{
	std::list<FBullet>::iterator iter = mBulletList.begin();
	std::list<FBullet>::iterator iterEnd = mBulletList.end();

	// 플레이어의 총알리스트
	for (; iter != iterEnd;)
	{
		// 무브 벡터의 크기는 곧 이동거리를 의미한다.
		FVector2D Move = (*iter).MoveDirect * 500.f * DeltaTime;

		(*iter).Pos += Move;
	
		float Distance = Move.Length();

		(*iter).Distance -= Distance;

		if ((*iter).Distance <= 0.f)
		{
			iter = mBulletList.erase(iter);
			iterEnd = mBulletList.end();
			continue;
		}
		// stl list 또는 stl vector 또는 map을 쓰면
		// list, vector에서 제거를 하면 erase함수를 사용
		// erase를 사용하면, 그 node를 제거하고 
		// 다음노드의 iterator를 반환해준다.
		// 이런 특성으로 인해 end가 변경될 수 있음.
		else if (((*iter).Pos.x + (*iter).Size.x / 2.f <= 0.f ||
			(*iter).Pos.y + (*iter).Size.y / 2.f <= 0.f ||
			(*iter).Pos.y - (*iter).Size.y / 2.f >= 720.f ||
			(*iter).Pos.x - (*iter).Size.x / 2.f >= 1280.f) &&
			(*iter).Option == EBulletOption::Normal)
		{
			// 여기서 제거를 하게 되면 ++iter가 되는 순간,
			// 제거된 다음 칸의 iterator는 생략되고 그 다음칸부터
			// for문이 실행된다.
			// 즉 제거기능이 일어나면 2칸이동이 된다고 볼 수 있다.
			// 그렇기에 for문에 있는 ++iter를 for문 최하단에 추가해준다.
			iter = mBulletList.erase(iter);
			iterEnd = mBulletList.end();

			// if문이 실행되면 iterator의 제거가 이루어지고 ++iter를 함으로써,
			// 2칸 이동이 되어서는 안되기 떄문에 continue로 for문을 다시 돌게한다.
			continue;
		}
		else if ((*iter).Option == EBulletOption::Bounce)
		{
			FVector2D Normal;

			// 벽에 부딪혔는지 판단한다.
			if ((*iter).Pos.x - (*iter).Size.x / 2.f <= 0.f)
			{
				Normal.x = 1.f;
				// 총알의 크기가 50이니 절반인 25가 닿는다는 것은
				// 총알 크기(중앙)를 기준으로 넣은 데이터이다.
				// 딱맞게 x축 왼쪽벽에 닿음을 인지하는 기준이 된다.
				(*iter).Pos.x = 25.f;
			}
			else if ((*iter).Pos.x + (*iter).Size.x / 2.f >= 1280.f)
			{
				Normal.x = -1.f;
				(*iter).Pos.x = 1255.f;
			}
			// 벽에 부딪혔는지 판단한다.
			else if ((*iter).Pos.y - (*iter).Size.y / 2.f <= 0.f)
			{
				Normal.y = 1.f;
				// 총알의 크기가 50이니 절반인 25가 닿는다는 것은
				// 총알 크기(중앙)를 기준으로 넣은 데이터이다.
				// 딱맞게 x축 왼쪽벽에 닿음을 인지하는 기준이 된다.
				(*iter).Pos.y = 25.f;
			}
			else if ((*iter).Pos.y + (*iter).Size.y / 2.f >= 720.f)
			{
				Normal.y = -1.f;
				(*iter).Pos.y = 695.f;
			}

			// 바운스 기능
			if (Normal.Length() > 0.f)
			{
				(*iter).MoveDirect = (*iter).MoveDirect - Normal * 2.f * Normal.Dot((*iter).MoveDirect);
				(*iter).MoveDirect.Normalize();
			}
		}

		++iter;
	}

	// 적 이동
	mEnemyPos.y += mEnemyDirect * 300.f * DeltaTime;

	// 화면의 바닥을 넘어갈 경우
	if (mEnemyPos.y + mEnemySize.y / 2.f >= 720.f)
	{
		mEnemyRC.Bottom = 720.f;
		mEnemyRC.Top = 620.f;
		mEnemyDirect = -1.f;
	}
	// 화면의 상단을 넘어갈 경우
	else if (mEnemyPos.y - mEnemySize.y / 2.f <= 0.f)
	{
		mEnemyRC.Bottom = 100.f;
		mEnemyRC.Top = 0.f;
		mEnemyDirect = 1.f;
	}

	std::list<FBullet>::iterator iter1 = mEnemyBulletList.begin();
	std::list<FBullet>::iterator iter1End = mEnemyBulletList.end();
	
	// stl list 또는 stl vector 또는 map을 쓰면
	// list, vector에서 제거를 하면 erase함수를 사용
	// erase를 사용하면, 그 node를 제거하고 
	// 다음노드의 iterator를 반환해준다.
	// 이런 특성으로 인해 end가 변경될 수 있음.
	for (; iter1 != iter1End;)
	{
		// 무브 벡터의 크기는 곧 이동거리를 의미한다.
		FVector2D Move = (*iter1).MoveDirect * 500.f * DeltaTime;

		(*iter1).Pos += (*iter1).MoveDirect * 500.f * DeltaTime;

		float Distance = Move.Length();

		(*iter1).Distance -= Distance;

		if ((*iter1).Distance <= 0.f)
		{
			iter1 = mEnemyBulletList.erase(iter1);
			iter1End = mEnemyBulletList.end();
			continue;
		}
		
		// x축의
		// Left를 넘어갈때 총알 해제
		// Top을 넘어갈때 총알 해제
		// Bottom을 넘어갈 때 총알 해제
		// Right를 넘어갈때 총알 해제
		else if ((*iter1).Pos.x + (*iter1).Size.x / 2.f <= 0.f ||
			(*iter1).Pos.y + (*iter1).Size.y / 2.f <= 0.f ||
			(*iter1).Pos.y - (*iter1).Size.y / 2.f >= 720.f ||
			(*iter1).Pos.y - (*iter1).Size.y / 2.f >= 1280.f)
		{
			iter1 = mEnemyBulletList.erase(iter1);
			iter1End = mEnemyBulletList.end();
			continue;
		}

		++iter1;
	}

	mFireAccelTime += DeltaTime;

	if (mFireAccelTime >= mFireTime)
	{
		// 0.f로 초기화 할경우 조금씩 값이 틀어질 수 있다.
		mFireAccelTime -= mFireTime;

		// 총알 시작 위치는 적의 왼쪽에 생성
		FBullet Bullet;

		Bullet.Pos.x = mEnemyPos.x - mEnemySize.x / 2.f - 25.f;
		Bullet.Pos.y = mEnemyPos.y;

		Bullet.Size = FVector2D(50.f, 50.f);
		// 타겟 중앙 포지션 값 - 총알의 중앙포지션 값 = 타겟 방향의 총알 벡터값
		Bullet.MoveDirect = mPlayerPos - Bullet.Pos;
		Bullet.MoveDirect.Normalize();

		Bullet.Distance = 400.f;

		mEnemyBulletList.push_back(Bullet);
	}
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
}

void CGameManager::Render(float DeltaTime)
{
	// World 좌표 기준으로 생성
	// DirectX는 중앙이 0,0
	// WinAPI는 좌측상단이 0,0이다.
	// 
	// 창크기에 맞춰서 (Ex: 1280/720)으로 생성을 해도,
	// 윈도우창의 전체크기로 생성이 된다.
	// 즉 전체화면이 아닐때, Title창도 크기로 인식이 된다.
	//Rectangle(mHandleDC, 100, 100, 200, 200);
	//Rectangle(mHandleDC, 
	//	(int)mRC.Left, (int)mRC.Top, 
	//	(int)mRC.Right, (int)mRC.Bottom);
	
	// size는 전체크기이기 때문에 중점을 맞추기 위해 / 2를 함
	// 매개변수2 : 왼쪽 좌표
	// 매개변수3 : 상단 좌표
	// 매개변수4 : 오른쪽 좌표
	// 매개변수5 : 하단 좌표
	Rectangle(mHandleDC, (int)(mPlayerPos.x - mPlayerSize.x / 2.f),
		(int)(mPlayerPos.y - mPlayerSize.y / 2.f),
		(int)(mPlayerPos.x + mPlayerSize.x / 2.f),
		(int)(mPlayerPos.y + mPlayerSize.y / 2.f));

	std::list<FBullet>::iterator iter = mBulletList.begin();
	std::list<FBullet>::iterator iterEnd = mBulletList.end();

	for (; iter != iterEnd; ++iter)
	{
		Ellipse(mHandleDC, (int)((*iter).Pos.x - (*iter).Size.x / 2.f),
			(int)((*iter).Pos.y - (*iter).Size.y / 2.f),
			(int)((*iter).Pos.x + (*iter).Size.x / 2.f),
			(int)((*iter).Pos.y + (*iter).Size.y / 2.f));
	}

	Rectangle(mHandleDC, (int)(mEnemyPos.x - mPlayerSize.x / 2.f),
		(int)(mEnemyPos.y - mPlayerSize.y / 2.f),
		(int)(mEnemyPos.x + mPlayerSize.x / 2.f),
		(int)(mEnemyPos.y + mPlayerSize.y / 2.f));

	//////////////////////적 관련 iterator//////////////////////	
	std::list<FBullet>::iterator iter1 = mEnemyBulletList.begin();
	std::list<FBullet>::iterator iter1End = mEnemyBulletList.end();

	for (; iter1 != iter1End; ++iter1)
	{
		Ellipse(mHandleDC, (int)((*iter1).Pos.x - (*iter1).Size.x / 2.f),
			(int)((*iter1).Pos.y - (*iter1).Size.y / 2.f),
			(int)((*iter1).Pos.x + (*iter1).Size.x / 2.f),
			(int)((*iter1).Pos.y + (*iter1).Size.y / 2.f));
	}
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
