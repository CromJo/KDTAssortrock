#pragma once
#include "Object.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	char mName[128] = {};	// �÷��̾� �̸�
	int mScore = 0;
	bool isActive = true;	// �⺻������ Ȱ��ȭ �� ����.

public:
	virtual void Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
	virtual ECollisionType CollisionEnable(CObject* Destroy);
};

