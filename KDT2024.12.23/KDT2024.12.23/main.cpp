#include <iostream>

/*
	템플릿 가변인자(Variadic template);
	템플릿 타입을 가변인자로 만들어서,
	타입을 가변적으로 받아올 수 있는 기능이다.
	template <typename T, typename... Types>
	struct FTest10
	{
	};

	template <typename T, typename... Types>
	T TestVariadic(T Param, Types... Params)
	{
		return Param + TestVariadic(Params);
	}
	// 재귀함수 마지막에 호출될 함수.
	template <typename T>
	T TestVariadic(T Param)
	{
		return Param;
	}
*/

// 비타입인자 활용법
// template <int... Numbers>


// 정해져있는 자료형
template <typename T1, typename T2 = short>
struct FTest
{
	int Test1;
	int Test2;
	T1 Test3;
	T2 Test4;

public:
	void Output()
	{
		std::cout << "T1 : " << typeid(T).name() << std::endl;
		std::cout << "T2 : " << typeid(T).name() << std::endl;
	}

public:
	template <typename T3>
	void OutputTemplate(T3 Template2)
	{
		std::cout << "T3 : " << typeid(T3).name() << std::endl;
	}
};

class CTest1
{
	// 프렌드 처리 된 클래스/함수를 사용 하려면 프렌드 선언한 라면 템플릿을 선언해줘야한다.
	// private을 접근가능하게 하기 위한 기능 : friend
	template<typename T1, typename T2>
	friend class FTest;

public:
	// 클래스에 템플릿을 선언하지 않더라도, 내부함수에만 템플릿을 설정할 수 있다.
	template <typename T>
	void Output(T Template)
	{

	}
};

class CObject
{
};

class CPlayer : public CObject
{
};

class CMonster : public CObject
{
};

class CItem : public CObject
{
};

// 비타입템플릿 인자
/*
	비타입 템플릿 인자는 상수로취급 한다. (const)
	컴파일 타임에 어떤 값이 들어갈지 결정되겡, 
	상수로 취급받을 수 있는 것이다.
*/
template <int Number>
void TestTypeTemplate()
{
	int Count = 100;
	int Array[Number] = {};
	std::cout << Number << std::endl;
}

template <int Number = 1000>
void TestTypeTemplate1()
{
	std::cout << Number << std::endl;
}

/// <summary>
/// 응용법
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="Number"></typeparam>
/// <returns></returns>
template <typename T, int Number = 1000>
T* CreateArray()
{
	T* Array = new T[Number];

	return Array;
}




template <typename T>
T* CreateCObject()
{
	T* Obj = new T;

	return Obj;
}

enum class EObjectType
{
	Player,
	Monster,
	Item
};

CObject* CreateObject(EObjectType Type)
{
	CObject* Obj = nullptr;

	// 스위치문의 문제점 :
	//	1. 속도가 느릴 수 있다 (순차적 접근 방식 때문에)
	//	2. 유지보수가 힘들다. (늘릴때마다 케이스문이 늘어남으로 써 난잡해질 수 있음)
	switch (Type)
	{
	case EObjectType::Player:
		Obj = new CPlayer;
		break;
	case EObjectType::Monster:
		Obj = new CMonster;
		break;
	case EObjectType::Item:
		Obj = new CItem;
		break;
	}
}

/*
	template <typename 원하는 이름>
	template <class 원하는 이름>
	template <typename 원하는 이름1, typename 원하는 이름2>
	등으로 템플릿 선언 가능

	원하는 이름 <-- 변수 타입이 된다.
	컴파일 타임에 타입이 결정 된다.

*/
template <typename T>
T Add(T Num1, T Num2)
{
	// typeid : 이 타입이 무엇인지 알 수있게 해준다.
	std::cout << "Type : " << typeid(T).name() << std::endl;
	return Num1 + Num2;
}

template <typename T>
void OutputType(T Template)
{
	std::cout << typeid(T).name() << std::endl;
}

/*
	템플릿 특수화 : 특정 타입만 다른 방식으로 처리하기
					위해 사용되는 문법이다.
*/
template <>
const char* Add(const char* Num1, const char* Num2)
{
	static char* Text[256] = {};
	//memset(Text, 0, 256);

	strcpy_s(Text, Num1);
	strcat_s(Text, Num2);

	return Text;
}

int main()
{
	// 템플릿 & 오퍼레이터
	// 템플릿이 지정된 함수를 호출 할때 2가지의 호출 방법이있다.
	// 1. 타입을 명시적으로 지정하는 방법
	// 2. 인자에 들어간 데이터의 타입을 암시적으로 지정하는 방법.
	std::cout << Add<float>(3.14f, 223.551f) << std::endl;
	std::cout << Add(10, 20) << std::endl;

	// 구조체 템플릿 선언 방법
	// 자료형을 지정하여야 한다.
	FTest<int, float> Test1;
	FTest<int> Test2;			// 매개변수2번재는 short로 선언을 미리 해줬음. (선언이 없을땐 short로 잡힘)

	Test1.Output();
	Test2.Output();
	Test2.OutputTemplate<char>();

	CTest1 Test3;
	Test3.Output<int>(10);		// 명시적 형변환
	Test3.Output<short>(10.2f);	// 명시적 형변환
	Test3.Output(3.14f);		// 암시적 형변환

	CPlayer* Player = CreateCObject<CPlayer>();
	CMonster* Monster = CreateCObject<CMonster>();

	// 인자 전달하듯이 사용가능.
	TestTypeTemplate<300>();
	TestTypeTemplate<500>();
	TestTypeTemplate1<800>();
	TestTypeTemplate1();		// 타입

	// 타임업무터 사용이란
	std::cout << Add<int>(35, 50) << td::endl;
	std::cout << Add("ABC : ", "BCD : ")

	return 0;
}