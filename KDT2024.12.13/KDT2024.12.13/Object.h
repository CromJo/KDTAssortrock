#pragma once
#include <iostream>

enum class EObjectType : unsigned char
{
	Character,
	Item
};

class CObject
{
public:
	CObject();
	virtual ~CObject();

protected:
	EObjectType mObjType;
	char mName[32];

public:
	virtual bool Init();
	virtual void Output();
	virtual void CharacterExclusive();
};
