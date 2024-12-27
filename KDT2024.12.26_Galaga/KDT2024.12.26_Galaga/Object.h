#pragma once
#include "GameInfo.h"

// �߻�Ŭ������ ����
class CObject abstract
{
public :
	CObject();
	virtual ~CObject();

protected:
	EObjectType mType;
	COORD mPos = {};
	bool mActive = true;		// ������Ʈ ���ſ� ����

public:
	void SetType(EObjectType Type)
	{
		mType = Type;
	}

	EObjectType GetType()
	{
		return mType;
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
	// �����ʿ䰡 ���ٸ� (�ڽİ�ü������ �ҷ��ð��̶��) \
	// ���������Լ��� ���� ��.
	virtual bool Init() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void Output(char* OutputBuffer) = 0;
	virtual ECollisionType CollisionEnable(CObject* Dest) = 0;
	virtual bool Damage(int Damage);
	virtual int GetDamage();

};

