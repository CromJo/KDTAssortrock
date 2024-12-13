#pragma once
#include "Chracter.h"

enum class EJob : unsigned char
{
	None,
	Knight,
	Archer,
	Magicion
};

class CPlayer : public CCharacter
{
public:
	CPlayer();
	virtual ~CPlayer();

protected:
	EJob mJob;
	virtual void Output();

public:
	void SetName(const char* Name);
};

