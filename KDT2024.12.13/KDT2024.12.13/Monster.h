#pragma once
#include "Chracter.h"

class CMonster :public CCharacter
{
public:
	CMonster();
	virtual ~CMonster();

protected:
	EJob mJob;
	virtual void Output();
};

