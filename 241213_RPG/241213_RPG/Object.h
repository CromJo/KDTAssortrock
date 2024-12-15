#pragma once
#include <iostream>

enum class EObjectType : unsigned char
{
	Character,
	Item,
};

class CObject
{
public:
	CObject();
	virtual ~CObject();

protected:
	EObjectType mType;
	char	mName[32] = {};

public:
	void SetName(const char* Name)
	{
		strcpy_s(mName, Name);
	}

public:
	virtual bool Init();
	virtual void Output();
};

