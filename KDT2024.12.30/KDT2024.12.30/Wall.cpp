#include "Wall.h"
#include "StageManager.h"

CWall::CWall()
{
}

CWall::~CWall()
{
}

bool CWall::Init()
{
    return false;
}

void CWall::Update(float DeltaTime)
{
}

void CWall::Output(char* OutputBuffer)
{
    int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX();
    OutputBuffer[mPos.Y * (CountX + 1) + mPos.X] = '*';
}

ECollisionType CWall::CollisionEnable(CObject* Dest)
{
    return ECollisionType();
}
