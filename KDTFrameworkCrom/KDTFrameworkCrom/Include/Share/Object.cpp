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
