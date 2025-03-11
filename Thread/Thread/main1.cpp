#include <iostream>
#include <process.h>

#include <Windows.h>

int gNumber = 100;

// Critical Section 구조체
CRITICAL_SECTION gCrt;


// void* 무조건 넣어줘야함
// 반환값은 unsigned int 무조건 넣어줘야함
unsigned int __stdcall ThreadFunction1(void* Arg)
{
	std::cout << "ThreadFunction1" << std::endl;

	for (int i = 0; i < 100000000; ++i)
	{
		// Lock
		EnterCriticalSection(&gCrt);
		
		gNumber++;

		// UnLock
		LeaveCriticalSection(&gCrt);
	}

	return 0;
}

unsigned int __stdcall ThreadFunction2(void* Arg)
{
	std::cout << "ThreadFunction1" << std::endl;

	// Lock (자원 최적화 계산시 for문 밖에서 단 한번만)
	//EnterCriticalSection(&gCrt);

	for (int i = 0; i < 100000000; ++i)
	{
		// Lock (정밀하게 계산시 for문 안에서 하나하나 계산)
		EnterCriticalSection(&gCrt);

		gNumber--;

		// UnLock (정밀하게 계산시 for문 안에서 하나하나 계산)
		LeaveCriticalSection(&gCrt);
	}

	// UnLock (자원 최적화 계산시 for문 밖에서 단 한번만)
	//LeaveCriticalSection(&gCrt);



	return 0;
}

int main()
{
	// 크리티컬섹션 객체 생성.
	InitializeCriticalSection(&gCrt);

	// 매개변수1 : 보안사항
	// 매개변수2 : 스택사이즈 (0넣어주면 자동으로 크기 잡아줌)
	// 매개변수3 : 
	// 매개변수4 :
	HANDLE Thread1 = (HANDLE)_beginthreadex(nullptr, 0, ThreadFunction1, nullptr, 0, 0);
	HANDLE Thread2 = (HANDLE)_beginthreadex(nullptr, 0, ThreadFunction2, nullptr, 0, 0);

	// Handle을 Signal, NorSignal 2가지 상태로 나눌 수 있다.
	// 스레드 종료 시 해당 스레드의 Handle은 Signal 상태가 된다.
	// WaitForSingleObject 함수는 Handle이 Signal 상태인지 체크해주는 이벤트 동기화 함수.
	WaitForSingleObject(Thread1, INFINITE);
	WaitForSingleObject(Thread2, INFINITE);

	std::cout << gNumber << std::endl;

	CloseHandle(Thread1);
	CloseHandle(Thread2);

	// 프로그램이 종료되면 객체를 해제 시킨다.
	DeleteCriticalSection(&gCrt);

	return 0;
}