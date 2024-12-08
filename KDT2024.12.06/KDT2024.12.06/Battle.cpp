#include "Battle.h"

bool InitBattle()
{
	FMonster Monster;

	if (!MonsterInit(&Monster))
		return false;


	// 몬스터 초기화가 성공하면 하위 구문 실행.
	std::cout << "몬스터 이름 : " << Monster.Name << std::endl;
	std::cout << "몬스터 체력 : " << Monster.HP << std::endl;
	std::cout << "몬스터 공격력 : " << Monster.Attack << std::endl;
	std::cout << "몬스터 방어력 : " << Monster.Defense << std::endl;

	return true;
}

EMode BattleMenu()
{
	system("cls");
	std::cout << "1. 쉬움" << std::endl;
	std::cout << "2. 보통" << std::endl;
	std::cout << "3. 어려움" << std::endl;
	std::cout << "4. 뒤로가기" << std::endl;
	std::cout << "메뉴 선택 : ";

	int SelectLevel = 0;

	std::cin >> SelectLevel;

	if (SelectLevel <= EMode::None || SelectLevel > EMode::Back)
		return EMode::None;

	// 정상적으로 선택을 했다면,
	return (EMode)SelectLevel;
}

/*
	1. 전투 쉬움, 보통 어려움에 따라 몬스터 능력치를 다르게 설정.
	2. 플레이어가 먼저 공격을 하면 플레이어 공격력 - 몬스터 방어력 만큼 몬스터 체력 감소.
	3. 이때, 플레이어의 공격력보다 몬스터의 방어력이 높다면 - 값이 나오므로, 이 경우 최소 대미지 1이 나오게 한다.
*/

bool MonsterInit(FMonster* Monster)
{
	srand(time(0));

	EMode Level = BattleMenu();
	switch (Level)
	{
	case Easy:
		strcpy_s(Monster->Name, "슬라임");		// 이름 설정
		Monster->Attack = 10;					// 공격력 설정
		Monster->Defense = 2;					// 방어력 설정
		Monster->HPMax = 100;						// 최대 체력 설정
		Monster->HP = Monster->HPMax;						// 체력 설정
		Monster->Gold = rand() % 100;	// 난이도에 따른 골드 금액 설정
		break;
	case Normal:
		strcpy_s(Monster->Name, "고블린");		// 이름 설정
		Monster->Attack = 15;					// 공격력 설정
		Monster->Defense = 5;					// 방어력 설정
		Monster->HPMax = 120;						// 최대 체력 설정
		Monster->HP = Monster->HPMax;						// 체력 설정
		Monster->Gold = rand() % 125;	// 난이도에 따른 골드 금액 설정

		break;
	case Hard:
		strcpy_s(Monster->Name, "오크");		// 이름 설정
		Monster->Attack = 30;					// 공격력 설정
		Monster->Defense = 10;					// 방어력 설정
		Monster->HPMax = 200;						// 최대 체력 설정
		Monster->HP = Monster->HPMax;						// 체력 설정
		Monster->Gold = rand() % 180;	// 난이도에 따른 골드 금액 설정
		break;
	case Back:
		break;
	}
	
	return true;
}

/// <summary>
/// 배틀 실행용 구현부 함수
/// 종료시 배틀을 종료합니다.
/// </summary>
void RunBattle()
{
	while (true)
	{
		switch (BattleMenu())
		{

		case Easy:
			InitBattle();

			break;
		case Normal:
			break;
		case Hard:
			break;
		case Back:
			break;
		default:
			return;
		}
	}
}