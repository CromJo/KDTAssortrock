#include "Character.h"

CCharacter::CCharacter()
{
	mType = EObjectType::Character;
}

CCharacter::CCharacter(const CCharacter& Obj)
{
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
	// �θ� Ŭ���� �ƿ�ǲ ���
	CObject::Output();

	std::cout << "���ݷ� : "  << mAttack << "\t���� : " << mDefense << std::endl;
	std::cout << "ü�� : " << mHP << "\t\t���� : " << mMP << std::endl;
	std::cout << "����ġ : " << mExp << "\t���� : " << mLevel << std::endl;
	std::cout << "������ : " << mGold << std::endl;
}

void CCharacter::CharacterExclusive()
{
}
