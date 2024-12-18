#include "Monster.h"

CMonster::CMonster()
{
	mType = ECharacterType::Monster;
}

CMonster::CMonster(const CMonster& Obj) :
	CCharacter(Obj)
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init()
{
	CCharacter::Init();

	while (true)
	{
		std::cout << "1. 오크" << std::endl;
		std::cout << "2. 고블린" << std::endl;
		std::cout << "3. 타우렌" << std::endl;
		std::cout << "4. 슬라임" << std::endl;
		std::cout << "몬스터 캐릭터 선택 : ";

		int Input = 0;
		std::cin >> Input;

		if (Input < 1 || Input > 4)
			continue;

		mMob = (EMob)Input;
		break;
	}

	while (true)
	{
		std::cout << "1. 쉬움" << std::endl;
		std::cout << "2. 보통" << std::endl;
		std::cout << "3. 어려움" << std::endl;
		std::cout << "난이도를 선택하세요 : ";

		int Input = 0;
		std::cin >> Input;

		if (Input < 1 || Input > 3)
			continue;

		mBattleType = (EBattleType)(Input - 1);
		break;
	}

	return true;
}

bool CMonster::Init(FILE* File)
{
	CCharacter::Init(File);

	return true;
}

void CMonster::Save(FILE* File)
{
	CCharacter::Save(File);
}

void CMonster::Output()
{
	CCharacter::Output();

	switch (mMob)
	{
	case EMob::Orc:
		std::cout << "몬스터 정보 : 오크" << std::endl;
		break;
	case EMob::Goblin:
		std::cout << "몬스터 정보 : 고블린" << std::endl;
		break;
	case EMob::Taulen:
		std::cout << "몬스터 정보 : 타우렌" << std::endl;
		break;
	case EMob::Slime:
		std::cout << "몬스터 정보 : 슬라임" << std::endl;
		break;
	}
}

CMonster* CMonster::Clone()
{
    return new CMonster(*this);
}
