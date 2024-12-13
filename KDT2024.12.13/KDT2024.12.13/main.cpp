
#include <iostream>

/*
클래스 상속 : 부모클래스의 멤버를 자식클래스가 물려
받아 사용할 수 있게 해주는 기능이다.

private : 자기자신 내부에서 접근 가능하고 외부 혹은
자식클래스 내부에서는 접근이 불가능하다.
protected : 자기자신 내부 및 자식클래스 내부에서는
접근이 가능하고 외부에서는 접근이 불가능하다.

상속 관계에서 생성자와 소멸자의 호출 순서
생성자 : 부모 -> 자식
소멸자 : 자식 -> 부모

RTTI(Real Time Type Information)
다형성 : 부모와 자식 사이의 형변환이
가능한 성질을 말한다.

업캐스팅 : 자식타입을 부모타입으로 형변환
다운캐스팅 : 부모타입을 자식타입으로 형변환

일반 멤버함수 호출 : 일반 멤버함수는 함수 호출 시
해당 함수의 주소를 바로 호출을 하게 된다.

가상함수 테이블 : 클래스 타입마다 만들어지게 된다.
가상함수들의 메모리 주소를 저장하기 위한 배열이다.

가상함수 : 클래스의 멤버함수에 virtual 키워드를
붙여주면 해당 멤버함수는 가상함수가 된다.

가상함수를 만들게 되면 가상함수 테이블이 만들어진다.
따라서 가상함수를 호출하게 되면 일반 함수처럼 바로
메모리주소로 콜 하는 것이 아니라 먼저 가상함수테이블
을 참조하여 거기에 있는 메모리 주소로 함수를
호출하게 된다.
가상함수 테이블에 저장되는 주소는 가상함수를
자식클래스에 재정의 했다면 자식 함수의 메모리 주소가
들어가게 되고 재정의가 없다면 부모 함수의 메모리
주소가 저장되게 된다.
*/
class CParent
{
public:
	CParent()
	{
		mB = 500;
		std::cout << "CParent 생성자" << std::endl;
	}

	virtual ~CParent()
	{
		std::cout << "CParent 소멸자" << std::endl;
	}

public:
	int		mA;

private:
	int		mB;

protected:
	int		mC;

public:
	virtual void Output()
	{
		std::cout << "CParent Output" << std::endl;
	}
};

class CChild : public CParent
{
public:
	CChild()
	{
		//mB = 1020;
		mC = 10203;
		std::cout << "CChild 생성자" << std::endl;
	}

	~CChild()
	{
		std::cout << "CChild 소멸자" << std::endl;
	}

public:
	int		mD;

public:
	/*
	함수 재정의(함수 오버라이딩) : 부모의 함수를
	자식클래스에 완전히 동일한 형태로 다시
	정의하는것을 말한다.
	*/
	void Output()
	{
		CParent::Output();
		std::cout << "CChild Output" << std::endl;
	}
};

class CChild1 : public CParent
{
public:
	CChild1()
	{
		std::cout << "CChild1 생성자" << std::endl;
	}

	~CChild1()
	{
		std::cout << "CChild1 소멸자" << std::endl;
	}
};

class CChildChild : public CChild
{
public:
	CChildChild()
	{
		std::cout << "CChildChild 생성자" << std::endl;
	}

	~CChildChild()
	{
		std::cout << "CChildChild 소멸자" << std::endl;
	}

public:
	int		mNumber = 100;
};

class CTest
{
};

int main()
{
	std::cout << sizeof(CTest) << std::endl;
	std::cout << sizeof(CParent) << std::endl;

	// new CChild를 해주어서 CChild타입의 메모리
	// 크기만큼 힙에 공간을 할당하고 그 주소를
	// 반환해준다. 그런데 CChild포인터타입을
	// CParent포인터타입으로 대입을 해주고 있다.
	// 아래는 업캐스팅이 되고 있다.
	CParent* Child = new CChild;
	CParent* Child1 = new CChild1;

	CParent* Array[10] = {};
	Array[0] = Child;
	Array[1] = Child1;

	Array[0]->Output();
	Array[1]->Output();

	//CChild* ChildError = (CChild*)Child1;

	// dynamic_cast : 다운캐스팅을 할 때 잘못된
	// 타입으로 캐스팅이 일어날 경우 nullptr을
	// 반환하고 정상적인 형변환일 경우 해당 메모리
	// 주소를 반환한다.
	CChild* ChildError = dynamic_cast<CChild*>(Child1);
	CChild1* ChildError1 = dynamic_cast<CChild1*>(Child1);

	//ChildError->mD = 500;


	// Child1은 CParent 포인터타입 변수이다.
	// 이를 CChild1 포인터타입 변수로 형변환
	// 하고 있다.(다운캐스팅)
	CChild1* Child11 = (CChild1*)Child1;


	delete Child;
	delete Child1;

	//CParent parent;
	//CChild	child;
	//CChild1	child1;

	//child1.mA = 1020;
	////child.CParent::Output();
	//child.Output();
	//child1.Output();

	//child.mC = 1020;

	return 0;
}
