#include "Chracter.h"

CCharacter::CCharacter()
{
    mObjType = EObjectType::Character;
}

CCharacter::~CCharacter()
{
}

bool CCharacter::Init()
{
    std::cout << "ĳ���� �̴� ������" << std::endl;

    return true;
}

void CCharacter::Output()
{
    CObject::Output();
    std::cout << "���ݷ� : " << mAttack << "\t���� : " << mDefense << std::endl;
    std::cout << "ü�� : " << mHP << "\t\t���� : " << mMP << std::endl;
    std::cout << "���� : " << mLevel << "\t\t����ġ : " << mExp << std::endl;
    std::cout << "������ : " << mGold << std::endl;
    

}

void CCharacter::CharacterExclusive()
{
}
