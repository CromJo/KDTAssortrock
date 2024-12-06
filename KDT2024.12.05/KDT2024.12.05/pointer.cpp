#include <iostream>

int* GetIntAddress()
{
	// NumberFunc 변수는 이 함수가 호출될 때 메모리가 생성되고,
	//	이 함수의 호출이 종료될 때 메모리가 제거 됨.
	// 여기서 이 변수의 주소를 반환하게 되면 함수가 종료될 때,
	//	반환된 주소는 이미 제거된 메모리가 되므로,
	//	반환된 주소로 역참조 시도 시 문제가 발생된다.
	// 이렇게 제거된 메모리 주소를 가지고 있는 포인터를
	//	"댕글링포인터"라고 한다.

	int NumberFunc = 500;

	return &NumberFunc;
}

int main()
{
	/*
		변수를 선언 시 해당 변수의 크기만큼 메모리에 공간이 할당 되고, 
			그 공간에 데이터를 저장하게 된다.
		메모리에 주소를 부여하고, 해당 주소를 이용해 공간을 찾는다.
		주소는 바이트 단위로 부여가 된다.
		32bit인지 64bit인지에 따라 메모리 주소의 바이트 단위가 달라진다.

		16진수 1자리 = 2진수 4자리
		32비트 = 16진수 8자리 표현 가능
		64비트 = 16진수 16자리 표현 가능

		포인터 : 메모리 주소를 저장하기 위한 변수 타입.
		모든 변수타입은 포인터 타입 변수를 생성 할 수 있다.
		메모리 주소를 저장하는 변수이기 때문에, 모든 포인터들의 바이트는
		32bit : 4byte,
		64bit : 8byte
		의 크기를 가지게 된다.

		참조 : 포인터 변수가 메모리 주소를 가짐.
		역참조 : 가지고 있는 메모리 주소에 접근함.

		포인터 선언시 타입을 동일하게 선언해야 한다.
		Ex) int변수의 메모리 주소의 저장을 위해서는,
				int의 포인터 타입으로 선언해야함.
	*/

	int Number = 100;
	int* pNumberInt = &Number;
	float* pNumberFloat = (float*)&Number;
	void* pNumberVoid = &Number;

	std::cout << "숫자 : " << Number << std::endl;
	std::cout << "주소 숫자 : " << &Number << std::endl;
	std::cout << "참조 숫자 : " << pNumberInt << std::endl;
	std::cout << "역참조 숫자 : " << *pNumberInt << std::endl;

	int Array[10] = {};
	
	// 배열의 이름은 이 배열의 할당 된 메모리 시작의 주소이다.
	std::cout << Array << std::endl;		// 결과 : Array 배열의 첫번째 시작 주소값.
	// 배열의시작주소[인덱스]
	Array[2] = 500;
	
	// 배열이름은 배열의 시작 주소이므로 포인터 변수에
	// 배열의 시작주소를 저장한다.
	int* pArray = Array;

	// pArray도 Array와 동일하게 배열의 시작 주소를 가지고 있으므로,
	// 인덱스를 이용하여 동일한 배열에 접근이 가능하다.
	pArray[2] = 111111;
	
	std::cout << pArray[2] << " | " << *pArray << " | " << pArray << " | "  << Array << std::endl;

	return 0;
}