#include <iostream>

class CTemp
{
private:
	int mTemp = 100;

public:
	CTemp();
	CTemp(int num)
	{
		int num;
	}
	~CTemp();

	/*
		이동생성자 : 객체가 살아있는 상태에서 사용 안한다는것을
					보장할 수 있는 상황일 때 사용한다.
					&&가 들어가게 되면 우측값 레퍼런스이다.
	*/
	CTemp(CTemp&& ref)
	{
		std::cout << "이동 생성자" << std::endl;
	}

	CTemp(const CTemp& Temp)
	{
		mTemp = Temp.mTemp;
	}


private:
}

int TestFunc(const int& Num)
{
	std::cout << Num << std::endl;

	return Num;
}

int main()				// 스택, 데이터 영역
{
	// lvalue(좌측값) : & 연산자를 이용하여 메모리의 주소를 가져올 수 있는 값이다.
	// rvalue(우측값) : 주소를 가져올 수 없는 값.
	// 아래에서 Number는 좌측값을, 10은 우측값을 의미한다.
	int Number = 10;
	TestFunc(Number);

	CTemp temp;
	CTemp temp1(20);
	// 1. 임시객체생성
	// 2. 대입
	// 3. 대입이 끝날 때 임시객체 제거
	temp1 = CTemp(30);

	CTemp temp2 = temp;

	const CTemp& ref1 = CTemp(70);

	CTemp temp4 = CTemp(90);
	temp4 = CTemp(200);
	
	temp4 = temp.Create();

	return 0;
}