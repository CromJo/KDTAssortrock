#pragma once
#include "SkillActive.h"

class CBash : public CSkillActive
{
public:
	CBash();
	CBash(const CBash& Obj);
	~CBash();

protected:
	EItemType::Type mType;
	int mOption = 0;
	int mBuy = 0;
	int mSell = 0;

public:
	virtual bool Init();
	virtual bool Init(FILE* File);
	virtual void Output();
	virtual CBash* Clone();

	virtual void VirtualPure();
	virtual void VirtualPure1();
	virtual void VirtualPure2();
	virtual void VirtualPure3();
};

