#pragma once
#include "Item.h"
class CItemScore : public CItem
{
public:
	CItemScore();
	virtual ~CItemScore();

public:
	virtual bool Init();
	virtual void Output(char* OutputBuffer);
};