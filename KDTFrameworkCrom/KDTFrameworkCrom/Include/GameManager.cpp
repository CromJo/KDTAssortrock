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

	// �Ű������� �� �����쿡 ����� �� �ִ� DC��
	// ���������.
	// GetDC�� ���� DC�� ��� �ݵ�� �Ҹ��ڿ��� ����
	// ��������Ѵ�.
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
	FVector2D PlayerMoveDirect;

	// Ű �Է� ��� �߰�
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
	// �밢�� 3���� �Ѿ� �߻� ���
	// 1. x�� +������ �����Ǿ����� (���������θ� �����Ѵٴ� �����Ͽ�)
	// 2. y�� -1, 0, 1�� �Ǿ���Ѵ�. 
	if (GetAsyncKeyState('1') & 0x8000)
	{
		for (int i = 0; i < 3; ++i)
		{
			FBullet Bullet;

			Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
			Bullet.Pos.y = mPlayerPos.y;

			Bullet.Size = FVector2D(50.f, 50.f);
			// Ÿ�� �߾� ������ �� - �Ѿ��� �߾������� �� = Ÿ�� ������ �Ѿ� ���Ͱ�
			// 3���� ��, �߾�, �Ʒ��� ������ ������ ���� �����ϴ� 
			// �ڵ带 �����ϰ� �ϱ� ���� i (0 - 1) (1 - 0) (2 - 1)�� ���� �־��ش�.
			// �׷��� -1, 0, 1�̳����� �ǰ�,
			// WINAPI������ y�� -1�� ��, 
			// 0�� ���� y��ġ ����, 
			// 1�� �Ʒ��� �ǹ��ϹǷ� 3�������� �߻�ǰ� �ȴ�.
			Bullet.MoveDirect = FVector2D(1.f, i - 1.f);
			Bullet.MoveDirect.Normalize();
			
			Bullet.Distance = 600.f;

			mBulletList.push_back(Bullet);
		}
	}
	
	// 8���� �Ѿ� �߻� ���
	if (GetAsyncKeyState('2') & 0x8000)
	{
		FVector2D Direct[8] =
		{	// ����			// ���е� ����
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

			// ���� ��ġ���� PlayerPos�� �־��ָ� 
			// �÷��̾��� ������ �Ѿ��� 8�������� �߻��ϰ� �ȴ�.
			//Bullet.Pos = mPlayerPos;

			Bullet.Size = FVector2D(50.f, 50.f);
			// Ÿ�� �߾� ������ �� - �Ѿ��� �߾������� �� = Ÿ�� ������ �Ѿ� ���Ͱ�
			// 3���� ��, �߾�, �Ʒ��� ������ ������ ���� �����ϴ� 
			// �ڵ带 �����ϰ� �ϱ� ���� i (0 - 1) (1 - 0) (2 - 1)�� ���� �־��ش�.
			// �׷��� -1, 0, 1�̳����� �ǰ�,
			// WINAPI������ y�� -1�� ��, 
			// 0�� ���� y��ġ ����, 
			// 1�� �Ʒ��� �ǹ��ϹǷ� 3�������� �߻�ǰ� �ȴ�.
			Bullet.MoveDirect = Direct[i];
			Bullet.MoveDirect.Normalize();
			
			// ���⼭�� Bullet�� MoveDirect���� ������ �����̱� ������,
			// MoveDirect���� Ư�� ������ŭ ������� ��ġ�� �������ش� (���Ѵ�)
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
		// Ÿ�� �߾� ������ �� - �Ѿ��� �߾������� �� = Ÿ�� ������ �Ѿ� ���Ͱ�
		// x���� ����� : 1 frame���� +1�� x������ �̵�
		// y���� ����� : 1 frame���� +1�� y������ �̵�
		Bullet.MoveDirect = FVector2D(1.f, -1.f);
		Bullet.MoveDirect.Normalize();

		// floatŸ������ ǥ���� �� �ִ� �ִ�
		Bullet.Distance = FLT_MAX;
		Bullet.Option = EBulletOption::Bounce;


		mBulletList.push_back(Bullet);
	}

	// �밢�� �̵� ����ȭ���Ѽ� �ӵ��� �����ϰ� ����.
	PlayerMoveDirect.Normalize();

	mPlayerPos += PlayerMoveDirect * 400.f * DeltaTime;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		FBullet Bullet;

		Bullet.Pos.x = mPlayerPos.x + mPlayerSize.x / 2.f + 25.f;
		Bullet.Pos.y = mPlayerPos.y;

		Bullet.Size = FVector2D(50.f, 50.f);
		// Ÿ�� �߾� ������ �� - �Ѿ��� �߾������� �� = Ÿ�� ������ �Ѿ� ���Ͱ�
		// x���� ����� : 1 frame���� +1�� x������ �̵�
		// y���� ����� : 1 frame���� +1�� y������ �̵�
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

	// �÷��̾��� �Ѿ˸���Ʈ
	for (; iter != iterEnd;)
	{
		// ���� ������ ũ��� �� �̵��Ÿ��� �ǹ��Ѵ�.
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
		// stl list �Ǵ� stl vector �Ǵ� map�� ����
		// list, vector���� ���Ÿ� �ϸ� erase�Լ��� ���
		// erase�� ����ϸ�, �� node�� �����ϰ� 
		// ��������� iterator�� ��ȯ���ش�.
		// �̷� Ư������ ���� end�� ����� �� ����.
		else if (((*iter).Pos.x + (*iter).Size.x / 2.f <= 0.f ||
			(*iter).Pos.y + (*iter).Size.y / 2.f <= 0.f ||
			(*iter).Pos.y - (*iter).Size.y / 2.f >= 720.f ||
			(*iter).Pos.x - (*iter).Size.x / 2.f >= 1280.f) &&
			(*iter).Option == EBulletOption::Normal)
		{
			// ���⼭ ���Ÿ� �ϰ� �Ǹ� ++iter�� �Ǵ� ����,
			// ���ŵ� ���� ĭ�� iterator�� �����ǰ� �� ����ĭ����
			// for���� ����ȴ�.
			// �� ���ű���� �Ͼ�� 2ĭ�̵��� �ȴٰ� �� �� �ִ�.
			// �׷��⿡ for���� �ִ� ++iter�� for�� ���ϴܿ� �߰����ش�.
			iter = mBulletList.erase(iter);
			iterEnd = mBulletList.end();

			// if���� ����Ǹ� iterator�� ���Ű� �̷������ ++iter�� �����ν�,
			// 2ĭ �̵��� �Ǿ�� �ȵǱ� ������ continue�� for���� �ٽ� �����Ѵ�.
			continue;
		}
		else if ((*iter).Option == EBulletOption::Bounce)
		{
			FVector2D Normal;

			// ���� �ε������� �Ǵ��Ѵ�.
			if ((*iter).Pos.x - (*iter).Size.x / 2.f <= 0.f)
			{
				Normal.x = 1.f;
				// �Ѿ��� ũ�Ⱑ 50�̴� ������ 25�� ��´ٴ� ����
				// �Ѿ� ũ��(�߾�)�� �������� ���� �������̴�.
				// ���°� x�� ���ʺ��� ������ �����ϴ� ������ �ȴ�.
				(*iter).Pos.x = 25.f;
			}
			else if ((*iter).Pos.x + (*iter).Size.x / 2.f >= 1280.f)
			{
				Normal.x = -1.f;
				(*iter).Pos.x = 1255.f;
			}
			// ���� �ε������� �Ǵ��Ѵ�.
			else if ((*iter).Pos.y - (*iter).Size.y / 2.f <= 0.f)
			{
				Normal.y = 1.f;
				// �Ѿ��� ũ�Ⱑ 50�̴� ������ 25�� ��´ٴ� ����
				// �Ѿ� ũ��(�߾�)�� �������� ���� �������̴�.
				// ���°� x�� ���ʺ��� ������ �����ϴ� ������ �ȴ�.
				(*iter).Pos.y = 25.f;
			}
			else if ((*iter).Pos.y + (*iter).Size.y / 2.f >= 720.f)
			{
				Normal.y = -1.f;
				(*iter).Pos.y = 695.f;
			}

			// �ٿ ���
			if (Normal.Length() > 0.f)
			{
				(*iter).MoveDirect = (*iter).MoveDirect - Normal * 2.f * Normal.Dot((*iter).MoveDirect);
				(*iter).MoveDirect.Normalize();
			}
		}

		++iter;
	}

	// �� �̵�
	mEnemyPos.y += mEnemyDirect * 300.f * DeltaTime;

	// ȭ���� �ٴ��� �Ѿ ���
	if (mEnemyPos.y + mEnemySize.y / 2.f >= 720.f)
	{
		mEnemyRC.Bottom = 720.f;
		mEnemyRC.Top = 620.f;
		mEnemyDirect = -1.f;
	}
	// ȭ���� ����� �Ѿ ���
	else if (mEnemyPos.y - mEnemySize.y / 2.f <= 0.f)
	{
		mEnemyRC.Bottom = 100.f;
		mEnemyRC.Top = 0.f;
		mEnemyDirect = 1.f;
	}

	std::list<FBullet>::iterator iter1 = mEnemyBulletList.begin();
	std::list<FBullet>::iterator iter1End = mEnemyBulletList.end();
	
	// stl list �Ǵ� stl vector �Ǵ� map�� ����
	// list, vector���� ���Ÿ� �ϸ� erase�Լ��� ���
	// erase�� ����ϸ�, �� node�� �����ϰ� 
	// ��������� iterator�� ��ȯ���ش�.
	// �̷� Ư������ ���� end�� ����� �� ����.
	for (; iter1 != iter1End;)
	{
		// ���� ������ ũ��� �� �̵��Ÿ��� �ǹ��Ѵ�.
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
		
		// x����
		// Left�� �Ѿ�� �Ѿ� ����
		// Top�� �Ѿ�� �Ѿ� ����
		// Bottom�� �Ѿ �� �Ѿ� ����
		// Right�� �Ѿ�� �Ѿ� ����
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
		// 0.f�� �ʱ�ȭ �Ұ�� ���ݾ� ���� Ʋ���� �� �ִ�.
		mFireAccelTime -= mFireTime;

		// �Ѿ� ���� ��ġ�� ���� ���ʿ� ����
		FBullet Bullet;

		Bullet.Pos.x = mEnemyPos.x - mEnemySize.x / 2.f - 25.f;
		Bullet.Pos.y = mEnemyPos.y;

		Bullet.Size = FVector2D(50.f, 50.f);
		// Ÿ�� �߾� ������ �� - �Ѿ��� �߾������� �� = Ÿ�� ������ �Ѿ� ���Ͱ�
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
		�浹 (�� ������ ������ ã��)
		1. A�� Left�� B�� Right���� Ŀ���Ѵ�.
		2. B�� Left�� A�� Right���� �۾ƾ��Ѵ�.
		3. A�� Top�� B�� Bottom���� �۰ų� ���ƾ��Ѵ�.
		4. B�� Top�� A�� Bottom���� �۰ų� ���ƾ��Ѵ�.
	*/
}

void CGameManager::PostCollision(float DeltaTime)
{
}

void CGameManager::Render(float DeltaTime)
{
	// World ��ǥ �������� ����
	// DirectX�� �߾��� 0,0
	// WinAPI�� ��������� 0,0�̴�.
	// 
	// âũ�⿡ ���缭 (Ex: 1280/720)���� ������ �ص�,
	// ������â�� ��üũ��� ������ �ȴ�.
	// �� ��üȭ���� �ƴҶ�, Titleâ�� ũ��� �ν��� �ȴ�.
	//Rectangle(mHandleDC, 100, 100, 200, 200);
	//Rectangle(mHandleDC, 
	//	(int)mRC.Left, (int)mRC.Top, 
	//	(int)mRC.Right, (int)mRC.Bottom);
	
	// size�� ��üũ���̱� ������ ������ ���߱� ���� / 2�� ��
	// �Ű�����2 : ���� ��ǥ
	// �Ű�����3 : ��� ��ǥ
	// �Ű�����4 : ������ ��ǥ
	// �Ű�����5 : �ϴ� ��ǥ
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

	//////////////////////�� ���� iterator//////////////////////	
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
