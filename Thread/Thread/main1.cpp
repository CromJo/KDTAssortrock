#include <iostream>
#include <process.h>

#include <Windows.h>

int gNumber = 100;

// Critical Section ����ü
CRITICAL_SECTION gCrt;


// void* ������ �־������
// ��ȯ���� unsigned int ������ �־������
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

	// Lock (�ڿ� ����ȭ ���� for�� �ۿ��� �� �ѹ���)
	//EnterCriticalSection(&gCrt);

	for (int i = 0; i < 100000000; ++i)
	{
		// Lock (�����ϰ� ���� for�� �ȿ��� �ϳ��ϳ� ���)
		EnterCriticalSection(&gCrt);

		gNumber--;

		// UnLock (�����ϰ� ���� for�� �ȿ��� �ϳ��ϳ� ���)
		LeaveCriticalSection(&gCrt);
	}

	// UnLock (�ڿ� ����ȭ ���� for�� �ۿ��� �� �ѹ���)
	//LeaveCriticalSection(&gCrt);



	return 0;
}

int main()
{
	// ũ��Ƽ�ü��� ��ü ����.
	InitializeCriticalSection(&gCrt);

	// �Ű�����1 : ���Ȼ���
	// �Ű�����2 : ���û����� (0�־��ָ� �ڵ����� ũ�� �����)
	// �Ű�����3 : 
	// �Ű�����4 :
	HANDLE Thread1 = (HANDLE)_beginthreadex(nullptr, 0, ThreadFunction1, nullptr, 0, 0);
	HANDLE Thread2 = (HANDLE)_beginthreadex(nullptr, 0, ThreadFunction2, nullptr, 0, 0);

	// Handle�� Signal, NorSignal 2���� ���·� ���� �� �ִ�.
	// ������ ���� �� �ش� �������� Handle�� Signal ���°� �ȴ�.
	// WaitForSingleObject �Լ��� Handle�� Signal �������� üũ���ִ� �̺�Ʈ ����ȭ �Լ�.
	WaitForSingleObject(Thread1, INFINITE);
	WaitForSingleObject(Thread2, INFINITE);

	std::cout << gNumber << std::endl;

	CloseHandle(Thread1);
	CloseHandle(Thread2);

	// ���α׷��� ����Ǹ� ��ü�� ���� ��Ų��.
	DeleteCriticalSection(&gCrt);

	return 0;
}