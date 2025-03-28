#pragma once
#include "Object.h"

class CEnemy : public CObject
{
public:
	CEnemy();
	virtual ~CEnemy();

private:
	int mHP = 2;
	int mHPMax = mHP;

protected:
	float mMoveX = 0.f;
	float mMoveY = 0.f;
	float mFireTime = 0.f;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
	virtual ECollisionType CollisionEnable(CObject* Dest);
	virtual bool Damage(int Damage);
	virtual int GetDamage();

};

