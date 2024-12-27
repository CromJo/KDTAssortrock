#pragma once

#include "Object.h"

class CBullet :
	public CObject
{
public:
	CBullet();
	virtual ~CBullet();

protected:
	float	mMoveX = 0.f;
	float	mMoveY = 0.f;
	float	mMoveDirX = 0.f;
	float	mMoveDirY = 0.f;

public:
	void SetMoveDir(float x, float y)
	{
		mMoveDirX = x;
		mMoveDirY = y;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
	virtual ECollisionType CollisionEnable(CObject* Dest);
	virtual bool Damage(int Damage);
	virtual int GetDamage();

};

