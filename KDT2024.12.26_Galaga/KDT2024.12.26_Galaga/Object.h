#pragma once
#include "GameInfo.h"

// �߻�Ŭ������ ����
class CObject abstract
{
public :
	CObject();
	virtual ~CObject();

protected:
	char mName[32] = {};
	COORD mPos = {};

public:
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
	virtual void Output() = 0;
};

