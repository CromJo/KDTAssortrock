#include "Battle.h"
#include "ObjectManager.h"
#include "Monster.h"

CBattle::CBattle()
{
}

CBattle::~CBattle()
{
}

void CBattle::Run()
{
	CObject* MonsterOrigin = 
		CObjectManager::GetInst()->FindMonster(mType);

	if (!MonsterOrigin)
		return;

	CMonster* Monster = (CMonster*)MonsterOrigin->Clone();
}
