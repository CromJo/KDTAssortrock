#include "SharedPointer.h"
#include "Object.h"

CSharedPointer::CSharedPointer()
{
}


/// <summary>
/// Object 또는 SharedPointer를 전달 받을 때
/// Object가 있으면 참조가 일어난 것이기 때문에
/// ReferenceCount 1증가
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
/// 오브젝트 존재 시 참조 카운트를 감소시킨다.
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
	// 이미있다면 해제 후
	if (mObject)
		mObject->Release();

	// 교체작업을 시작한다.
	mObject = Pointer.mObject;

	if (mObject)
		mObject->AddReference();
}

void CSharedPointer::operator=(CSharedPointer&& Pointer)
{
	// 이미있다면 해제 후
	if (mObject)
		mObject->Release();

	// 교체작업을 시작한다.
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
/// 컨버전 : SharedPointer 객체가 있으면 Object Pointer에 넣는다.
/// mObject는 SharedPointer로 이루어져있음.
/// </summary>
CSharedPointer::operator class CObject* () const
{
	return mObject;
}

CObject* CSharedPointer::Get() const
{
	return mObject;
}
