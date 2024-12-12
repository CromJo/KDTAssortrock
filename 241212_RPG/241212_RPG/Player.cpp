#include "Player.h"

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

CPlayer::~CPlayer()
{
}

/// <summary>
/// 입력하는 기능
/// </summary>
/// <returns></returns>
int CPlayer::SelectInput()
{
	while (true)
	{
		std::cout << "행동을 선택 하세요 : ";
		std::cin >> mInput;

		if (mInput <= 0 || mInput > 4)
		{
			std::cout << "범위 내에서 다시 고르세요." << std::endl;
			continue;
		}
		else
			break;
	}

	return mInput;
}

/// <summary>
/// 대미지를 주는 기능
/// </summary>
/// <returns></returns>
int CPlayer::TargetAttack()
{
	

	return 0;
}

int CPlayer::GetAttack()
{
	return mAttack;
}

int CPlayer::GetDefense()
{
	return mDefense;
}

int CPlayer::GetExp()
{
	return mExp;
}

int CPlayer::GetGold()
{
	return mGold;
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

    return true;
}

void CPlayer::Output()
{
	std::cout << "이름 : " << mName << "\t" <<
		"직업 : ";

	switch (mJob)
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

	std::cout << "레벨 : " << mLevel <<
		"\t경험치 : " << mExp << " / " <<
		gLevelUpTable[mLevel - 1] << std::endl;
	std::cout << "공격력 : " << mAttack <<
		"\t방어력 : " << mDefense << std::endl;
	std::cout << "체력 : " << mHP << " / " <<
		mHPMax << "\t마나 : " << mMP <<
		" / " << mMPMax << std::endl;
	std::cout << "Gold : " << mGold << std::endl;
}
