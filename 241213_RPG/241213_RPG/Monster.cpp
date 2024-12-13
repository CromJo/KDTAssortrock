#include "Monster.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init(FILE* File)
{
	// 이름을 읽어온다.
	fread(mName, sizeof(char), 32, File);

	// 공격력
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

void CMonster::Output()
{
	std::cout << "이름 : " << mName << std::endl;

	std::cout << "레벨 : " << mLevel <<
		"\t경험치 : " << mExp << std::endl;
	std::cout << "공격력 : " << mAttack <<
		"\t방어력 : " << mDefense << std::endl;
	std::cout << "체력 : " << mHP << " / " <<
		mHPMax << "\t마나 : " << mMP <<
		" / " << mMPMax << std::endl;
	std::cout << "Gold : " << mGold << std::endl;
}

CMonster* CMonster::Clone()
{
	// CMonster 타입의 새로운 객체를 만들고 그 주소
	// 를 반환해준다. 이때 나를 넣어주어 나를
	// 복제한 새로운 객체가 만들어진다.
	return new CMonster(*this);
}
