#include <iostream>
#include <process.h>		// 멀티스레드 사용을 위함
#include <Windows.h>		// 동기화를 위함

#include <thread>			// C++ 11이상버전부터 사용가능한 thread 객체 사용법
#include <atomic>

int gNumber = 100;;
std::atomic(int) gNumber1(100)

void ThreadFunction1()
{
	std::cout << "ThreadFunction1" << std::endl;

	for (int i = 0; i < 100000000; ++i)
	{
		gNumber++;
	}
}

void ThreadFunction2()
{
	std::cout << "ThreadFunction2" << std::endl;

	for (int i = 0; i < 100000000; ++i)
	{
		gNumber--;
	}
}

void ThreadFunctionParameter1(int num1, int num2)
{
	std::cout << "ThreadFunction3" << std::endl;
}

int main()
{
	// C++ 11버전 이하에서도 작동하는 함수
	//_beginthreadex()

	// 각 쓰레드 받아오는 함수에 따라 다른 사용법
	std::thread thread1(ThreadFunction1);					
	std::thread thread2(ThreadFunction2);
	std::thread thread3(ThreadFunctionParameter1, 10, 20);

	
	// join 함수는 메인쓰레드가 이 쓰레드가 끝날때까지 대기해준다.
	// joinable 함수는 join이 가능한 상태인지를 판별한다.
	if (thread1.joinable())
	{
		thread1.join();
	}
	thread2.join();
	thread3.join();
	
	// detach 함수는 메인스레드가 독립적으로 동작한다.
	// 백그라운드에서 스레드가 동작되기 때문에 메인스레드가 먼저 종료될 위험이 있다.
	thread1.detach();
	thread2.detach();
	thread3.detach();

	// 특정시간만큼 대기
	std::this_thread::sleep_for(std::chrono::seconds(10));


	std::cout << "Number : " << gNumber << std::endl;
	std::cout << "Atomic Number : " << gNumber1.load() << std::endl;

	// hardware_concurrency 함수는 실행 가능한 CPU의 코어수를 반환한다.
	std::cout << std::thread::hardware_concurrency() << std::endl;

	return 0; 
}