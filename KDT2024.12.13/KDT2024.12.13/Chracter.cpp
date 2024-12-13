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
    std::cout << "캐릭터 이닛 데스요" << std::endl;

    return true;
}

void CCharacter::Output()
{
    CObject::Output();
    std::cout << "공격력 : " << mAttack << "\t방어력 : " << mDefense << std::endl;
    std::cout << "체력 : " << mHP << "\t\t마나 : " << mMP << std::endl;
    std::cout << "레벨 : " << mLevel << "\t\t경험치 : " << mExp << std::endl;
    std::cout << "소지금 : " << mGold << std::endl;
    

}

void CCharacter::CharacterExclusive()
{
}
