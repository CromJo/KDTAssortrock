#include <iostream>
#include <vector>
#include <list>
#include "Array.h"

/*
	링크드 리스트		: 포인터 배열
			특징		: 중간 삽입/삭제가 빠르다.
	벡터와의 차이점	: 			
*/

class CInner1
{

};

class COuter1
{
public:
	typedef CInner1 Inner;
};

class COuter
{
public:
	class CInner
	{
	};
};

class CTestClass
{
};

int main()
{
	std::list<int> IntList;

	for (int i = 0; i < 10; i++)
	{
		//IntList.push_back(i + 1);			// push_back과 emplace_back의 차이는 없다.
		IntList.emplace_back(i + 1);
	}

	IntList.emplace_front(1000);

	std::list<int>::iterator iter;
	std::list<int>::iterator iterEnd = IntList.end();

	for (iter = IntList.begin(); iter != iterEnd; iter++)
	{
		std::cout << *iter << std::endl;
	}

	//iter = IntList.begin() + 10;

	std::vector<int> vectorInt;

	vectorInt.push_back(1);
	vectorInt.push_back(2);
	vectorInt.push_back(3);
	vectorInt.push_back(4);
	vectorInt.push_back(5);

	// resize는 기존 Capacity보다 작게 설정될 경우,
	// Capacity는 유지하며 size만 감소시킨다.
	// 클 경우에는 Capacity만 늘려준다.
	// 기존에 들어가있는 값이 있다면 유지한다.
	vectorInt.resize(2);		// 2개의 배열만 남긴다.

	// reserve는 기존 Capacity보다 작게 설정될 경우,
	// 아무런 일도없다.
	// 클 경우 기존 사이즈는 유지되며, Capacity만,
	// 지정된 크기로 늘어나서 배열크기만큼 만들게 된다.
	// 기존 그대로 값은 유지된다.
	vectorInt.reserve(2);		// 
	vectorInt.resize(20);		// 5개까지만 1~5로 초기화가 되고 나머지 15개는 0초기화가 된다.
	vectorInt.reserve(20);		// 5개까지만 생성되고 Capacity만 20개로 늘려준다.

	// 가상함수테이블
	// memset(TestArr, 0, sizeof(CTestClass) * Capacity);

	CArray<int> ArrInt;

	for (int i = 0; i < 10; i++)
	{
		ArrInt.push_back(i + 1);
	}


	COuter::CInner In;
	COuter1::Inner In1;
	CArray<int>::iterator IterArr;

	IterArr = ArrInt.begin() + 6;

	std::cout << *IterArr << std::endl;

	IterArr = ArrInt.erase(IterArr);

	std::cout << *IterArr << std::endl;

	ArrInt.pop_back();

	//ArrInt.clear();

	CArray<int>::iterator	iterArrEnd =
		ArrInt.end();

	for (IterArr = ArrInt.begin();
		IterArr != iterArrEnd; ++IterArr)
	{
		std::cout << *IterArr << std::endl;
	}

	return 0;
}