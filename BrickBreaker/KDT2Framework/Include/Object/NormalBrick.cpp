#include "NormalBrick.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "BallObject.h"
#include "PlayerObject.h"

CNormalBrick::CNormalBrick()
{
}

CNormalBrick::CNormalBrick(const CNormalBrick& Obj) :
    CBrickObject(Obj)
{
}

CNormalBrick::CNormalBrick(CNormalBrick&& Obj) :
    CBrickObject(Obj)
{
}

CNormalBrick::~CNormalBrick()
{
}

bool CNormalBrick::Init()
{
    CBrickObject::Init();

    SetTarget(mScene->FindObjectFromType<CPlayerObject>());

    return true;
}

void CNormalBrick::Update(float DeltaTime)
{
    CBrickObject::Update(DeltaTime);

    if (mTarget)
    {
        if (mTarget->IsEnable())
        {
            float Angle = GetWorldPosition().GetViewTargetAngle(
                mTarget->GetWorldPosition());

            SetWorldRotationZ(Angle);
        }
    }

}

