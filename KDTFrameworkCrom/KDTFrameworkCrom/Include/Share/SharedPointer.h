#pragma once

template <typename T>
class CSharedPointer
{
public:
	CSharedPointer()
	{

	}
	 
	CSharedPointer(T* Object)
	{
		mObject = Object;
		 
		if (mObject)
			mObject->AddReference();
	}

	CSharedPointer(const CSharedPointer& Pointer)
	{
		mObject = Pointer.mObject;

		if (mObject)
			mObject->AddReference();
	}

	CSharedPointer(CSharedPointer&& Pointer)
	{
		mObject = Pointer.mObject;

		if (mObject)
			mObject->AddReference();
	}

	~CSharedPointer()
	{
		if (mObject)
			mObject->Release();
	}

public:
	void operator = (T* Object)
	{
		if (mObject)
			mObject->Release();

		mObject = Object;

		if (mObject)
			mObject->AddReference();
	}
	void operator = (const CSharedPointer& Pointer)
	{
		// �̹��ִٸ� ���� ��
		if (mObject)
			mObject->Release();

		// ��ü�۾��� �����Ѵ�.
		mObject = Pointer.mObject;

		if (mObject)
			mObject->AddReference();
	}

	void operator = (CSharedPointer&& Pointer)
	{
		// �̹��ִٸ� ���� ��
		if (mObject)
			mObject->Release();

		// ��ü�۾��� �����Ѵ�.
		mObject = Pointer.mObject;

		if (mObject)
			mObject->AddReference();
	}

	bool operator == (T* Object) const
	{
		return mObject == Object;
	}

	bool operator == (const CSharedPointer& Pointer) const
	{
		return mObject == Pointer.mObject;
	}

	bool operator == (CSharedPointer&& Pointer) const
	{
		return mObject == Pointer.mObject;
	}

	bool operator != (T* Object) const
	{
		return mObject != Object;
	}

	bool operator != (const CSharedPointer& Pointer) const
	{
		return mObject != Pointer.mObject;
	}

	bool operator != (CSharedPointer&& Pointer) const
	{
		return mObject != Pointer.mObject;
	}

	T* operator -> () const
	{
		return mObject;
	}

	operator T* () const
	{
		return mObject;
	}

	T* Get() const
	{
		return mObject;
	}

private:
	T* mObject = nullptr;
};
