#include "Object.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

bool CObject::Init()
{
	std::cout << "������Ʈ �ʱ�ȭ ������." << std::endl;

	return true;
}

void CObject::Output()
{
	std::cout << "�̸� : " << mName << std::endl;
}

void CObject::CharacterExclusive()
{
}
