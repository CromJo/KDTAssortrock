#include "SceneComponent.h"

CSceneComponent::CSceneComponent()
{
}

CSceneComponent::CSceneComponent(const CSceneComponent& Com) :
    CComponent(Com)
{
}

CSceneComponent::CSceneComponent(CSceneComponent&& Com) :
    CComponent(Com)
{
}

CSceneComponent::~CSceneComponent()
{
    size_t Size = mChildList.size();
    
    for (size_t i = 0; i < Size; i++)
    {
        mChildList[i]->Destroy();
    }
}

void CSceneComponent::AddChild(CSceneComponent* Child)
{
    // 기본 추가일 경우 자기자신이 곧 부모(최상위 객체)임을 암시함.
    Child->mParent = this;

    mChildList.emplace_back(Child);
}

bool CSceneComponent::Init()
{
    return true;
}

bool CSceneComponent::Init(const char* FileName)
{
    return true;
}

void CSceneComponent::PreUpdate(float deltaTime)
{
    CComponent::PreUpdate(deltaTime);
    // Active가 False면 해제해줄 예정.

    std::vector<CSharedPointer<CSceneComponent>>::iterator iter;
    std::vector<CSharedPointer<CSceneComponent>>::iterator iterEnd = mChildList.end();

    for (iter = mChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, mChildList.back());
            // sharedpointer
            mChildList.pop_back();
            iterEnd = mChildList.end();

            continue;
        }
        else if (!(*iter)->IsEnable())
        {
            iter++;

            continue;
        }

        (*iter)->PreUpdate(deltaTime);
        iter++;
    }
}

void CSceneComponent::Update(float deltaTime)
{
    CComponent::Update(deltaTime);

    std::vector<CSharedPointer<CSceneComponent>>::iterator iter;
    std::vector<CSharedPointer<CSceneComponent>>::iterator iterEnd = mChildList.end();

    for (iter = mChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, mChildList.back());
            // sharedpointer
            mChildList.pop_back();
            iterEnd = mChildList.end();

            continue;
        }
        else if (!(*iter)->IsEnable())
        {
            iter++;

            continue;
        }

        (*iter)->Update(deltaTime);
        iter++;
    }
}

void CSceneComponent::PostUpdate(float deltaTime)
{
    CComponent::PostUpdate(deltaTime);

    std::vector<CSharedPointer<CSceneComponent>>::iterator iter;
    std::vector<CSharedPointer<CSceneComponent>>::iterator iterEnd = mChildList.end();

    for (iter = mChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, mChildList.back());
            // sharedpointer
            mChildList.pop_back();
            iterEnd = mChildList.end();

            continue;
        }
        else if (!(*iter)->IsEnable())
        {
            iter++;

            continue;
        }

        (*iter)->PostUpdate(deltaTime);
        iter++;
    }
}

void CSceneComponent::Collision(float deltaTime)
{
    CComponent::Collision(deltaTime);

    std::vector<CSharedPointer<CSceneComponent>>::iterator iter;
    std::vector<CSharedPointer<CSceneComponent>>::iterator iterEnd = mChildList.end();

    for (iter = mChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, mChildList.back());
            // sharedpointer
            mChildList.pop_back();
            iterEnd = mChildList.end();

            continue;
        }
        else if (!(*iter)->IsEnable())
        {
            iter++;

            continue;
        }

        (*iter)->Collision(deltaTime);
        iter++;
    }
}

void CSceneComponent::PreRender()
{
    CComponent::PreRender();

    mMatrixScale.Scaling(mWorldScale);
    mMatrixRotation.Rotation(mWorldRotation);
    mMatrixTranslate.Translation(mWorldPosition);

    mMatrixWorld = mMatrixScale * mMatrixRotation * mMatrixTranslate;

    std::vector<CSharedPointer<CSceneComponent>>::iterator iter;
    std::vector<CSharedPointer<CSceneComponent>>::iterator iterEnd = mChildList.end();

    for (iter = mChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, mChildList.back());
            // sharedpointer
            mChildList.pop_back();
            iterEnd = mChildList.end();

            continue;
        }
        else if (!(*iter)->IsEnable())
        {
            iter++;

            continue;
        }

        (*iter)->PreRender();
        iter++;
    }
}

void CSceneComponent::Render()
{
    CComponent::Render();

    std::vector<CSharedPointer<CSceneComponent>>::iterator iter;
    std::vector<CSharedPointer<CSceneComponent>>::iterator iterEnd = mChildList.end();

    for (iter = mChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, mChildList.back());
            // sharedpointer
            mChildList.pop_back();
            iterEnd = mChildList.end();

            continue;
        }
        else if (!(*iter)->IsEnable())
        {
            iter++;

            continue;
        }

        (*iter)->Render();
        iter++;
    }
}

