#pragma once
#include "Object.h"
class CItem : public CObject
{
public:
	CItem();
	virtual ~CItem();

private:
	float mMoveY = 0.f;
	ECollisionType mCollisionType;

public:
	ECollisionType GetCollisionType()
	{
		return mCollisionType;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
	virtual ECollisionType CollisionEnable(CObject* Dest);
};

