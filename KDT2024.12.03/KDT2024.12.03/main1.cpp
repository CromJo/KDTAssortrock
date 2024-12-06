#include <iostream>

int main()
{
	/*
		switch문 : 분기처리가 가능하다. 
		변수의 값에 따라 case의 상수를 찾아 코드를 동작 시킨다.
		break를 만나면 switch문을 종료한다.
		default는 if문의 else와 같다.
		case 다음의 상수 중에서 변수의 값과 같은 상수가 없을경우 default가 동작한다.
	*/

	/*
		사용자정의 변수 타입 : 현재 이 프로젝트만의 고유한 변수 타입을 직접 만들어 사용할 수 있다. (커스텀 변수)
		Ex) 열거형(Enum), 구조체(Struct), 클래스(Class)

		열거형 (Enum) : 사용자 정의 변수 타입을 만들어주기 위한 하나의 문법이다.
		엵형은 연속된 숫자 상수를 만들 수 있다.
		숫자에 이름을 부여할 수 있다.
		열거형은 기본으로 4byte의 크기를 가지고 있다.
	*/
	enum E직업 : unsigned short
	{
		none = 0,
		궁수,
		마법사,
		도적,
		전사,
		MAX
	};

	enum class E아이템 : unsigned char
	{
		무기 = 0,
		방어구,
	};

	enum EBuf
	{
		Buf_Attack = 0x1,
		Buf_Defense,
		Buf_HP,
		Buf_MP,
		Buf_EXP
	};

	E직업 Job = E직업::궁수;
	
	//sizeof : 괄호안에 들어가는 타입 혹은 변수의 메모리 크기가 몇 바이트인지 구해준다.
	std::cout << sizeof(E직업) << std::endl;
	std::cout << sizeof(int) << std::endl;

	switch (Job)
	{
	case E직업::궁수:
	case E직업::도적:
		std::cout << "궁수 또는 도적 입니다. " << std::endl;
		break;
	case E직업::마법사:
	case E직업::전사:
		std::cout << "마법사 또는 전사 입니다. " << std::endl;
		break;
	default:
		break;
	}

	E아이템 A = E아이템::무기;
	std::cout << "ㅇㅇ : " << A << std::endl;
}