#pragma once
#include "Object.h"

class CItem : public CObject
{
public:
	CItem();
	virtual ~CItem();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
	virtual ECollisionType CollisionEnable(CObject* Dest);
	virtual bool Damage(int Dmg);
	virtual int Score(int Score);
};

