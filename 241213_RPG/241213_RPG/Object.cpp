#include "Object.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

bool CObject::Init()
{
	return true;
}

void CObject::Output()
{
	std::cout << "�̸� : " << mName << std::endl;
}
