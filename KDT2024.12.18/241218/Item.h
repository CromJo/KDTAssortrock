#pragma once
#include "Object.h"

/*
	1. �������� �÷��̾ �Դ±�� (Player���� �������� �ν��ؾ���)
	2. �������� ��� (Item���� �ɷ��� �ΰ��ؾ���
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

