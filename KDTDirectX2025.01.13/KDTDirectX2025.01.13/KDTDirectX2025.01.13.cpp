// KDTDirectX2025.01.13.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "framework.h"
#include "KDTDirectX2025.01.13.h"

#define MAX_LOADSTRING 100   

/*
    윈도우는 메세지 기반의 운영체제이다.
    발생하는 이벤트(키입력, 마우스 클릭/이동/휠 사용, 화면 절전기능 등)
    을 메세지로 변경해서 이벤트가 발생한 윈도우에 메세지를 전송해준다.
    
    윈도우는 내부에 메세지 큐를 가지고 있다.
    메세지 큐에 운영체제로부터 전송받은 메세지가 저장되고,
    이 메세지를 가져와서 메세지에 맞는 작업을 수행해주는 방식으로 동작한다.
*/


// UniCode base : 1문자당 2byte 방식
// UniCode Base에 속하는 자료형 : WCHAR
// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
bool gLoop = true;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
// HWND : WiNDow Handle의 약자
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

/*
    실행시키기 위해선 운영체제의 허락이 필요함.
    운영체제는 이러한 코드를 실행시키기 위해 IDE를 부여함.
    HInstance : 실행시키는 프로그램마다 하나씩 부여 
        (Ex : 비주얼 스튜디오를 2개 켰다면 2개의 각 HInstance 부여)
        하나의 HInstance에서 N개의 HWND가 나올 수 있음.
        HInstance는 개발자가 지정해줄 수 없음. 요청시 운영체제에서 자동으로 부여 함.

*/


// WinMain : 시작점
// 
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // LoadStringW : String Table의 특정 ID에 문자열을 얻어와 szTitle에 넣어주는 기능.
    //              굳이 사용하지 않음.
    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KDTDIRECTX20250113, szWindowClass, MAX_LOADSTRING);
    // 
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // 쓸대 없어서 안배움
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KDTDIRECTX20250113));

    // 운영체제가 만들어주는 메세지를 전달받기 위한 구조체.
    MSG msg;

    // 기본 메시지 루프입니다:
    // GetMessage : 메세지 큐의 메세지를 얻어오는 함수.
    //               이 함수는 메세지큐가 비어있다면,
    //               메세지가 들어올때까지 대기.
    //               메세지가 들어오면 가지고 온다.
    //              메세지가 없는 시간을 윈도우 DeadTime이라고 한다.
    //              (※ 게임에서는 사용하기 힘든 함수이다.)
    // PeekMessage : 메세지 큐의 메세지를 얻어오는 함수.
    //              이 함수는 메세지큐가 비어있을 경우 바로 빠져나오며 0을 반환.
    //              메세지 큐에 메세지가 있다면 해당 메세지를 가져온다.
    while (gLoop)
    {
        if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
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
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    // 윈도우클래스 구조체의 크기를 나타낸다.
    // 반드시 지정되어야 한다.
    wcex.cbSize = sizeof(WNDCLASSEX);

    // 클라이언트 영역 : Window창 틀 안의 출력 가능한 모든 부분.
    // 클라 영역의 크기(가로/세로)가 변경될 시 전부 다시 그린다.
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    // 메세지큐에서 얻어온 메세지를 인자로 넣어서 호출해줄 함수의 주소를 넘겨준다.
    wcex.lpfnWndProc    = WndProc;
    // Cls | Wnd Extra : 예약된 메세지 (쓸대 없음)
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    // 운영체제에서 부여해준 HInstance를 전달한다.
    wcex.hInstance      = hInstance;
    // Icon : 실행파일 아이콘을 지정한다.
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KDTDIRECTX20250113));
    // Cursor : 윈도우 프로그램 내 창에서의 커서 모양을 나타낸다.
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    // 클라이언트 영역의 색상을 지정한다.
    // 1 : 횐색 | 2 : 회색 | 3 : 검은색
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 3);
    // MenuName : 윈도우 메뉴를 지정한다.
    // 0을 넣어줄 시 메뉴창이 사라진다.
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KDTDIRECTX20250113);
    // ClassName : 등록할 윈도우클래스의 이름을 지정한다.
    wcex.lpszClassName  = szWindowClass;
    // IconSm : 왼쪽 최상단의 Small Icon을 지정한다.
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // 위에서 설정한 윈도우 클래스를 등록한다.
    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // CreateWindow : 윈도우 창을 생성해주는 함수.
   // WinAPI에서 함수명뒤에 
   // W가 붙으면 UniCode,
   // A가 붙으면 MultiByte이다.
   // 1번인자   : 윈도우 클래스의 이름을 지정.
   // 2번인자   : 윈도우 타이틀바에 출력할 이름을 지정.
   // 3번인자   : 윈도우 창의 모양을 결정.
   // 4번인자   : 화면에서 윈도우가 시작할 X지점을 지정.   (모니터에서 프로그램을 출력할 위치)
   // 5번인자   : 화면에서 윈도우가 시작할 Y지점을 지정.   (모니터에서 프로그램을 출력할 위치)
   // 6번인자   : 윈도우 창의 가로 크기를 지정.    (프로그램의 X 사이즈)
   // 7번인자   : 윈도우 창의 세로 크기를 지정.    (프로그램의 Y 사이즈)
   // 8번인자   : 부모윈도우가 있을 경우 부모윈도우의 핸들을 지정.
   // 9번인자   : 메뉴 핸들을 지정.
   // 10번인자  : 윈도우 인스턴스를 전달.    (WinMain에서 전달은 값으로 해야한다.)
   // 11번인자  : 창 생성 데이터를 지정.
   //           메세지 발생 시, WndProc 함수의 lParam에 이 값이 전달된다.
   // 이렇게 윈도우 생성시 윈도우 핸들을 만들어준다.
   // 잘못된 생성일 시 0반환.
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   // ShowWindow : 창을 출력할 지 숨길지 결정한다.
   ShowWindow(hWnd, nCmdShow);
   // UpdateWindow : 클라이언트 영역을 강제로 다시 크리게 요청해준다.
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                // Case문의 메세지 외의 다른 메세지가 발생할 경우,
                // 윈도우의 기본 동작 메세지가 되게 만들어준다.
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    // WM_PAINT : 윈도우 창에 그려야 하는 경우 동작한다.
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            // HDC : 화면에 그리는 도구.
            HDC hdc = BeginPaint(hWnd, &ps);

            // TextOut : 화면에 문자열을 출력해주는 함수.
            // 글자 갯수만큼 안넣어줄 경우 쓰레기 문자 출력.
            TextOut(hdc, 100, 100, L"출력", 3);

            // Rectangle : 사각형을 만든다. (2 ~ 5는 그려줄 위치 지정)
            Rectangle(hdc, 100, 200, 200, 300);

            // Ellipse : 원을 만든다.
            Ellipse(hdc, 100, 200, 200, 300);

            // 선의 시작점을 지정한다. 
            MoveToEx(hdc, 200, 100, nullptr);
            // 선의 끝점을 지정한다.
            LineTo(hdc, 300, 500);
            // 이전 MoveToEx가 없으면 마지막점 기준으로 선을 그린다.
            LineTo(hdc, 400, 200);

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    // WM_DESTROY : 윈도우 창 종료 메세지
    case WM_DESTROY:
        gLoop = false;
        PostQuitMessage(0);
        break;
    // 위에서 지정한 메세지 외의 다른 메세지가 발생할 경우 윈도우의 기본 동작으로 처리가 되게 만들어준다.
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
