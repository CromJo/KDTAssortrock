#include "Enemy.h"
#include "Stage.h"
#include "StageManager.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "ItemScore.h"

CEnemy::CEnemy()
{
}

CEnemy::~CEnemy()
{
}

bool CEnemy::Init()
{
    return true;
}

void CEnemy::Update(float DeltaTime)
{
    mMoveY += DeltaTime;
    
    if (mMoveY >= 1.f)
    {
        mMoveY -= 1.f;

        mPos.Y++;
    }

    mFireTime += DeltaTime;

    if (mFireTime >= 3.f)
    {
        mFireTime -= 3.f;


        CBullet* Bullet = CObjectManager::GetInst()->CreateObj<CBullet>();

        Bullet->SetPos(mPos.X, mPos.Y + 1);
        Bullet->SetMoveDir(0.f, 1.f);
        Bullet->SetType(EObjectType::EnemyBullet);
    }
}

void CEnemy::Output(char* OutputBuffer)
{
    // 구버전
    //SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mPos);
    //std::cout << "♨";

    // 신버전
    int CountX = CStageManager::GetInst()->GetStage()->GetStageCountX();
    OutputBuffer[mPos.Y * (CountX + 1) + mPos.X] = '!';
}

ECollisionType CEnemy::CollisionEnable(CObject* Dest)
{
    switch (Dest->GetType())
    {
    case EObjectType::Player:
    case EObjectType::PlayerBullet:
        return ECollisionType::Damage;
    }

    return ECollisionType::None;
}

bool CEnemy::Damage(int Damage)
{
    mHP -= Damage;

    if (mHP <= 0)
    {
        int Spawn = rand() % 100;

        if (Spawn < 50)
        {
            // 아이템 종류에 따른 갯수 "End (EItemType 갯수를 의미)"
            Spawn = rand() % EItemType::End;
            CItem* Item = nullptr;

            switch (Spawn)
            {
            case EItemType::Score:
                Item = CObjectManager::GetInst()->CreateObj<CItemScore>();
                break;
            case EItemType::Heal:
                Item = CObjectManager::GetInst()->CreateObj<CItemScore>();
                break;
            case EItemType::Power:
                Item = CObjectManager::GetInst()->CreateObj<CItemScore>();
                break;
            }

            Item->SetPos(mPos.X, mPos.Y);
        }

        return true;
    }

    return false;
}

int CEnemy::GetDamage()
{
    return 1;
}
