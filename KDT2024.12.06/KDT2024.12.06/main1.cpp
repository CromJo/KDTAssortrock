#include <iostream>

/*
	함수 오버로딩 : 같은 이름의 함수를 다른 형태로 여러개 만들어주는 기능.
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
	재귀함수 : 자기 자신을 호출하는 방식이다.
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