#include "Object.h"

CObject::CObject()
{
}

CObject::CObject(const CObject& Obj)
{
	// this는 자기 자신의 포인터이다.
	// 여기에 역참조를 하면 자기자신의 객체가 될 것이고,
	// 거기에 인자로 들어온 오브젝트를 대입하여 모든 멤버변수를,
	// 얕은복사로 복사하게 된다.
	*this = Obj;
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
	std::cout << "이름 : " << mName << std::endl;
}

void CObject::OverrideTest()
{
}

void CObject::VirtualPure()
{
}

void CObject::VirtualPure1()
{
}

void CObject::VirtualPure2()
{
}
