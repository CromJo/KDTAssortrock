#include "SharedPointer.h"
#include "Object.h"

CSharedPointer::CSharedPointer()
{
}


/// <summary>
/// Object �Ǵ� SharedPointer�� ���� ���� ��
/// Object�� ������ ������ �Ͼ ���̱� ������
/// ReferenceCount 1����
/// </summary>
/// <param name="Object"></param>
CSharedPointer::CSharedPointer(CObject* Object)
{
	mObject = Object;

	if (Object)
		mObject->AddReference();
}

CSharedPointer::CSharedPointer(const CSharedPointer& Pointer)
{
	mObject = Pointer.mObject;

	if (mObject)
		mObject->AddReference();
}

CSharedPointer::CSharedPointer(CSharedPointer&& Pointer)
{
	mObject = Pointer.mObject;

	if (mObject)
		mObject->AddReference();
}

/// <summary>
/// ������Ʈ ���� �� ���� ī��Ʈ�� ���ҽ�Ų��.
/// </summary>
CSharedPointer::~CSharedPointer()
{
	if (mObject)
		mObject->Release();
}

void CSharedPointer::operator=(CObject* Object)
{
	if (mObject)
		mObject->Release();

	mObject = Object;

	if (Object)
		mObject->AddReference();
}

void CSharedPointer::operator=(const CSharedPointer& Pointer)
{
	// �̹��ִٸ� ���� ��
	if (mObject)
		mObject->Release();

	// ��ü�۾��� �����Ѵ�.
	mObject = Pointer.mObject;

	if (mObject)
		mObject->AddReference();
}

void CSharedPointer::operator=(CSharedPointer&& Pointer)
{
	// �̹��ִٸ� ���� ��
	if (mObject)
		mObject->Release();

	// ��ü�۾��� �����Ѵ�.
	mObject = Pointer.mObject;

	if (mObject)
		mObject->AddReference();
}

bool CSharedPointer::operator==(CObject* Object) const
{
	return mObject == Object;
}

bool CSharedPointer::operator==(const CSharedPointer& Pointer) const
{
	return mObject == Pointer.mObject;
}

bool CSharedPointer::operator==(CSharedPointer&& Pointer) const
{
	return mObject == Pointer.mObject;
}

bool CSharedPointer::operator!=(CObject* Object) const
{
	return mObject != Object;
}

bool CSharedPointer::operator!=(const CSharedPointer& Pointer) const
{
	return mObject != Pointer.mObject;
}

bool CSharedPointer::operator!=(CSharedPointer&& Pointer) const
{
	return mObject != Pointer.mObject;
}

CObject* CSharedPointer::operator->() const
{
	return mObject;
}

/// <summary>
/// ������ : SharedPointer ��ü�� ������ Object Pointer�� �ִ´�.
/// mObject�� SharedPointer�� �̷��������.
/// </summary>
CSharedPointer::operator class CObject* () const
{
	return mObject;
}

CObject* CSharedPointer::Get() const
{
	return mObject;
}
