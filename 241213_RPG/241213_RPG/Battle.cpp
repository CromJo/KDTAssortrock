#include "Battle.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"

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

void CBattle::SetBattleState(EBattleState State)
{
	mState = State;
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
		std::cout << "2. 스킬" << std::endl;
		std::cout << "3. 뒤로가기" << std::endl;
		std::cout << "메뉴를 선택하세요 : ";
		int	Input;
		std::cin >> Input;

		if (Input < (int)EBattleState::None || Input > (int)EBattleState::Back)
			continue;

		int Damage = 0;

		switch (Input)
		{
		case (int)EBattleState::None:
			break;
		case (int)EBattleState::Attack:
			// 전투
			Damage = Player->GetAttack() - Monster->GetDefense();
			Damage = Damage < 1 ? 1 : Damage;

			break;
		case (int)EBattleState::Skill:
			Damage = 
			break;
		case (int)EBattleState::Back:
			SAFE_DELETE(Monster);

			return;
		}

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
