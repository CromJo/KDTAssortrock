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
	SetConsume(10);		// 10�� ��밪

	// ���� ������ ���ġ �ʴٸ� ����
	ConsumeCost(Player, GetConsume());



	return true;
}
