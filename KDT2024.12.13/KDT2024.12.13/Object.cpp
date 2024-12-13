#include "Object.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

bool CObject::Init()
{
	std::cout << "오브젝트 초기화 데스요." << std::endl;

	return true;
}

void CObject::Output()
{
	std::cout << "이름 : " << mName << std::endl;
}

void CObject::CharacterExclusive()
{
}
