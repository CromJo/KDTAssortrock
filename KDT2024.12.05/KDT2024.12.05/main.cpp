#include <iostream>
#include <string>

/*
	배열 : 하나의 타입을 같은 이름으로 여러개 만드는 것.
	구조체 : N개의 자료형 변수를 하나의 그룹으로 만드는 것.
		struct Type
		{ 
			int a = 0; 
			float b = 0.1f; 
			double c = 0.002f; 
		};
*/

enum class EItemType : unsigned char
{
	Weapon = 0,
	Armor,

	MAX
};

struct FState
{
	// 구조체 멤버 맞춤이 기본값으로 되어있다면,
	// 내가 선언한 자료형중 가장 큰 바이트의 변수로 맞춰지고,
	// 크기도 맞춤에 맞게 올라간다.
	// 변수의 선언 위치에 따라서 바이트의 범위가 달라질 수 있다.
	bool a;
	bool b;
	bool c;
	double ccc;
	bool d;
	int ef;
	bool e;
};

struct FItem
{
	// 문자열 사용시 문자열 배열의 끝은 0(null)로 저장되어야 한다.
	char Name[32];
	int Option;
	int Price;
	short shortty;
	EItemType ItemType;
};

// 함수의 선언
void OutputItem(FItem& item);
void OutputItem(const FItem& item);		// 8byte이상의 자료형을 사용할때 레퍼런스를 참조하여 사용하면 속도적인 측면을 향상 시킬 수 있다. 


int main()
{
	FItem item;
	FItem item2 = {"ㅇㅇ 형이야", 2, 4, 2, EItemType::Weapon };
	FItem& item3 = item;
	item.ItemType = EItemType::Weapon;
	item.Option = 100;
	item.Price = 1000;
	// strcpy : 문자열 복사함수. 2번째 매개변수의 문자열을 첫번째에게 붙여넣어주는 기능이다.
	strcpy_s(item.Name, "김치 워리어");

	// 레퍼런스 : 참조, 다른 변수를 참조하는 변수를 만들 수 있다.
	//			참조를 하게되면 해당 변수의 값을 변경할 수 있게 된다.
	//			참조 대상은 반드시 레퍼런스 선언과 동시에 지정되어야 한다.

	// RefNumber는 Number변수를 참조하게 되어 RefNumber를 이용하여 Number의 값을 변경할 수 있게 된다.
	int Number = 500;
	int Number1 = 100;
	int& RefNumber = Number;

	// 아래는 참조가 아니라 RefNumber가 참조하고 있는 Number 변수의 값을 
	// Number1의 값으로 "대입"해주는 것이다.
	RefNumber = Number1;

	OutputItem(item3);

	return 0;
}

// 함수의 구현
void OutputItem(const FItem& item)
{

}