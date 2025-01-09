#pragma once
#include "GameInfo.h"

class CObject abstract
{
public:
	CObject();
	~CObject();

private:
	EBlockType mType = EBlockType::None;
	COORD mBoard = {};
	bool mActive = true;		// ��� ���� �� ����

public:
	// ��� �ʿ���� ������ �������� �߰����� �ʴ���.
	void SetType(EObjectType Type)
	{
		mType = (EBlockType)Type;
	}

	void SetBlockType(EBlockType Type)
	{
		mType = Type;
	}

	EBlockType GetBlockType()
	{
		return mType;
	}

	void SetBoardSize(short X, short Y)
	{
		mBoard.X = X;
		mBoard.Y = Y;
	}

public:
	virtual void Init() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void Output(char* OutputBuffer) = 0;
	virtual ECollisionType CollisionEnable(CObject* Destroy) = 0;
	virtual bool GameOver(bool isTrigger);
};

