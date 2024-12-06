#include <iostream>

int main()
{
	/*
		포인터 연산 : +, - 
		포인터 연산은 포인터 변수가 배열의 주소를 알고 있을 경우에 주로 활용 된다.
		포인터 연산은 포인터 변수 자료형의 크기만큼 자동으로 맵핑(치환)이 된다.
	*/

	int Array[10] = {};
	int* pArray = Array;

	for (int i = 0; i < 11; i++)
	{
		std::cout << (pArray + i) << std::endl;
	}

	int* pNumber = Array;
	*pNumber = 111;

	pNumber = Array;
	*pNumber = 222;

	const int* cpNumber = Array;
	// 변수 타입 왼쪽에 const가 붙으면 변경이 불가능.
	// 잘못된 예 : *cpNumber = 555555;
	std::cout << *cpNumber << std::endl;

	cpNumber = Array;
	int* const pcNumber = Array;
	*pcNumber = 123456;
	// 변수 타입 오른쪽에 const가 붙을 경우 참조대상을 변경할 수 없다.
	// 잘못된 예 : pcNumber = Array;

	int* PointerArray[10] = {};

	std::cout << std::endl << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << PointerArray + i << std::endl;
	}


	return 0;
}