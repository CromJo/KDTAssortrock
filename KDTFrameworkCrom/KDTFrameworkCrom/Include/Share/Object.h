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

public:
	virtual void AddReference();
	virtual void Release();

};

