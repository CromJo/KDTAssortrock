#include "Object.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

void CObject::AddRef()
{
	mRefCount++;
}

void CObject::Release()
{
	mRefCount--;

	// ��ü�� �����Ҷ��� �����ͷ� �����߾����� ������ �� �̰� this�� �ұ�?
	if (mRefCount == 0)
		delete this;
}
