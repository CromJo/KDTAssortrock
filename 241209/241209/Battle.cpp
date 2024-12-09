
#include "Battle.h"

int	gLevelUpTable[LEVEL_MAX - 1] =
{
	2000,
	5000,
	10000,
	18000,
	30000,
	45000,
	65000,
	90000,
	150000
};

enum EMap
{
	None,
	Easy,
	Normal,
	Hard,
	Back
};

enum class EBattleMenu : unsigned char
{
	None,
	Attack,
	Back
};

enum class EBattleResult : unsigned char
{
	None,
	PlayerDeath,
	MonsterDeath
};

bool InitBattle()
{
	// 전투 초기화에 관련된 코드를 작성한다.

	return true;
}

EMap BattleMenu()
{
	system("cls");
	std::cout << "1. 쉬움" << std::endl;
	std::cout << "2. 보통" << std::endl;
	std::cout << "3. 어려움" << std::endl;
	std::cout << "4. 뒤로가기" << std::endl;
	std::cout << "메뉴 선택 : ";

	int SelectMenu = 0;

	std::cin >> SelectMenu;

	// 잘못된 메뉴를 선택했을 경우
	if (SelectMenu <= EMap::None ||
		SelectMenu > EMap::Back)
		return EMap::None;

	return (EMap)SelectMenu;
}

// 인자로 들어오는 난이도에 따라 Monster를 생성한다.
FMonster* CreateMonster(EMap Map)
{
	// 몬스터를 동적할당하고 메모리 주소를 포인터변수에
	// 넣어준다.
	FMonster* Monster = new FMonster;

	switch (Map)
	{
	case Easy:
		strcpy_s(Monster->Name, "고블린");
		Monster->Attack = 30;
		Monster->Defense = 10;
		Monster->HP = 100;
		Monster->HPMax = 100;
		Monster->MP = 10;
		Monster->MPMax = 10;
		Monster->Level = 1;
		Monster->Exp = 1000;
		Monster->Gold = 1000;
		break;
	case Normal:
		strcpy_s(Monster->Name, "오크");
		Monster->Attack = 70;
		Monster->Defense = 40;
		Monster->HP = 600;
		Monster->HPMax = 600;
		Monster->MP = 100;
		Monster->MPMax = 100;
		Monster->Level = 5;
		Monster->Exp = 5000;
		Monster->Gold = 5000;
		break;
	case Hard:
		strcpy_s(Monster->Name, "드래곤");
		Monster->Attack = 200;
		Monster->Defense = 150;
		Monster->HP = 2000;
		Monster->HPMax = 2000;
		Monster->MP = 1000;
		Monster->MPMax = 1000;
		Monster->Level = 10;
		Monster->Exp = 10000;
		Monster->Gold = 10000;
		break;
	}

	return Monster;
}

void OutputPlayer(FPlayer* Player)
{
	std::cout << "이름 : " << Player->Name << "\t" <<
		"직업 : ";

	switch (Player->Job)
	{
	case EJob::Knight:
		std::cout << "기사" << std::endl;
		break;
	case EJob::Archer:
		std::cout << "궁수" << std::endl;
		break;
	case EJob::Magicion:
		std::cout << "마법사" << std::endl;
		break;
	}

	std::cout << "레벨 : " << Player->Level << 
		"\t경험치 : " << Player->Exp << " / " <<
		gLevelUpTable[Player->Level - 1] << std::endl;
	std::cout << "공격력 : " << Player->Attack <<
		"\t방어력 : " << Player->Defense << std::endl;
	std::cout << "체력 : " << Player->HP << " / " <<
		Player->HPMax << "\t마나 : " << Player->MP <<
		" / " << Player->MPMax << std::endl;
	std::cout << "Gold : " << Player->Gold << std::endl;
}