void CSceneComponent::PostRender()
{
    CComponent::PostRender();

    std::vector<CSharedPointer<CSceneComponent>>::iterator iter;
    std::vector<CSharedPointer<CSceneComponent>>::iterator iterEnd = mChildList.end();

    for (iter = mChildList.begin(); iter != iterEnd;)
    {
        if (!(*iter)->IsActive())
        {
            // 지워야 할 값과 마지막 값을 바꾼다.
            std::swap(*iter, mChildList.back());
            // sharedpointer
            mChildList.pop_back();
            iterEnd = mChildList.end();

            continue;
        }
        else if (!(*iter)->IsEnable())
        {
            iter++;

            continue;
        }

        (*iter)->PostRender();
        iter++;
    }
}

CSceneComponent* CSceneComponent::Clone()
{
    return new CSceneComponent(*this);
}

void CSceneComponent::SetRelativeScale(const FVector3D& Scale)
{
    mRelativeScale = Scale;

    if (mParent)
    {
        mWorldScale = mRelativeScale * mParent->mWorldScale;
    }
    // 부모가 없으면 RelativeScale 자체가 부모가 된다.
    else
    {
        mWorldScale = mRelativeScale;
    }

    size_t Size = mChildList.size();

    for (size_t i = 0; i < Size; i++)
    {
        mChildList[i]->mWorldPosition = mChildList[i]->
            mRelativePosition * mWorldScale + mWorldPosition;
        mChildList[i]->SetWorldScale(mChildList[i]->mRelativeScale * mWorldScale);
    }
}

