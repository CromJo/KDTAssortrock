#pragma once
#include "Object.h"

class CPlayer : public CObject
{
public:
	CPlayer();
	virtual ~CPlayer();

private:
	char mName[128] = {};	// 플레이어 이름
	int mScore = 0;
	bool isActive = true;	// 기본적으로 활성화 된 상태.

public:
	virtual void Init();
	virtual void Update(float DeltaTime);
	virtual void Output(char* OutputBuffer);
	virtual ECollisionType CollisionEnable(CObject* Destroy);
};

