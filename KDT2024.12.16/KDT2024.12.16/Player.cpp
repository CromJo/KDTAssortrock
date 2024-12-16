#include "Player.h"
#include "Item.h"
#include "Bash.h"

int gLevelUpTable[LEVEL_MAX - 1] =
{
	3000,
	5000,
	10000,
	20000,
	35000,
	55000,
	80000,
	110000,
	150000
};

CPlayer::CPlayer()
{
}

CPlayer::CPlayer(const CPlayer& Obj)
{
}

CPlayer::~CPlayer()
{
}

int CPlayer::GetAttack()
{
	int	Attack = mAttack;

	return Attack;
}

int CPlayer::GetDefense()
{
	int	Defense = mDefense;
	return Defense;
}

CItem* CPlayer::Equip(CItem* Item)
{
	EEquip::Type	EquipType;

	CItem* ReturnItem = nullptr;

	return ReturnItem;
}

bool CPlayer::Init()
{
	std::cout << "이름 : ";
	std::cin >> mName;

	while (true)
	{
		std::cout << "1. 기사" << std::endl;
		std::cout << "2. 궁수" << std::endl;
		std::cout << "3. 마법사" << std::endl;
		std::cout << "직업을 선택하세요 : ";
		int	Job = 0;
		std::cin >> Job;

		if (Job <= (int)EJob::None ||
			Job >= (int)EJob::End)
			continue;

		mJob = (EJob)Job;
		break;
	}

	switch (mJob)
	{
	case EJob::Knight:
		mAttack = 40;
		mDefense = 20;
		mHP = 500;
		mHPMax = 500;
		mMP = 100;
		mMPMax = 100;
		break;
	case EJob::Archer:
		mAttack = 50;
		mDefense = 15;
		mHP = 400;
		mHPMax = 400;
		mMP = 200;
		mMPMax = 200;
		break;
	case EJob::Magicion:
		mAttack = 60;
		mDefense = 10;
		mHP = 300;
		mHPMax = 300;
		mMP = 300;
		mMPMax = 300;
		break;
	}

	mLevel = 1;
	mExp = 0;
	mGold = 10000;

	mSkillArray[0] = new CSkillActive

    return true;
}

CPlayer* CPlayer::Clone()
{
	return new CPlayer(*this);
}

void CPlayer::Output()
{
	std::cout << "------------------플레이어 정보------------------" << std::endl;

	switch (mJob)
	{
	case EJob::Knight:
		std::cout << "직업 : 기사" << std::endl;
		break;
	case EJob::Archer:
		std::cout << "직업 :궁수" << std::endl;
		break;
	case EJob::Magicion:
		std::cout << "직업 :마법사" << std::endl;
		break;
	}

	CCharacter::Output();
	mMP -= mSkillArray[0]->GetMP();

	int Attack = mAttack + mSkillArray[0]->GetAttack();

}