void CSceneComponent::SetRelativeScale(float x, float y, float z)
{
    SetRelativeScale(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativeScale(const FVector2D& Scale)
{
    SetRelativeScale(FVector3D(Scale.x, Scale.y, mRelativeScale.z));
}

void CSceneComponent::SetRelativeScale(float x, float y)
{
    SetRelativeScale(FVector3D(x, y, mRelativeScale.z));
}

void CSceneComponent::SetRelativeRotation(const FVector3D& Rotation)
{
    mRelativeRotation = Rotation;

    if (mParent)
    {
        mWorldRotation = mRelativeRotation + mParent->mWorldRotation;
    }
    else
    {
        mWorldRotation = mRelativeRotation;
    }

    size_t Size = mChildList.size();

    for (size_t i = 0; i < Size; i++)
    {
        mChildList[i]->mWorldPosition = mChildList[i]->
            mRelativePosition.GetRotation(mWorldRotation) + mWorldPosition;

        mChildList[i]->SetWorldRotation(mChildList[i]->mRelativeRotation + mWorldRotation);
    }
}

void CSceneComponent::SetRelativeRotation(float x, float y, float z)
{
    SetRelativeRotation(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativeRotation(const FVector2D& Rotation)
{
    SetRelativeRotation(FVector3D(Rotation.x, Rotation.y, mRelativeRotation.z));
}

void CSceneComponent::SetRelativeRotation(float x, float y)
{
    SetRelativeRotation(FVector3D(x, y, mRelativeRotation.z));
}

void CSceneComponent::SetRelativeRotationX(float x)
{
    SetRelativeRotation(FVector3D(x, mRelativeRotation.y, mRelativeRotation.z));
}

void CSceneComponent::SetRelativeRotationY(float y)
{
    SetRelativeRotation(FVector3D(mRelativeRotation.x, y, mRelativeRotation.z));
}

void CSceneComponent::SetRelativeRotationZ(float z)
{
    SetRelativeRotation(FVector3D(mRelativeRotation.x, mRelativeRotation.y, z));
}

void CSceneComponent::SetRelativeRotationAxis(float angle, const FVector3D& Axis)
{
}

void CSceneComponent::SetRelativePosition(const FVector3D& Position)
{
    mRelativePosition = Position;

    if (mParent)
    {
        mWorldPosition = mRelativePosition + mParent->mWorldPosition;
    }
    else
    {
        mWorldPosition = mRelativePosition;
    }

    size_t Size = mChildList.size();

    for (size_t i = 0; i < Size; i++)
    {
        mChildList[i]->SetWorldPosition(mChildList[i]->mRelativePosition + mWorldPosition);
    }
}

void CSceneComponent::SetRelativePosition(float x, float y, float z)
{
    SetRelativePosition(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativePosition(const FVector2D& Position)
{
    SetRelativePosition(FVector3D(Position.x, Position.y, mRelativePosition.z));
}

void CSceneComponent::SetRelativePosition(float x, float y)
{
    SetRelativePosition(FVector3D(x, y, mRelativePosition.z));
}

void CSceneComponent::SetWorldScale(const FVector3D& Scale)
{
    mWorldScale = Scale;

    if (mParent)
    {
        mRelativeScale = mWorldScale / mParent->mWorldScale;
    }
    else
    {
        mRelativeScale = mWorldScale;
    }

    size_t Size = mChildList.size();

    for (size_t i = 0; i < Size; i++)
    {
        mChildList[i]->SetWorldScale(mChildList[i]->mRelativeScale * mWorldScale);
        mChildList[i]->SetWorldPosition(mChildList[i]->mRelativePosition * mWorldScale + mWorldPosition);
    }
}

void CSceneComponent::SetWorldScale(float x, float y, float z)
{
    SetRelativeScale(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldScale(const FVector2D& Scale)
{
    SetRelativeScale(FVector3D(Scale.x, Scale.y, mWorldScale.z));
}

void CSceneComponent::SetWorldScale(float x, float y)
{
    SetRelativeScale(FVector3D(x, y, mWorldScale.z));
}

void CSceneComponent::SetWorldRotation(const FVector3D& Rotation)
{
    mRelativeRotation = Rotation;

    if (mParent)
    {
        mRelativeRotation = mWorldRotation / mParent->mWorldRotation;
    }
    else
    {
        mRelativeRotation = mWorldRotation;
    }

    FVector3D Axis[EAxis::End] =
    {
        FVector3D(1.f, 0.f, 0.f),
        FVector3D(0.f, 1.f, 0.f),
        FVector3D(0.f, 0.f, 1.f),
    };

    FMatrix matrixRotation;
    matrixRotation.Rotation(mWorldRotation);

    // 회전된 축을 구한다.
    mAxis[EAxis::X] = Axis[EAxis::X].TransformNormal(matrixRotation);
    mAxis[EAxis::Y] = Axis[EAxis::Y].TransformNormal(matrixRotation);
    mAxis[EAxis::Z] = Axis[EAxis::Z].TransformNormal(matrixRotation);

    size_t Size = mChildList.size();

    for (size_t i = 0; i < Size; i++)
    {
        mChildList[i]->SetWorldRotation(mChildList[i]->mRelativeRotation * mWorldRotation);
        
        FVector3D ParentRotation = GetWorldRotation();

        FMatrix matrixRotation;
        matrixRotation.Rotation(ParentRotation);

        memcpy(&matrixRotation._41, &mWorldPosition, sizeof(FVector3D));

        //mChildList[i]->mWorldPosition = mChildList[i]->mRelativePosition.TransformCoord

        mChildList[i]->SetWorldPosition(mChildList[i]->mRelativePosition.GetRotation(mWorldRotation) + mWorldPosition);
    }
}

void CSceneComponent::SetWorldRotation(float x, float y, float z)
{
    SetWorldRotation(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldRotation(const FVector2D& Rotation)
{
    SetWorldRotation(FVector3D(Rotation.x, Rotation.y, mRelativeRotation.z));
}

void CSceneComponent::SetWorldRotation(float x, float y)
{
    SetWorldRotation(FVector3D(x, y, mRelativeRotation.z));
}

void CSceneComponent::SetWorldRotationX(float x)
{
    SetWorldRotation(FVector3D(x, mRelativeRotation.y, mRelativeRotation.z));
}

void CSceneComponent::SetWorldRotationY(float y)
{
    SetWorldRotation(FVector3D(mRelativeRotation.x, y, mRelativeRotation.z));
}

void CSceneComponent::SetWorldRotationZ(float z)
{
    SetWorldRotation(FVector3D(mRelativeRotation.x, mRelativeRotation.y, z));
}

void CSceneComponent::SetWorldRotationAxis(float Angle, const FVector3D& Axis)
{
}

void CSceneComponent::SetWorldPosition(const FVector3D& Position)
{
    mWorldPosition = Position;

    if (mParent)
    {
        FVector3D ParentRotation = mParent->GetWorldRotation();
        
        FMatrix matrixRotation;
        matrixRotation.Rotation(ParentRotation);

        // 행렬의 41, 42, 43에 부모의 위치를 넣어 부모위치를 중심으로 회전하는
        // 행렬을 만든다.
        memcpy(&matrixRotation._41, &mParent->mWorldPosition, sizeof(FVector3D));

        mWorldPosition = mRelativePosition.TransformCoord(matrixRotation);

        FVector3D RelativePosition = mWorldPosition - mParent->mWorldPosition;
        mRelativePosition = RelativePosition.GetRotation(mParent->mWorldRotation * -1.f);
    }
    else
    {
        mRelativePosition = mWorldPosition;
    }

    size_t Size = mChildList.size();

    for (size_t i = 0; i < Size; i++)
    {
        mChildList[i]->SetWorldPosition(mChildList[i]->mRelativePosition + mWorldPosition);
    }
}

void CSceneComponent::SetWorldPosition(float x, float y, float z)
{
    SetWorldPosition(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldPosition(const FVector2D& Position)
{
    SetWorldPosition(FVector3D(Position.x, Position.y, mRelativePosition.z));
}

void CSceneComponent::SetWorldPosition(float x, float y)
{
    SetWorldPosition(FVector3D(x, y, mRelativePosition.z));
}
