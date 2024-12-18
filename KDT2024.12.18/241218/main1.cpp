
#include <iostream>

class CTemp
{
public:
	CTemp()					// 생성자
	{
	}

	CTemp(int Num)			// 인자 생성자
	{
		mNumber = Num;
	}

	CTemp(const CTemp& ref)	// 복사 생성자
	{
		mNumber = ref.mNumber;
		std::cout << "복사생성자" << std::endl;
	}

	/*
	이동생성자 : 객체가 살아있는 상태에서 사용 안한다는것을
	보장할 수 있는 상황일 때 사용한다.
	&& 가 들어가게 되면 우측값 레퍼런스이다.
	*/
	CTemp(CTemp&& ref)
	{
		mNumber = ref.mNumber;
		std::cout << "이동생성자" << std::endl;
	}

	~CTemp()
	{
	}

private:
	int	mNumber = 100;

public:
	void operator = (CTemp temp)
	{
		mNumber = temp.mNumber;
	}

	CTemp Create(CTemp t1)
	{
		return t1;
	}

	CTemp* Create1()
	{
		CTemp	temp;
		return &temp;
	}
};

int TestFunc(const int& Num)
{
	std::cout << Num << std::endl;
	return Num;
}

int& TestRef(int& Num)
{
	return Num;
}


int main()
{
	// lvalue(좌측값) : & 연산자를 이용하여 메모리의 주소를
	// 가져올 수 있는 값이다. 아래에서는 Number 변수가
	// lvalue에 속한다.
	// rvalue(우측값) : 주소를 가져올 수 없는 값.
	// 아래에서는 10이 해당된다.
	int	Number = 10;
	//int& Ref1 = 30;
	int& Ref2 = TestRef(Number);
	int* Ref3 = &Number;

	int* Ref4 = &Number;
	int* Ref5 = &Ref2;
	Ref4 = Ref5;

	std::cout << "Number : " << Number << "\t &Number : " << &Number << std::endl;
	std::cout << "TestRef : " << TestRef(Number) << "\t &Ref2 : " << &Ref2 << std::endl;
	std::cout << "*Ref3 : " << Ref3 << std::endl;
	std::cout << "Ref4 주소값 : " << *Ref4 << "\t Ref5 주소값 : " << *Ref5 << std::endl;

	TestRef(Number) = 500;


	TestFunc(Number);

	//10 = Number;

	CTemp	temp;
	CTemp	temp1(20);
	// 1. 임시객체 생성
	// 2. 대입
	// 3. 대입이 끝날때 임시객체 제거
	temp = CTemp(30);

	CTemp	temp2 = temp;

	//CTemp* pTemp = &CTemp(40);
	//CTemp(50) = temp;
	//CTemp& ref = CTemp(60);
	// 레퍼런스가 유지되는 동안 임시객체도 유지된다.
	const CTemp& ref1 = CTemp(70);


	//CTemp	temp3 = temp.Create();

	//temp3 = temp.Create();

	CTemp	temp4 = temp.Create(temp1);

	//CTemp* pTemp = temp.Create1();

	//CTemp(80).


	return 0;
}
