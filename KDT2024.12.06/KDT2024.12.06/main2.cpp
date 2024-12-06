#include <iostream>

/*
	함수포인터 : 함수의 주소를 저장하기 위한 변수이다.
	함수의 형태는 반환타입과 인자로 결정된다.

	- 선언방법
	반환타입(*이름)(인자타입);

*/

void Output()
{
	std::cout << "아웃풋 펑션" << std::endl;
}

void Outputtest()
{
	std::cout << "아웃풋 테스트 펑션" << std::endl;
}

int main()
{
	Output();

	std::cout << Output << std::endl;

	void(*FuncPointer)();
	FuncPointer = Output;

	return 0;
}