#include "Object.h"

CObject::CObject()
{
}

CObject::CObject(const CObject& Obj)
{
	// this�� �ڱ� �ڽ��� �������̴�.
	// ���⿡ �������� �ϸ� �ڱ��ڽ��� ��ü�� �� ���̰�,
	// �ű⿡ ���ڷ� ���� ������Ʈ�� �����Ͽ� ��� ���������,
	// ��������� �����ϰ� �ȴ�.
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
	std::cout << "�̸� : " << mName << std::endl;
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
