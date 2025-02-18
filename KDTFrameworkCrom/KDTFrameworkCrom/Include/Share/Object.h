#pragma once

#include "../GameInfo.h"

// Reference Count를 지원하기 위해 추상클래스로 변경.
class CObject abstract
{
protected:
	CObject();
	virtual ~CObject();

protected:
	// 상속받는 Object들은 모든 ReferenceCount들을
	// 가지게 된다.
	int mReferenceCount = 0;

public:
	virtual void AddReference();
	virtual void Release();

};

