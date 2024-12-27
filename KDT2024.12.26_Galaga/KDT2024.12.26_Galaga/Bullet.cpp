#include "Bullet.h"
#include "StageManager.h"
#include "Stage.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
}

bool CBullet::Init()
{
    return true;
}

void CBullet::Update(float DeltaTime)
{
    mMoveX += mMoveDirX * DeltaTime * 6.f;
    mMoveY += mMoveDirY * DeltaTime * 6.f;

    int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX() - 1;
    int CountY = CStageManager::GetInst()->GetStage()->GetStageCountY() - 1;

    // mMoveX�� �������� �� ��� -1���� �۰ų� ����.
    // mMoveX�� ���������� �� ��� 1���� ũ�ų� ����.
    // mMoveY�� �Ʒ��� �� ��� 1���� ũ�ų� ����.
    // mMoveY�� ���� �� ��� 1���� �۰ų� ����.
    // abs�Լ� : ���밪�� �����ִ� �Լ��̴�.
    if (abs(mMoveX) >= 1.f)
    {
        mPos.X += (int)mMoveX;
        mMoveX -= (int)mMoveX;

        if (mPos.X < 1 ||
            mPos.X >= CountX)
        {
            mActive = false;
        }
    }

    if (abs(mMoveY) >= 1.f)
    {
        mPos.Y += (int)mMoveY;
        mMoveY -= (int)mMoveY;
        
        if (mPos.Y >= CountY)
        {
            mActive = false;
        }
    }
}

void CBullet::Output(char* OutputBuffer)
{
    int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX();
    OutputBuffer[mPos.Y * (CountX + 1) + mPos.X] = '*';
}

ECollisionType CBullet::CollisionEnable(CObject* Dest)
{
    if (mType == EObjectType::PlayerBullet &&
        Dest->GetType() == EObjectType::Enemy)
        return ECollisionType::Damage;
    else if (mType == EObjectType::EnemyBullet &&
        Dest->GetType() == EObjectType::Player)
        return ECollisionType::Damage;

    return ECollisionType::None;
}

bool CBullet::Damage(int Damage)
{
    return true;
}

int CBullet::GetDamage()
{
    return 1;
}
