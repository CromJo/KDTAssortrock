#pragma once

template <typename T>
class CSharedPointer
{
public:
	CSharedPointer()
	{
	}

	CSharedPointer(T* Obj)
	{
		mObj = Obj;

		// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1 ������Ų��.
		if (mObj)
			mObj->AddRef();
	}

	CSharedPointer(const CSharedPointer& Ptr)
	{
		mObj = Ptr.mObj;

		// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1 ������Ų��.
		if (mObj)
			mObj->AddRef();
	}

	CSharedPointer(CSharedPointer&& Ptr)
	{
		mObj = Ptr.mObj;

		// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1 ������Ų��.
		if (mObj)
			mObj->AddRef();
	}

	~CSharedPointer()
	{
		// ������Ʈ�� ���� ��� ����ī��Ʈ�� �����Ǿ��� ������ ����ī��Ʈ�� ���ҽ�Ų��.
		if (mObj)
			mObj->Release();
	}


public:
	void operator = (T* Obj)
	{
		if (mObj)
			mObj->Release();

		mObj = Obj;

		// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1 ������Ų��.
		if (mObj)
			mObj->AddRef();
	}

	void operator = (const CSharedPointer& Ptr)
	{
		if (mObj)
			mObj->Release();

		mObj = Ptr.mObj;

		// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1 ������Ų��.
		if (mObj)
			mObj->AddRef();
	}

	void operator = (CSharedPointer&& Ptr)
	{
		if (mObj)
			mObj->Release();

		mObj = Ptr.mObj;

		// ������Ʈ�� ���� ��� ������ �Ͼ�� ���̱� ������ ���� ī��Ʈ�� 1 ������Ų��.
		if (mObj)
			mObj->AddRef();
	}

	bool operator == (T* Obj)	const
	{
		return mObj == Obj;
	}

	bool operator == (const CSharedPointer& Ptr)	const
	{
		return mObj == Ptr.mObj;
	}

	bool operator == (CSharedPointer&& Ptr)	const
	{
		return mObj == Ptr.mObj;
	}

	bool operator != (T* Obj)	const
	{
		return mObj != Obj;
	}

	bool operator != (const CSharedPointer& Ptr)	const
	{
		return mObj != Ptr.mObj;
	}

	bool operator != (CSharedPointer&& Ptr)	const
	{
		return mObj != Ptr.mObj;
	}

	T* operator -> ()	const
	{
		return mObj;
	}

	operator T* ()	const
	{
		return mObj;
	}

	T* Get()	const
	{
		return mObj;
	}

private:
	T* mObj = nullptr;
};

