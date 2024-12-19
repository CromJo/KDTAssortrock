#pragma once
#include "Object.h"

/*
	1. 아이템을 플레이어가 먹는기능 (Player에서 아이템을 인식해야함)
	2. 아이템의 기능 (Item에서 능력을 부과해야함
*/

class CItem : public CObject
{
public:
	CItem();
	virtual ~CItem();

public:
	virtual bool Init();
	virtual void Update();
	virtual void Output(char* OutBuffer, int CountX);
};

