#include <iostream>

/*
	�Լ� �����ε� : ���� �̸��� �Լ��� �ٸ� ���·� ������ ������ִ� ���.
*/
	
int Add(int a, int b)
{
	return a + b;
}

//int Add(int a, int b = 500)
//{
//	return a + b;
//}

/*
	����Լ� : �ڱ� �ڽ��� ȣ���ϴ� ����̴�.
*/
int Factorial(int Number)
{
	if (Number == 1)
		return 1;

	return Number * Factorial(Number - 1);
}

int FactorialTail(int Number)
{
	return Number * Factorial(Number - 1);
}

int FactorialTail(int Result, int Number)
{
	if (Number == 1)
		return Result;

	return FactorialTail(Number * Result, Number - 1);
}

int main()
{
	//Add(10);

	std::cout << Factorial(5) << std::endl;
	std::cout << FactorialTail(5) << std::endl;
	return 0;
}