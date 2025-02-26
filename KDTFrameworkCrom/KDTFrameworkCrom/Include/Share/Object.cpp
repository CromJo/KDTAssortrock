#include "Object.h"

CObject::CObject()
{
}

CObject::~CObject()
{
}

void CObject::AddReference()
{
	++mReferenceCount;
}

void CObject::Release()
{
	--mReferenceCount;

	if (mReferenceCount == 0)
		delete this;
}

// 오브젝트가 파괴시 실행 
// (파괴후 릴리즈를 동작 하도록 구현되어있음)
void CObject::Destroy()
{
	mActive = false;
}
