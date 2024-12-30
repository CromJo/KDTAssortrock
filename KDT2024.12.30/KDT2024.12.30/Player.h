#pragma once
#include "Object.h"

class CPlayer :
	public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	int		mHP = 1;
	int		mHPMax = 1;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
	virtual ECollisionType CollisionEnable(CObject* Dest);
	virtual bool Damage(int Dmg);
	virtual int Score(int Score);
};