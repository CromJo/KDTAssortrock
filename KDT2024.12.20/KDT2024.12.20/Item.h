#pragma once
#include "Object.h"
class CItem :
	public CObject
{
public:
	CItem();
	virtual ~CItem();

public:
	virtual bool Init();
	virtual void Update();
	virtual void Output(char* OutBuffer, int CountX);
};

