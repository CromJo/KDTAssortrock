#include <iostream>

/*
	메모리 영역
	스택		: 지역변수가 만들어지는 영역.
	데이터	: 전역변수, 정적 변수가 만들어지는 영역.
				정적변수와 전역변수는 초기화 값을 대입하지 않으면, 0으로 자동 초기화 된다.
	코드		: 프로그램 실행 시 코드가 저장되는 영역.
	힙		: 동적할당한 변수의 메모리가 만들어지는 영역.

	- 함수호출규약 알아보기

	지역변수	: 코드 블록 안에 선언하여 사용하는 변수.
				함수의 인자도 지역변수이다.
				함수 종료 시 메모리가 제거된다.
*/

// 전역 변수 : 코드블록 바깥에 선언하는 함수.
// 프로그램 시작 시 메모리가 생성되고,
// 프로그램 종료 시 메모리가 제거된다.
int gNumber = 1000;

void Test(int Number)
{
	int Number1;		// 지역변수

	// 정적변수가 된다. 이 변수는 처음 1번만 초기화되고, 
	// 다음부터는 초기화가 무시된다.
	// 일반(지역) 변수는 함수 종료 시 메모리가 제거되지만,
	// 정적변수는 프로그램이 끝날때가지 유지 된다.
	static int staticNumber = 50;
}

int* CreateDynamicInt()
{
	return new int;
}

// bool 타입으로 공간할당이 되었는지를 체크한다.
bool CreateDynamicBool(int** Alloc)
{
	*Alloc = new int;

	return true;
}

bool CreateDynamicInt2(int*& Alloc)
{
	Alloc = new int;

	return true;
}

int main()
{
	/*
		다중포인터도 메모리 주소를 저장하는 변수이다.
		이중포인터 : 일반 변수의 메모리 주소를 담아놓는 변수
		이중포인터 : 일반포인터 변수의 메모리 주소를 담아놓는 변수
		삼중포인터 : 이중포인터 변수의 메모리 주소를 담아놓는 변수.
	*/

	int Number = 100;
	int* pNumber = &Number;
	int** ppNumber = &pNumber;

	std::cout << pNumber << " | " << &pNumber << " | " << ppNumber << " | " << &ppNumber << std::endl;

	std::cout << "Number \t\t: " << Number << std::endl;
	std::cout << "Number Addr\t: " << &Number << std::endl;
	std::cout << "pNumber \t: " << pNumber << std::endl;
	std::cout << "pNumber Addr \t: " << &pNumber << std::endl;
	std::cout << "pNumber Value \t: " << *pNumber << std::endl;
	std::cout << "ppNumber \t: " << ppNumber << std::endl;
	std::cout << "ppNumber Addr \t: " << &ppNumber << std::endl;
	std::cout << "ppNumber Value \t: " << *ppNumber << std::endl;

	// pNumber는 Number의 변수의 메모리 주소를 가지고 있기 때문에, 
	// 역참조를 통해 Number변수의 값을 변경할 수 있다.
	*pNumber = 500;
	std::cout << Number << std::endl;

	/*
		동적 할당 : 런타임에 메모리의 생성과 해제를 컨트롤 할 수 있는 기능.
		C언어 방식 : malloc, free를 이용하여 메모리를 생성 및 해제.	(클래스의 생성자 호출 X)
		C++ 방식 :	new, delete를 이용하여 메모리를 생성 및 해제.	(클래스의 생성자 호출 O)
			- new 할당할 타입;
				※ 할당할 타입의 메모리 크기만큼 힙 영역에 메모리를 생성하고 그 주소를 반환.
				※ new를 이용하여 동적할당 된 메모리는,
					delete를 이용하여 메모리를 제거하지 않을 경우,
					메모리가 그대로 남아있게 된다. 
					이러한 현상을 "메모리 릭"이라고 한다.
	*/
	int* NumberAddr = new int;
	int** ppNumberAddr = new int*;
	*NumberAddr = 500;
	std::cout << "넘버주소 : " << NumberAddr << "\t넘버 값 : " << *NumberAddr << "\t엠퍼센트 넘버 : " << &ppNumberAddr << std::endl;
	// 동적 데이터 삭제
	delete NumberAddr;

	// 동적 배열 할당
	int* pArray = new int[10];
	CreateDynamicBool(ppNumberAddr);
	pArray[1] = 300;
	// 동적 배열 삭제
	delete[] pArray;


	return 0;
}