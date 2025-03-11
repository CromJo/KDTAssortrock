#include <iostream>
#include <process.h>		// ��Ƽ������ ����� ����
#include <Windows.h>		// ����ȭ�� ����

#include <thread>			// C++ 11�̻�������� ��밡���� thread ��ü ����
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
	// C++ 11���� ���Ͽ����� �۵��ϴ� �Լ�
	//_beginthreadex()

	// �� ������ �޾ƿ��� �Լ��� ���� �ٸ� ����
	std::thread thread1(ThreadFunction1);					
	std::thread thread2(ThreadFunction2);
	std::thread thread3(ThreadFunctionParameter1, 10, 20);

	
	// join �Լ��� ���ξ����尡 �� �����尡 ���������� ������ش�.
	// joinable �Լ��� join�� ������ ���������� �Ǻ��Ѵ�.
	if (thread1.joinable())
	{
		thread1.join();
	}
	thread2.join();
	thread3.join();
	
	// detach �Լ��� ���ν����尡 ���������� �����Ѵ�.
	// ��׶��忡�� �����尡 ���۵Ǳ� ������ ���ν����尡 ���� ����� ������ �ִ�.
	thread1.detach();
	thread2.detach();
	thread3.detach();

	// Ư���ð���ŭ ���
	std::this_thread::sleep_for(std::chrono::seconds(10));


	std::cout << "Number : " << gNumber << std::endl;
	std::cout << "Atomic Number : " << gNumber1.load() << std::endl;

	// hardware_concurrency �Լ��� ���� ������ CPU�� �ھ���� ��ȯ�Ѵ�.
	std::cout << std::thread::hardware_concurrency() << std::endl;

	return 0; 
}