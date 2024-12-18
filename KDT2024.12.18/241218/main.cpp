
#include <iostream>

class CParent
{
public:
	int  mA;

public:
	virtual void Output()	const
	{
		//mA = 200;
	}
};

class CChild : public CParent
{
public:
	int	mB;

public:
	virtual void Output()
	{
		mB = 10;
	}
};

class CTest
{
public:
	CTest()
	{
		std::cout << "CTest 생성자" << std::endl;
	}

	CTest(const CTest& ref)
	{
	}

	~CTest()
	{
		std::cout << "CTest 소멸자" << std::endl;
	}

public:
	int  mA;

public:
	CTest Create()
	{
		CTest test;

		test.mA = 200;

		// 리턴시 임시객체가 생성될 수 있다.
		return test;
	}
};

class CArray
{
public:
	int  mA[1000];

public:
	void SetData()	const
	{
		// 이 함수는 뒤에 const가 붙었기 때문에
		// 멤버변수의 값을 변경할 수 없다.
		//mA[10] = 500;
	}

	void SetData1()
	{
	}
};

void OutputArray(const CArray& array)
{
	for (int i = 0; i < 1000; ++i)
	{
		std::cout << array.mA[i] << std::endl;
	}
}

class CSingleton
{
private:
	CSingleton()
	{
	}

	~CSingleton()
	{
	}

private:
	static CSingleton* mInst;

public:
	static CSingleton* GetInst()
	{
		if (!mInst)
			mInst = new CSingleton;
		return mInst;
	}

	static void DestroyInst()
	{
		if (mInst)
		{
			delete mInst;
			mInst = nullptr;
		}
	}
};

CSingleton* CSingleton::mInst = nullptr;

/*
	데이터 : 시작과 끝	   (절대 안사라짐)
	코드 : 내가 친 코드덩어리들을 컴퓨터언어로 전환
	스택 : 컴퓨터가 처리 (소멸도 가능)
	힙 : 반환값
*/

int main()
{
	int	Num1 = 100;
	int	Num2 = 200;

	int& Ref = Num1;
	// Num2의 값을 참조하고 있는 Num1에 대입해준다.
	Ref = Num2;

	CTest	test;

	test.mA = 100;

	const CTest	ctest;

	CTest	test2(ctest);
	CTest	test1(test);

	// 객체 복사가 일어난다.
	//CTest test1 = test.Create();

	//std::cout << test1->mA << std::endl;

	std::cout << sizeof(CChild) << std::endl;


	CArray	arr;

	OutputArray(arr);

	arr.SetData();
	arr.SetData1();

	const CArray	arr1;

	arr1.SetData();
	// const 객체는 함수 뒤에 const가 붙은 함수만
	// 호출이 가능하다.
	//arr1.SetData1();

	CChild	child;

	child.Output();

	return 0;
}