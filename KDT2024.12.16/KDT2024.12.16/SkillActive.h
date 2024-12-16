#pragma once
#include "Skill.h"

class CSkillActive : public CSkill
{
public:
	CSkillActive();
	CSkillActive(const CSkillActive& Obj);
	~CSkillActive();

protected:
	int mMP;
	int mAttack = 0;

public:
	int GetMP()
	{
		return mMP;
	}

	int GetAttack()
	{
		return mAttack;
	}

public:
	virtual bool Init();
	virtual bool Init(FILE* File);
	virtual void Output();
	virtual CSkillActive* Clone();

	virtual void VirtualPure();
	virtual void VirtualPure1();
	virtual void VirtualPure2();
	virtual void VirtualPure3();
};

