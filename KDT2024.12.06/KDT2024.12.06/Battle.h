#pragma once
#include "GameInfo.h"
#include <time.h>		// 랜덤한 골드를 가지기 위해 선언


bool InitBattle();		// 전투 초기화
bool MonsterInit(FMonster* Monster);
void RunBattle();		// 전투 진행