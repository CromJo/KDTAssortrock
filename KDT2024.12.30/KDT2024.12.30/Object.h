#pragma once

#include "GameInfo.h"

class CObject abstract
{
public:
	CObject();
	virtual ~CObject();

protected:
	EObjectType	mType;
	COORD	mPos = {};
	bool	mActive = true;

public:
	EObjectType GetType()
	{
		return mType;
	}

	void SetType(EObjectType Type)
	{
		mType = Type;
	}

	bool GetActive()
	{
		return mActive;
	}

	const COORD& GetPos()
	{
		return mPos;
	}

	void SetPos(short x, short y)
	{
		mPos.X = x;
		mPos.Y = y;
	}

public:
	virtual bool Init() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void Output(char* OutputBuffer) = 0;
	virtual ECollisionType CollisionEnable(CObject* Dest) = 0;
	virtual int Score(int Score) = 0;
	virtual bool Damage(int Dmg);
	virtual int GetDamage();
};

