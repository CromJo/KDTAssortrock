#include "Item.h"
#include "StageManager.h"

CItem::CItem()
{
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
}

void CItem::Output(char* OutputBuffer)
{
    //int CountX = 
    //OutputBuffer[mPos.Y * (CountX + 1) + mPos.X] = '*';
}

ECollisionType CItem::CollisionEnable(CObject* Dest)
{
    switch (Dest->GetType())
    {
    case EObjectType::Player:
        return ECollisionType::Score;
    }

    return ECollisionType::None;
}

bool CItem::Damage(int Dmg)
{
    return false;
}

int CItem::Score(int Score)
{
    return 0;
}
