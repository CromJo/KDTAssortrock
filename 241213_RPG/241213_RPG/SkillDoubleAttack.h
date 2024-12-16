#pragma once
#include "Skill.h"

class SkillDoubleAttack : public CSkill
{
public:
	virtual bool Init();
	virtual void Run();

public:
	bool DoubleAttack(CPlayer* Player);
	DECLARE_SINGLE(SkillDoubleAttack);
};

