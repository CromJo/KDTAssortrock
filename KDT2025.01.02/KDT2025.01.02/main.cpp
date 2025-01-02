#include <iostream>
#include "Stack.h"
#include "Queue.h"

/*
	---------------Stack & Queue----------------
	스택	: 선입후출, 후입선출 방식의 자료구조
	큐	: 선입선출 방식의 자료구조

	선입선출			: 먼저들어온 것을 먼저 사용하는 방식		(리스트 방식을 추천)
	선입후출(후입선출)	: 마지막에 들어온것을 먼저 사용하는 방식	

	스택과 큐는 배열, 리스트 둘중하나를 이용하여 구현할 수 있다.

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