#include <iostream>
#include "Stack.h"
#include "Queue.h"

/*
	---------------Stack & Queue----------------
	����	: ��������, ���Լ��� ����� �ڷᱸ��
	ť	: ���Լ��� ����� �ڷᱸ��

	���Լ���			: �������� ���� ���� ����ϴ� ���		(����Ʈ ����� ��õ)
	��������(���Լ���)	: �������� ���°��� ���� ����ϴ� ���	

	���ð� ť�� �迭, ����Ʈ �����ϳ��� �̿��Ͽ� ������ �� �ִ�.

*/

int main()
{
	CStackDynamicArray<int> IntStack;
	CStackStaticArray<int, 10> IntStaticStack;
	CQueue<int> IntQueue;
	CCircleQueue<int, 10> IntCircleQueue;

	for (int i = 0; i < 10; i++)
	{
		IntStack.push(i);
	}
	
	std::cout << "-------------------Stack---------------------" << std::endl;

	while (!IntStack.empty())
	{
		std::cout << IntStack.pop() << std::endl;
	}


	for (int i = 0; i < 10; i++)
	{
		IntQueue.push(i);
	}

	std::cout << "-------------------Queue---------------------" << std::endl;

	while (!IntQueue.empty())
	{
		std::cout << IntQueue.pop() << std::endl;
	}



	for (int i = 0; i < 10; i++)
	{
		IntCircleQueue.push(i);
	}

	std::cout << "---------------Circle Queue-----------------" << std::endl;

	while (!IntCircleQueue.empty())
	{
		std::cout << IntCircleQueue.pop() << std::endl;
	}

	return 0;
}