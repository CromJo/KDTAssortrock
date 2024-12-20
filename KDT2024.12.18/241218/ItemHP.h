#pragma once
#include "Item.h"

class CItemHP : public CItem
{

public:
	CItemHP();
	virtual ~CItemHP();

public:
	virtual bool Init();
	virtual void Update();
	virtual void Output(char* OutBuffer, int CountX);

};

