#pragma once
#include "Object.h"

class CItem : public CObject
{
public:
	CItem();
	CItem(const CItem& Obj);
	~CItem();

protected:
	EItemType::Type mType;
	int mOption = 0;
	int mBuy = 0;
	int mSell = 0;

public:
	virtual bool Init();
	virtual bool Init(FILE* File);
	virtual void Output();
	virtual CItem* Clone();

	virtual void VirtualPure();
	virtual void VirtualPure1();
	virtual void VirtualPure2();
	virtual void VirtualPure3();
};