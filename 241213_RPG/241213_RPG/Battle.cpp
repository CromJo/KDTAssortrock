#include "Battle.h"
#include "ObjectManager.h"
#include "Player.h"

CBattle::CBattle()
{
}

CBattle::~CBattle()
{
}

void CBattle::SetBattleType(EBattleType Type)
{
	mType = Type;
}

void CBattle::Run()
{
	// 플레이어를 얻어온다.
	CPlayer* Player = CObjectManager::GetInst()->GetPlayer();

	CMonster* Monster = CObjectManager::GetInst()->CreateMonster(mType);

	while (true)
	{
		system("cls");

		Player->Output();

		Monster->Output();

		std::cout << "1. 공격" << std::endl;
		std::cout << "2. 뒤로가기" << std::endl;
		std::cout << "메뉴를 선택하세요 : ";
		int	Input;
		std::cin >> Input;

		if (Input < 1 || Input > 2)
			continue;

		else if (Input == 2)
		{
			SAFE_DELETE(Monster);
			break;
		}

		// 전투
		int	Damage = Player->GetAttack() -
			Monster->GetDefense();

		Damage = Damage < 1 ? 1 : Damage;

		// Monster의 Damage 함수는 죽었을 때 true
		// 살아있을 때 false를 반환한다.
		if (Monster->Damage(Damage))
		{
			Player->AddExp(Monster->GetExp());
			Player->AddGold(Monster->GetGold());
			// 몬스터를 제거하고 다시 생성한다.
			SAFE_DELETE(Monster);
			Monster = 
				CObjectManager::GetInst()->CreateMonster(mType);

			continue;
		}

		Damage = Monster->GetAttack() -
			Player->GetDefense();

		Damage = Damage < 1 ? 1 : Damage;

		if (Player->Damage(Damage))
		{
			Player->Resurrection();
		}
	}
}
