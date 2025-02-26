#pragma once

#include "../GameInfo.h"

// Reference Count�� �����ϱ� ���� �߻�Ŭ������ ����.
class CObject abstract
{
protected:
	CObject();
	virtual ~CObject();

protected:
	// ��ӹ޴� Object���� ��� ReferenceCount����
	// ������ �ȴ�.
	int mReferenceCount = 0;
	// Active = false �� ��ü ��Ȱ��ȭ
	bool mActive = true;
	// Enable = false �� Release����
	bool mEnable = true;

public:
	bool IsActive() const
	{
		return mActive;
	}

	bool IsEnable() const
	{
		return mEnable;
	}

public:
	virtual void AddReference();
	virtual void Release();
	void Destroy();
	void SetEnable(bool Enable)
	{
		mEnable = Enable;
	}

};

