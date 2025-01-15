#include "SharedPointer.h"
#include "Object.h"

CSharedPointer::CSharedPointer()
{
}

CSharedPointer::CSharedPointer(CObject* Obj)
{
	mObj = Obj;

	// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1����
	if (mObj)
	{
		mObj->AddRef();
	}
}

CSharedPointer::CSharedPointer(const CSharedPointer& Ptr)
{
	mObj = Ptr.mObj;

	// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1����
	if (mObj)
	{
		mObj->AddRef();
	}
}

CSharedPointer::CSharedPointer(CSharedPointer&& Ptr)
{
	mObj = Ptr.mObj;

	if (mObj)
	{
		mObj->AddRef();
	}
}

CSharedPointer::~CSharedPointer()
{
	if (mObj)
	{
		mObj->Release();
	}
}

void CSharedPointer::operator=(CObject* Obj)
{
	mObj = Obj;

	// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1����
	if (mObj)
	{
		mObj->AddRef();
	}
}

void CSharedPointer::operator=(const CSharedPointer& Ptr)
{
	mObj = Ptr.mObj;

	// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1����
	if (mObj)
	{
		mObj->AddRef();
	}
}

void CSharedPointer::operator=(CSharedPointer&& Ptr)
{
	mObj = Ptr.mObj;

	// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1����
	if (mObj)
	{
		mObj->AddRef();
	}
}

bool CSharedPointer::operator==(CObject* Obj) const
{
	return mObj == Obj;
}

bool CSharedPointer::operator==(const CSharedPointer& Ptr) const
{
	return mObj == Ptr.mObj;
}

bool CSharedPointer::operator==(CSharedPointer&& Ptr) const
{
	return mObj == Ptr.mObj;
}

bool CSharedPointer::operator!=(CObject* Obj) const
{
	return mObj != Obj;
}

bool CSharedPointer::operator!=(const CSharedPointer& Ptr) const
{
	return mObj != Ptr;
}

bool CSharedPointer::operator!=(CSharedPointer&& Ptr) const
{
	return mObj != Ptr.mObj;
}

CObject* CSharedPointer::operator->() const
{
	return mObj;
}

CSharedPointer::operator class CObject* () const
{
	return mObj;
}

CObject* CSharedPointer::Get() const
{
	return mObj;
}
