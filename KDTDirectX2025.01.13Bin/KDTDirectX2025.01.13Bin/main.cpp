#include "framework.h"
#include "main.h"

#define MAX_LOADSTRING 100

HINSTANCE handleInstance;
WCHAR stringZeroTerminatedTitle[MAX_LOADSTRING];
WCHAR stringZeroTerminatedWindowClass[MAX_LOADSTRING];

bool gLoop = true;

ATOM	MyRegisterClass(HINSTANCE handleInstance);
BOOL	InitInstance(HINSTANCE, int);

LRESULT CALLBACK	WindowProcess(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE handleInstance, 
					_In_opt_ HINSTANCE handlePreviousInstance, 
					_In_ LPWSTR longPointerCmdLine, 
					_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(handlePreviousInstance);
	UNREFERENCED_PARAMETER(longPointerCmdLine);

	LoadStringW(handleInstance, IDS_APP_TITLE, stringZeroTerminatedTitle, MAX_LOADSTRING);
	LoadStringW(handleInstance, IDC_MAIN, stringZeroTerminatedWindowClass, MAX_LOADSTRING);
	MyRegisterClass(handleInstance);

	if (!InitInstance(handleInstance, nCmdShow))
		return false;

	// HACCEL handleAccelTable = LoadAccelerators(handleInstance, MAKEINTRESOURCE(IDC_MAIN));

	MSG message;

	while (gLoop)
	{
		if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	return (int)message.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW windowClassExtended;

	windowClassExtended.cbSize = sizeof(WNDCLASSEX);
	windowClassExtended.style = CS_HREDRAW | CS_VREDRAW;
	windowClassExtended.lpfnWndProc = WindowProcess;
	//windowClassExtended.cbClsExtra = 0;
	//windowClassExtended.cbWndExtra = 0;
	windowClassExtended.hInstance = hInstance;
	windowClassExtended.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAIN));
	windowClassExtended.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDI_SMALL));
	windowClassExtended.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
	windowClassExtended.lpszMenuName = MAKEINTRESOURCEW(IDC_MAIN);
	windowClassExtended.lpszClassName = stringZeroTerminatedWindowClass;
	windowClassExtended.hIconSm = LoadIcon(windowClassExtended.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&windowClassExtended);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	handleInstance = hInstance;

	HWND handleWindow = CreateWindowW(stringZeroTerminatedWindowClass, stringZeroTerminatedTitle,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!handleWindow)
		return false;

	ShowWindow(handleWindow, nCmdShow);
	UpdateWindow(handleWindow);

	return true;
}

LRESULT CALLBACK WindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);

			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(handleInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);

				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;
	case WM_PAINT:
		{
		PAINTSTRUCT paintStruct;
		}
	}
}