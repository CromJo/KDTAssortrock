#include "Monster.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

bool CMonster::Init(FILE* File)
{
	// 이름 읽어오기
	fread(&mName, sizeof(char), 32, File);

	// 공격력
	fread(&mAttack, sizeof(char), 32, File);
	fread(&mDefense, sizeof(char), 32, File);
	fread(&mHP, sizeof(char), 32, File);
	fread(&mHPMax, sizeof(char), 32, File);
	fread(&mMP, sizeof(char), 32, File);
	fread(&mMPMax, sizeof(char), 32, File);
	fread(&mLevel, sizeof(char), 32, File);
	fread(&mExp, sizeof(char), 32, File);
	fread(&mGold, sizeof(char), 32, File);

	return false;
}

// 몬스터의 정보를 출력합니다.
void CMonster::Output()
{
	std::cout << "이름 : " << mName << std::endl;
	std::cout << "레벨 : " << mLevel << "\t경험치 : " << mExp << std::endl;
	std::cout << "공격력 : " << mAttack << "\t방어력 : " << mDefense << std::endl;
	std::cout << "체력 : " << mHP << "\t마나 : " << mMP << std::endl;
	std::cout << "골드 : " << mGold << std::endl;
}

// 몬스터를 복사해서 새로 생성해줍니다.
CMonster* CMonster::Clone()
{
	// CMonster 타입의 새로운 객체를 만들고 그 주소를 반환해준다.
	// 이때 나를 넣어주어 나를 복제한 새로운 객체가 만들어진다.
	return new CMonster(*this);
}

int CMonster::GetAttack()
{
	return mAttack;
}

int CMonster::GetDefense()
{
	return mDefense;
}
