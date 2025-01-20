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

	// 대체로 해제할때는 포인터로 해제했었던것 같은데 왜 이건 this로 할까?
	if (mRefCount == 0)
		delete this;
}

void CObject::Destroy()
{
	mActive = false;
}