void OutputMonster(FMonster* Monster)
{
	std::cout << "이름 : " << Monster->Name << std::endl;

	std::cout << "레벨 : " << Monster->Level <<
		"\t경험치 : " << Monster->Exp  << std::endl;
	std::cout << "공격력 : " << Monster->Attack <<
		"\t방어력 : " << Monster->Defense << std::endl;
	std::cout << "체력 : " << Monster->HP << " / " <<
		Monster->HPMax << "\t마나 : " << Monster->MP <<
		" / " << Monster->MPMax << std::endl;
	std::cout << "Gold : " << Monster->Gold << std::endl;
}

EBattleResult Battle(FPlayer* Player, FMonster* Monster)
{
	// 플레이어 공격
	int	Damage = Player->Attack - Monster->Defense;

	// 삼항연산자 : 조건식 ? true일때 : false일때
	Damage = Damage < 1 ? 1 : Damage;

	std::cout << Monster->Name << " 에게 " <<
		Damage << " 피해를 입혔습니다." << std::endl;

	Monster->HP -= Damage;

	if (Monster->HP <= 0)
		return EBattleResult::MonsterDeath;

	// 몬스터 공격
	Damage = Monster->Attack - Player->Defense;
	Damage = Damage < 1 ? 1 : Damage;

	Player->HP -= Damage;

	std::cout << Monster->Name << " 에게 " <<
		Damage << " 피해를 입었습니다." << std::endl;

	if (Player->HP <= 0)
		return EBattleResult::PlayerDeath;

	return EBattleResult::None;
}

void RunStage(EMap Map, FPlayer* Player)
{
	FMonster* Monster = CreateMonster(Map);

	while (true)
	{
		system("cls");

		// 플레이어 정보 출력
		std::cout << "=============== Player ===============" << std::endl;
		OutputPlayer(Player);
		std::cout << std::endl;

		std::cout << "=============== Monster ===============" << std::endl;
		OutputMonster(Monster);
		std::cout << std::endl;

		std::cout << "1. 공격" << std::endl;
		std::cout << "2. 도망가기" << std::endl;
		std::cout << "메뉴를 선택하세요 : ";
		int	Input;
		std::cin >> Input;

		if (Input == (int)EBattleMenu::Back)
		{
			delete Monster;
			return;
		}

		// 잘못된 입력일 경우 다시 입력받게 한다.
		else if (Input <= (int)EBattleMenu::None ||
			Input > (int)EBattleMenu::Back)
			continue;

		switch (Battle(Player, Monster))
		{
		case EBattleResult::PlayerDeath:
			Player->HP = Player->HPMax;
			Player->MP = Player->MPMax;
			Player->Exp *= 0.9f;
			Player->Gold *= 0.9f;
			break;
		case EBattleResult::MonsterDeath:
			Player->Exp += Monster->Exp;

			if (Player->Level < LEVEL_MAX)
			{
				if (Player->Exp >=
					gLevelUpTable[Player->Level - 1])
				{
					Player->Exp -= gLevelUpTable[Player->Level - 1];
					++Player->Level;
					Player->Attack *= 1.2f;
					Player->Defense *= 1.2f;
					Player->HPMax *= 1.2f;
					Player->MPMax *= 1.2f;
					Player->HP = Player->HPMax;
					Player->MP = Player->MPMax;
				}
			}

			Player->Gold += Monster->Gold;
			// 몬스터를 제거한다.
			delete Monster;
			Monster = CreateMonster(Map);
			break;
		}

		// pause : 일시정지 명령. 키 누를때까지 대기
		system("pause");
	}
}

/*
전투 쉬움, 보통, 어려움에 따라 몬스터의 능력치를
다르게 설정한다.
플레이어가 먼저 공격을 하면
플레이어공격력 - 몬스터 방어력 만큼 몬스터의 체력을
감소시킨다.
이때, 플레이어의 공격력보다 몬스터의 방어력이 높다면
- 값이 나오므로 이 경우 최소 데미지인 1이 나오게 한다.
*/
void RunBattle(FPlayer* Player)
{
	while (true)
	{
		EMap	Menu = BattleMenu();

		if (Menu == EMap::Back)
			return;

		else if (Menu == EMap::None)
			continue;

		RunStage(Menu, Player);
	}
}
