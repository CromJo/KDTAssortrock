#include "Item.h"
#include "Stage.h"
#include "StageManager.h"

CItem::CItem()
{
    mType = EObjectType::Item;
}

CItem::~CItem()
{
}

bool CItem::Init()
{
	return true;
}

void CItem::Update(float DeltaTime)
{
    mMoveY += DeltaTime;

    if (mMoveY >= 1.f)
    {
        mMoveY -= 1.f;

        mPos.Y++;

        int CountY = CStageManager::GetInst()->GetStage()->GetStageCountY() - 1;
        
        if (mPos.Y >= CountY)
        {
            mActive = false;
        }
    }

}

void CItem::Output(char* OutputBuffer)
{
}

ECollisionType CItem::CollisionEnable(CObject* Dest)
{
    switch (Dest->GetType())
    {
    case EObjectType::Player:
        return mCollisionType;
    }

	return ECollisionType::None;
}
