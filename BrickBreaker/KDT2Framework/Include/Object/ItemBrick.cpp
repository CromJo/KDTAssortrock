#include "ItemBrick.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BallObject.h"
#include "PlayerObject.h"

CItemBrick::CItemBrick()
{
}

CItemBrick::CItemBrick(const CItemBrick& Obj) :
    CBrickObject(Obj)
{
}

CItemBrick::CItemBrick(CItemBrick&& Obj) :
    CBrickObject(Obj)
{
}

CItemBrick::~CItemBrick()
{
}

bool CItemBrick::Init()
{
    CBrickObject::Init();

    SetTarget(mScene->FindObjectFromType<CPlayerObject>());

    mDetectDistance = 400.f;

    return true;
}

void CItemBrick::Update(float DeltaTime)
{
    CBrickObject::Update(DeltaTime);

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


