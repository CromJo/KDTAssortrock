#include "SkillActive.h"

CSkillActive::CSkillActive()
{
}

CSkillActive::CSkillActive(const CSkillActive& Obj) : CSkill(Obj)
{
}

CSkillActive::~CSkillActive()
{
}

bool CSkillActive::Init()
{
    return true;
}

bool CSkillActive::Init(FILE* File)
{
    return true;
}

void CSkillActive::Output()
{
}

CSkillActive* CSkillActive::Clone()
{
    return new CSkillActive(*this);
}

void CSkillActive::VirtualPure()
{
}

void CSkillActive::VirtualPure1()
{
}

void CSkillActive::VirtualPure2()
{
}

void CSkillActive::VirtualPure3()
{
}
