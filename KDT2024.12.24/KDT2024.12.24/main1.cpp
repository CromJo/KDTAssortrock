#include <iostream>
#include <vector>
#include <list>
#include "Array.h"

/*
	��ũ�� ����Ʈ		: ������ �迭
			Ư¡		: �߰� ����/������ ������.
	���Ϳ��� ������	: 			
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
		//IntList.push_back(i + 1);			// push_back�� emplace_back�� ���̴� ����.
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

	// resize�� ���� Capacity���� �۰� ������ ���,
	// Capacity�� �����ϸ� size�� ���ҽ�Ų��.
	// Ŭ ��쿡�� Capacity�� �÷��ش�.
	// ������ ���ִ� ���� �ִٸ� �����Ѵ�.
	vectorInt.resize(2);		// 2���� �迭�� �����.

	// reserve�� ���� Capacity���� �۰� ������ ���,
	// �ƹ��� �ϵ�����.
	// Ŭ ��� ���� ������� �����Ǹ�, Capacity��,
	// ������ ũ��� �þ�� �迭ũ�⸸ŭ ����� �ȴ�.
	// ���� �״�� ���� �����ȴ�.
	vectorInt.reserve(2);		// 
	vectorInt.resize(20);		// 5�������� 1~5�� �ʱ�ȭ�� �ǰ� ������ 15���� 0�ʱ�ȭ�� �ȴ�.
	vectorInt.reserve(20);		// 5�������� �����ǰ� Capacity�� 20���� �÷��ش�.

	// �����Լ����̺�
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