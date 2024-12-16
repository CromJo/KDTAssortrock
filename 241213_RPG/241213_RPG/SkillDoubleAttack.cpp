#include "SkillDoubleAttack.h"

bool SkillDoubleAttack::Init()
{
	return true;
}

void SkillDoubleAttack::Run()
{
}

bool SkillDoubleAttack::DoubleAttack(CPlayer* Player)
{
	SetConsume(10);		// 10의 비용값

	// 만약 마나가 충분치 않다면 종료
	ConsumeCost(Player, GetConsume());



	return true;
}
