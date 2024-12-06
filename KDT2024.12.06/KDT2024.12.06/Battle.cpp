#include "Battle.h"

/// <summary>
/// 게임의 난이도 State
/// </summary>
enum EMode
{
	None = 0,
	Easy,
	Normal,
	Hard,
	Back
};

bool InitBattle()
{
	// 전추 기화에 관련된 코드를 작성한다.


	return true;
}

EMode BattleMenu()
{
	system("cls");
	std::cout << "1. 전투" << std::endl;
	std::cout << "2. 상점" << std::endl;
	std::cout << "3. 가방" << std::endl;
	std::cout << "4. 종료" << std::endl;
	std::cout << "메뉴 선택 : " << std::endl;

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