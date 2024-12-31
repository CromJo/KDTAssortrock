#include <iostream>
#include "LinkedList.h"
#include <list>

/*
	linked list :
		- Node가 필요하다
			- Node는 크게 2가지의 방식이있다.
			- 싱글 방식 : Data, 다음 Node의 주소 (Next) 
			- 더블 방식 : Data, Next, Previous

		특징 : 배열에 비해서 중간 삽입/삭제가 빠르다.
				단순 삽입/삭제 (맨 끝 추가/삭제를 의미)는 Vector가 더 빠르다.

*/

int main()
{
	/*std::list<int> IntList1;

	IntList1.push_back(10);
	IntList1.push_back(20);
	IntList1.push_back(30);

	std::list<int>::iterator iter1 = IntList1.begin();
	iter1++;

	IntList1.insert(iter1, 40);

	std::cout << "------------IntList1 section-------------" << std::endl;

	for (iter1 = IntList1.begin(); iter1 != IntList1.end(); iter1++)
	{
		std::cout << *iter1 << std::endl;
	}

	std::list<int>::reverse_iterator riter;
	std::list<int>::reverse_iterator riterEnd = IntList1.rend();

	std::cout << "------------riter section-------------" << std::endl;
	for (riter = IntList1.rbegin(); riter != riterEnd; riter++)
	{
		std::cout << *riter << std::endl;
	}

	CLinkedList<int> IntList;

	for (int i = 0; i < 10; i++)
	{
		IntList.push_back(i);
	}

	CLinkedList<int>::iterator iter;
	CLinkedList<int>::iterator iterEnd = IntList.end();

	std::cout << "------------iter pointer section-------------" << std::endl;
	for (iter = IntList.begin(); iter != iterEnd; iter++)
	{
		std::cout << *iter << std::endl;
	}

	CLinkedList<int>::riterator customRiter;
	CLinkedList<int>::riterator customRiterEnd = IntList.rend();

	std::cout << "------------Custom riter section-------------" << std::endl;
	for (customRiter = IntList.rbegin(); customRiter != customRiterEnd; customRiter++)
	{
		std::cout << *customRiter << std::endl;
	}*/

	int a = 5;
	int* b = &a;
	int& c = a;

	return 0;
}