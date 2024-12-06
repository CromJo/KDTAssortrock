#include <iostream>

int main()
{
	/// :: : 범위지정 연산자.
	/// ex : std안에 있는 cout 기능
	/// std는 namespace이다. 
	/// namespace는 소속을 지정해준다.
	/// 실무에서는 namespace를 사용하지 않는다. 주의.

	std::cout << "Output\n";
	printf("Hello World\n");

	/*
	타입		|	데이터종류	|	메모리크기	|	값의 표현범위
	char	|	문자			|	1byte		|	-128 ~ 127 (0자리 표현으로 인해 127)
	bool	|	참 / 거짓	|	1byte		|	false ~ true (0 ~ 1)
	short	|	정수			|	2byte		|	-32768 ~ 32767
	int		|	정수			|	4byte		|	-2147483648 ~ 2147483647
	__int	|	정수			|	8byte		|
	float	|	부동소수점	|	4byte		|	소수점 7자리
	double	|	부동소수점	|	8byte		|	소수점 15자리
	unsigned|	양수			|				|	음수(-)의 값을 양수(+)로 변환해준다. Ex) unsinged char 0 ~ 255
	*/

	unsigned short ShortNumber = 32768 + 32769;
	std::cout << ShortNumber << std::endl;

	// 변수 타입 앞에 const를 붙이면 상수가 된다. (상수는 추후 데이터값을 변경할 수 없음.
	const unsigned short CONST_NUMBER = 500;

	bool TestBool = -1;
	std::cout << "참/거짓 : " << TestBool << std::endl;

	char TestChar = 'A';
	// C언어 스타일 형변환
	std::cout << "문자 : " << (int)TestChar << std::endl;
	// C++ 스타일 형변환
	std::cout << "문자 : " << static_cast<int>(TestChar) << std::endl;

	// Warning을 가볍게 생각하지 말자. 
	// f를 기입하지 않을경우 더블로 인식함.
	float TestFloat = 3.14f;
	double TestDouble = 2222.4534953467779456912345678901234567890;
	std::cout << "실수 : " << TestFloat << std::endl << "더블 : " << TestDouble << std::endl;
	printf("정수 출력 : %d\n", (int)TestDouble);
	printf("실수 최대 출력 : %.32f\n", TestDouble);

	int TestData = 1234567;
	TestFloat = TestData;
	std::cout << "문자 오류 : " << TestFloat << std::endl;

	/// 사칙 연산자 +, -, *, /, %			더하기, 빼기, 곱하기, 나누기, 나머지
	///	
	std::cout << 10 / 3.f << std::endl;

	/// 관계 연산자 : <, >, <=, >=, ==	오른쪽이 크다, 왼쪽이 크다, 오른쪽이 크거나 같다, 왼쪽이 크거나 같다, 동일하다.
	std::cout << "관계 연산자 : " << (70 <= 90) << std::endl;

	/// 논리 연산자 : ||, &&, !			OR, AND, NOT
	std::cout << "논리 연산자 : " << (0 || 0) << std::endl;

	/// 2진수 : 0, 1
	/// 10진수 : 0 ~ 9 
	/// 16진수 : 0 ~ 9 A(10) ~ F(15)

	/// 비트단위 논리 연산자 : 값 대 값을 연산해서 결과로 값이 나오게 된다.
	/// OR(|), AND(&), NOT(~), XOR(^)  

	int Buf = 0x1f;
	std::cout << Buf << std::endl;

	/// 쉬프트 연산자 : <<, >> 
	/// 값 대 값을 연산하여 결과로 값이 나오게 된다.
	/// 10 << 3은 10 * 2의3승의 곱하기 결과 값과 같다.
	/// 10 >> 4는 10 / 2의4승의 나눗셈 결과 값과 같다.
	/// 2의 n승 단위의 곱하기/나눗셈 연산에 특화되어 있다.

	int Color = 0;
	unsigned char r = 255;
	unsigned char g = 128;
	unsigned char b = 0;
	unsigned char a = 200;

	Color = a;
	Color = Color << 8;
	Color = Color | r;
	Color = Color << 8;
	Color = Color | g;
	Color = Color << 8;
	Color = Color | b;

	std::cout << "컬러 : " << Color << std::endl;
	std::cout << "b = " << (Color & 0x000000ff) << std::endl;
	std::cout << "g = " << ((Color >> 8) & 0xff) << std::endl;
	std::cout << "r = " << ((Color >> 16) & 0xff) << std::endl;
	std::cout << "a = " << ((Color >> 24) & 0xff) << std::endl;

	int TestShift = 1;
	TestShift <<= 8;
	std::cout << "시프트 : " << TestShift << std::endl;

	return 0;
}