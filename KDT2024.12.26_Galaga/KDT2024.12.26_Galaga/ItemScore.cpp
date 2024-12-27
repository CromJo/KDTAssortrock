#include "ItemScore.h"
#include "StageManager.h"

CItemScore::CItemScore()
{
    mCollisionType = ECollisionType::Score;
}

CItemScore::~CItemScore()
{
}

bool CItemScore::Init()
{
	return false;
}

void CItemScore::Output(char* OutputBuffer)
{
    int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX() - 1;

    if (mPos.Y >= CountX)
    {
        mActive = false;
    }
}
