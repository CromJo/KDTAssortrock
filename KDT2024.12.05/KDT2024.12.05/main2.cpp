#include <iostream>

int main()
{
	/*
		������ ���� : +, - 
		������ ������ ������ ������ �迭�� �ּҸ� �˰� ���� ��쿡 �ַ� Ȱ�� �ȴ�.
		������ ������ ������ ���� �ڷ����� ũ�⸸ŭ �ڵ����� ����(ġȯ)�� �ȴ�.
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
	// ���� Ÿ�� ���ʿ� const�� ������ ������ �Ұ���.
	// �߸��� �� : *cpNumber = 555555;
	std::cout << *cpNumber << std::endl;

	cpNumber = Array;
	int* const pcNumber = Array;
	*pcNumber = 123456;
	// ���� Ÿ�� �����ʿ� const�� ���� ��� ��������� ������ �� ����.
	// �߸��� �� : pcNumber = Array;

	int* PointerArray[10] = {};

	std::cout << std::endl << std::endl;
	for (int i = 0; i < 10; i++)
	{
		std::cout << PointerArray + i << std::endl;
	}


	return 0;
}