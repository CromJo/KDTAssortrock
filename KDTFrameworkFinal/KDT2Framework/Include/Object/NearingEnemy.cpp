﻿#include "NearingEnemy.h"
#include "../Component/StaticMeshComponent.h"
#include "../Component/SpriteComponent.h"
#include "../Scene/Scene.h"
#include "BulletObject.h"
#include "PlayerObject.h"

CNearingEnemy::CNearingEnemy()
{
}

CNearingEnemy::CNearingEnemy(const CNearingEnemy& Obj) :
    CEnemyObject(Obj)
{
}

CNearingEnemy::CNearingEnemy(CNearingEnemy&& Obj) :
    CEnemyObject(Obj)
{
}

CNearingEnemy::~CNearingEnemy()
{
}

bool CNearingEnemy::Init()
{
    CEnemyObject::Init();

    mRoot->SetTexture("Enemy1Tex", TEXT("Texture/block_wall.png"));
    mRoot->SetPivot(0.5f, 0.5f);

    //SetTarget(mScene->FindObjectFromType<CPlayerObject>());

    mDetectDistance = 400.f;

    return true;
}

void CNearingEnemy::Update(float DeltaTime)
{
    CEnemyObject::Update(DeltaTime);

    if (mTarget)
    {
        // 타겟과의 거리를 구한다.
        float   Distance = GetWorldPosition().Distance(mTarget->GetWorldPosition());

        if (Distance <= mDetectDistance)
        {
            float RotAngle = GetWorldPosition().GetViewTargetAngle(
                mTarget->GetWorldPosition());

            SetWorldRotationZ(RotAngle);

            // 타겟과의 각도를 계산한다.
            // 타겟을 바라보는 방향벡터를 구한다.
            FVector3D   View = mTarget->GetWorldPosition() -
                GetWorldPosition();
            View.Normalize();

            float Angle = GetAxis(EAxis::Y).GetAngle(View);

            if (Angle <= mDetectAngle)
            {                
                mAttackTime -= DeltaTime;

                if (mAttackTime <= 0.f)
                {
                    mAttackTime += 0.5f;

                    CPlayerObject* Player =
                        dynamic_cast<CPlayerObject*>(mTarget.Get());

                    if (Player)
                    {
                        Player->Damage(1);
                    }
                }
            }

            else
            {
                mAttackTime = 0.5f;
            }
        }

        else
        {
            mAttackTime = 0.5f;
        }
    }
}


