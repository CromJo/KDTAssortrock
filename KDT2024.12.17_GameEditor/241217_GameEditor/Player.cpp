#include "Player.h"

CPlayer::CPlayer()
{
	mType = ECharacterType::Player;
}

CPlayer::CPlayer(const CPlayer& Obj)	:
	CCharacter(Obj)
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
	system("cls");

	std::cout << "1. 기사" << std::endl;
	std::cout << "2. 궁수" << std::endl;
	std::cout << "3. 마법사" << std::endl;
	std::cout << "4. 도적" << std::endl;
	std::cout << "플레이어 캐릭터 선택 : ";

	int Input = 0;
	std::cin >> Input;
	mJob = (EJob)Input;

	CObject::Init();

	std::cout << "공격력 : ";
	std::cin >> mAttack;
	std::cout << "방어력 : ";
	std::cin >> mDefense;
	std::cout << "최대HP : ";
	std::cin >> mHPMax;
	std::cout << "최대MP : ";
	std::cin >> mMPMax;
	std::cout << "레벨 : ";
	std::cin >> mLevel;
	std::cout << "소지금 : ";
	std::cin >> mGold;

	mHP = mHPMax;
	mMP = mMPMax;

    return true;
}

void CPlayer::Output()
{
	CCharacter::Output();

	switch (mJob)
	{
	case EJob::Knight:
		std::cout << "직업 : 기사" << std::endl;
		break;
	case EJob::Archer:
		std::cout << "직업 : 궁수" << std::endl;
		break;
	case EJob::Magicion:
		std::cout << "직업 : 마법사" << std::endl;
		break;
	case EJob::Thief:
		std::cout << "직업 : 도적" << std::endl;
		break;
	}
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}
