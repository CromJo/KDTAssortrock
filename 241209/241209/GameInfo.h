#pragma once

#include <iostream>

// #이 붙었기 때문에 전처리기이다.
// #define은 이름 뒤에 있는 코드를 이 이름을 사용한곳에
// 컴파일 전에 복사해주고 복사된 코드를 컴파일
// 하게 된다.
// #define은 뒤의 코드를 반드시 1줄로 작성해야 한다.
#define	LEVEL_MAX	10

#define	INVENTORY_MAX	10

//int	gTest1 = 500;
//static int	gTest1 = 500;

// #define에서 \ 를 붙여주면 아래에 있는 줄을
// 여기에 붙여준다.
#define	TEST1	std::cout << "Test" << std::endl;\
std::cout << "Test1" << std::endl;

#define	TEST2(str)	std::cout << str << std::endl;

//TEST2("출력")

enum class EJob	: unsigned char
{
	None,
	Knight,
	Archer,
	Magicion,
	End
};

struct FPlayer
{
	char	Name[32];
	EJob	Job;
	int		Attack;
	int		Defense;
	int		HP;
	int		HPMax;
	int		MP;
	int		MPMax;
	int		Level;
	int		Exp;
	int		Gold;
};

struct FMonster
{
	char	Name[32];
	int		Attack;
	int		Defense;
	int		HP;
	int		HPMax;
	int		MP;
	int		MPMax;
	int		Level;
	int		Exp;
	int		Gold;
};

enum EItemType
{
	Item_Weapon,
	Item_Armor,
	Item_End
};

struct FItem
{
	char		Name[32];
	EItemType	Type;
	int			Option;
	int			Buy;
	int			Sell;
};
