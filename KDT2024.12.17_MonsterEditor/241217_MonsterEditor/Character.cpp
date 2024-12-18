#include "Character.h"

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
	CObject::Init();

	std::cout << "공격력 : ";
	std::cin >> mAttack;

	std::cout << "방어력 : ";
	std::cin >> mDefense;

	std::cout << "체력 : ";
	std::cin >> mHPMax;
	mHP = mHPMax;

	std::cout << "마나 : ";
	std::cin >> mMPMax;
	mMP = mMPMax;

	std::cout << "레벨 : ";
	std::cin >> mLevel;

	std::cout << "경험치 : ";
	std::cin >> mExp;

	std::cout << "골드 : ";
	std::cin >> mGold;

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

void CCharacter::Save(FILE* File)
{
	CObject::Save(File);

	fwrite(&mAttack, sizeof(int), 1, File);
	fwrite(&mDefense, sizeof(int), 1, File);
	fwrite(&mHP, sizeof(int), 1, File);
	fwrite(&mHPMax, sizeof(int), 1, File);
	fwrite(&mMP, sizeof(int), 1, File);
	fwrite(&mMPMax, sizeof(int), 1, File);
	fwrite(&mLevel, sizeof(int), 1, File);
	fwrite(&mExp, sizeof(int), 1, File);
	fwrite(&mGold, sizeof(int), 1, File);
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
	std::cout << "골드 : " << mGold << std::endl;
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
