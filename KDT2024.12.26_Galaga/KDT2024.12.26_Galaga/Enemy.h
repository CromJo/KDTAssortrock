#pragma once
#include "Object.h"

class CEnemy : public CObject
{
public:
	CEnemy();
	virtual ~CEnemy();

protected:
	float mMoveX = 0.f;
	float mMoveY = 0.f;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output();
};

