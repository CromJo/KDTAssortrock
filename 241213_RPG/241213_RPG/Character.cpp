#include "Character.h"

CCharacter::CCharacter()
{
	mType = EObjectType::Character;
}

CCharacter::~CCharacter()
{
}

bool CCharacter::Init()
{
	return true;
}

void CCharacter::Output()
{
	// 부모 클래스 아웃풋 출력
	CObject::Output();

	std::cout << "공격력 : "  << mAttack << "\t방어력 : " << mDefense << std::endl;
	std::cout << "체력 : " << mHP << "\t\t마나 : " << mMP << std::endl;
	std::cout << "경험치 : " << mExp << "\t레벨 : " << mLevel << std::endl;
	std::cout << "소지금 : " << mGold << std::endl;
}

void CCharacter::CharacterExclusive()
{
}
