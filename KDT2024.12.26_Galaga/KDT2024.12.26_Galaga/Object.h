#pragma once
#include "GameInfo.h"

// 추상클래스로 변경
class CObject abstract
{
public :
	CObject();
	virtual ~CObject();

protected:
	char mName[32] = {};
	COORD mPos = {};

public:
	void SetPos(short x, short y)
	{
		mPos.X = x;
		mPos.Y = y;
	}

public:
	// 만들필요가 없다면 (자식객체에서만 불러올것이라면) \
	// 순수가상함수로 만들 것.
	virtual bool Init() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void Output() = 0;
};

