#include <iostream>

/*
	���ø� ��������(Variadic template);
	���ø� Ÿ���� �������ڷ� ����,
	Ÿ���� ���������� �޾ƿ� �� �ִ� ����̴�.
	template <typename T, typename... Types>
	struct FTest10
	{
	};

	template <typename T, typename... Types>
	T TestVariadic(T Param, Types... Params)
	{
		return Param + TestVariadic(Params);
	}
	// ����Լ� �������� ȣ��� �Լ�.
	template <typename T>
	T TestVariadic(T Param)
	{
		return Param;
	}
*/

// ��Ÿ������ Ȱ���
// template <int... Numbers>


// �������ִ� �ڷ���
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
	// ������ ó�� �� Ŭ����/�Լ��� ��� �Ϸ��� ������ ������ ��� ���ø��� ����������Ѵ�.
	// private�� ���ٰ����ϰ� �ϱ� ���� ��� : friend
	template<typename T1, typename T2>
	friend class FTest;

public:
	// Ŭ������ ���ø��� �������� �ʴ���, �����Լ����� ���ø��� ������ �� �ִ�.
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

// ��Ÿ�����ø� ����
/*
	��Ÿ�� ���ø� ���ڴ� �������� �Ѵ�. (const)
	������ Ÿ�ӿ� � ���� ���� �����ǰ�, 
	����� ��޹��� �� �ִ� ���̴�.
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
/// �����
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

	// ����ġ���� ������ :
	//	1. �ӵ��� ���� �� �ִ� (������ ���� ��� ������)
	//	2. ���������� �����. (�ø������� ���̽����� �þ���� �� �������� �� ����)
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
	template <typename ���ϴ� �̸�>
	template <class ���ϴ� �̸�>
	template <typename ���ϴ� �̸�1, typename ���ϴ� �̸�2>
	������ ���ø� ���� ����

	���ϴ� �̸� <-- ���� Ÿ���� �ȴ�.
	������ Ÿ�ӿ� Ÿ���� ���� �ȴ�.

*/
template <typename T>
T Add(T Num1, T Num2)
{
	// typeid : �� Ÿ���� �������� �� ���ְ� ���ش�.
	std::cout << "Type : " << typeid(T).name() << std::endl;
	return Num1 + Num2;
}

template <typename T>
void OutputType(T Template)
{
	std::cout << typeid(T).name() << std::endl;
}

/*
	���ø� Ư��ȭ : Ư�� Ÿ�Ը� �ٸ� ������� ó���ϱ�
					���� ���Ǵ� �����̴�.
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
	// ���ø� & ���۷�����
	// ���ø��� ������ �Լ��� ȣ�� �Ҷ� 2������ ȣ�� ������ִ�.
	// 1. Ÿ���� ��������� �����ϴ� ���
	// 2. ���ڿ� �� �������� Ÿ���� �Ͻ������� �����ϴ� ���.
	std::cout << Add<float>(3.14f, 223.551f) << std::endl;
	std::cout << Add(10, 20) << std::endl;

	// ����ü ���ø� ���� ���
	// �ڷ����� �����Ͽ��� �Ѵ�.
	FTest<int, float> Test1;
	FTest<int> Test2;			// �Ű�����2����� short�� ������ �̸� ������. (������ ������ short�� ����)

	Test1.Output();
	Test2.Output();
	Test2.OutputTemplate<char>();

	CTest1 Test3;
	Test3.Output<int>(10);		// ����� ����ȯ
	Test3.Output<short>(10.2f);	// ����� ����ȯ
	Test3.Output(3.14f);		// �Ͻ��� ����ȯ

	CPlayer* Player = CreateCObject<CPlayer>();
	CMonster* Monster = CreateCObject<CMonster>();

	// ���� �����ϵ��� ��밡��.
	TestTypeTemplate<300>();
	TestTypeTemplate<500>();
	TestTypeTemplate1<800>();
	TestTypeTemplate1();		// Ÿ��

	// Ÿ�Ӿ����� ����̶�
	std::cout << Add<int>(35, 50) << td::endl;
	std::cout << Add("ABC : ", "BCD : ")

	return 0;
}