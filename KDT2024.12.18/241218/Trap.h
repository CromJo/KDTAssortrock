#pragma once
#include "Object.h"

class CTrap : public CObject
{
public:
	CTrap();
	virtual ~CTrap();

public:
	virtual bool Init();
	virtual void Update();
	virtual void Output(char* OutBuffer, int CountX);

};

