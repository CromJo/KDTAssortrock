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
	std::cout << "ÀÌ¸§ : " << mName << std::endl;
}
