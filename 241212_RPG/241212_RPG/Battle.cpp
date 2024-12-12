#include "Battle.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"

/*
	배틀 만들기
	1. 플레이어가 공격을 한다.
	2. 상대는 (플레이어 공격력 - 몬스터 방어력 (대미지 1이하 X))의 대미지를 입는다.
	3. 화면에 보이는 결과값들을 새로고침 한다. (다시 그려준다.)
*/

CBattle::CBattle()
{
}

CBattle::~CBattle()
{
}

/// <summary>
/// 할 수 있는 행동들을 보여주는 기능
/// </summary>
void SelectAction()
{
	std::cout << "1. 공격" << "\t\t2. 방어" << std::endl;
	std::cout << "3. 소모품" << "\t4. 도망" << std::endl;
}

/// <summary>
/// 행동이 골라진 후 그 행동에 맞는 결과를 실행 합니다.
/// </summary>
void ConsequencesOfActions(int Action, CPlayer* Player, CMonster* Monster)
{
	switch (Action)
	{
	case (int)Action::Attack:
		break;
	case (int)Action::Defense:
		break;
	case (int)Action::Consumables:
		break;
	case (int)Action::Escape:
		break;
	default:
		break;
	}
}

/// <summary>
/// 현재 난이도를 세팅합니다.
/// </summary>
/// <param name="Type"></param>
void CBattle::SetBattleType(EBattleType Type)
{
	mType = Type;
}

void CBattle::Run()
{
	// 플레이어를 얻어온다.
	CPlayer* Player = CObjectManager::GetInst()->GetPlayer();
	// 몬스터를 불러온다.
	CMonster* Monster = CObjectManager::GetInst()->CreateMonster(mType);

	while (true)
	{
		system("cls");

		// 플레이어와 몬스터를 출력해준다.
		Player->Output();
		Monster->Output();
		
		// 전투 (내가 만들고 있던 것)
		//SelectAction();			// 행동 선택 기능
		//int Action = Player->SelectInput();	// 플레이어가 행동을 고릅니다.
		//ConsequencesOfActions(Action);		// 액션을 실행합니다.
	
		// 전투 (선생님께서 만든 부분)



		std::cout << "1. 공격" << std::endl;
		std::cout << "2. 뒤로가기" << std::endl;
		std::cout << "메뉴를 선택하세요 : ";

		int Input;
		std::cin >> Input;

		if (Input < 1 || Input > 2)
			continue;

		else if (Input == 2)
		{
			SAFE_DELETE(Monster);
			break;
		}

		int Damage = Player->GetAttack() - Monster->GetDefense();
		
		Damage = Damage < 1 ? 1 : Damage;

		// 죽었을 때 true / 살았을 때 false를 반환
		if (Monster->Damage(Damage))
		{
			Player->AddExp(Monster->GetExp());
			Player->AddGold(Monster->GetGold());
			// 몬스터 제거 후 다시 생성
			SAFE_DELETE(Monster);
			Monster = CObjectManager::GetInst()->CreateMonster(mType);

			continue;
		}

		Damage = Monster->GetAttack() - Player->GetDefense();

		Damage = Damage < 1 ? 1 : Damage;

		if (Player->Damage(Damage))
		{
			Player->Resurrection();
		}
	}
}