#pragma once
#include "Object.h"

class CWall : public CObject
{
public:
	CWall();
	virtual ~CWall();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
	virtual ECollisionType CollisionEnable(CObject* Dest);
};