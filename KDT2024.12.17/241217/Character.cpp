#include "Character.h"
#include "Player.h"

CCharacter::CCharacter()
{
	mObjType = EObjectType::Character;
}

CCharacter::CCharacter(const CCharacter& Obj)	:
	CObject(Obj)
{
}

CCharacter::~CCharacter()
{
}

bool CCharacter::Init()
{
	std::cout << "CCharacter Init" << std::endl;

	return true;
}

bool CCharacter::Init(FILE* File)
{
	CObject::Init(File);

	fread(&mAttack, sizeof(int), 1, File);
	fread(&mDefense, sizeof(int), 1, File);
	fread(&mHP, sizeof(int), 1, File);
	fread(&mHPMax, sizeof(int), 1, File);
	fread(&mMP, sizeof(int), 1, File);
	fread(&mMPMax, sizeof(int), 1, File);
	fread(&mLevel, sizeof(int), 1, File);
	fread(&mExp, sizeof(int), 1, File);
	fread(&mGold, sizeof(int), 1, File);

	return true;
}

void CCharacter::Output()
{
	// 부모클래스의 Output함수를 호출한다.
	CObject::Output();

	//std::cout << "이름 : " << mName << std::endl;
	std::cout << "공격력 : " << mAttack <<
		"\t방어력 : " << mDefense << std::endl;
	std::cout << "체력 : " << mHP << " / " <<
		mHPMax << "\t마나 : " <<
		mMP << " / " << mMPMax << std::endl;
	std::cout << "레벨 : " << mLevel <<
		"\t경험치 : " << mExp << std::endl;
	std::cout << "소지금 : " << mGold << std::endl;
}

void CCharacter::CharacterExclusive()
{
}

void CCharacter::VirtualPure()
{
}

void CCharacter::VirtualPure1()
{
}

void CCharacter::VirtualPure2()
{
}

void CCharacter::VirtualPure3()
{
}
