#include "PlayerObject.h"
#include "../Component/StaticMeshComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Input.h"

CPlayerObject::CPlayerObject()
{
}

CPlayerObject::CPlayerObject(const CPlayerObject& Obj) :
	CSceneObject(Obj)
{
}

CPlayerObject::CPlayerObject(CPlayerObject&& Obj) noexcept :
	CSceneObject(Obj)
{
}

CPlayerObject::~CPlayerObject()
{
}

bool CPlayerObject::Init()
{
	mRoot = CreateComponent<CStaticMeshComponent>();
	mSub = CreateComponent<CStaticMeshComponent>();

	//CStaticMeshComponent* Root = CreateComponent<CStaticMeshComponent>();

	mRoot->SetMesh("CenterRect");
	mRoot->SetShader("ColorMeshShader");

	mRoot->SetWorldPosition(0.f, 0.f, 5.5f);

	SetRootComponent(mRoot);

	mScene->GetInput()->AddBindKey("MoveUp", 'W');
	mScene->GetInput()->AddBindKey("MoveDown", 'S');

	mScene->GetInput()->AddBindKey("RotationZ", 'D');
	mScene->GetInput()->AddBindKey("RotationZInverse", 'A');

	mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveUp", EInputType::Hold,
		this, &CPlayerObject::MoveUp);
	mScene->GetInput()->AddBindFunction<CPlayerObject>("MoveDown", EInputType::Hold,
		this, &CPlayerObject::MoveDown);
	
	mScene->GetInput()->AddBindFunction<CPlayerObject>("RotationZ", EInputType::Hold,
		this, &CPlayerObject::RotationZ);
	mScene->GetInput()->AddBindFunction<CPlayerObject>("RotationZInverse", EInputType::Hold,
		this, &CPlayerObject::RotationZInverse);

	return true;
}

void CPlayerObject::Update(float deltaTime)
{
	CSceneObject::Update(deltaTime);
	//FVector3D Rotation = mRotationPivot->GetRelativeRotation();

}

void CPlayerObject::MoveUp(float deltaTime)
{
	FVector3D Position = mRootComponent->GetWorldPosition();
	FVector3D Direct = mRootComponent->GetAxis(EAxis::Y);

	mRootComponent->SetWorldPosition(Position + Direct * deltaTime);
}

void CPlayerObject::MoveDown(float deltaTime)
{
	FVector3D Position = mRootComponent->GetWorldPosition();
	FVector3D Direct = mRootComponent->GetAxis(EAxis::Y);

	mRootComponent->SetWorldPosition(Position + Direct * -deltaTime);
}

void CPlayerObject::RotationZ(float deltaTime)
{
	FVector3D Rotation = mRootComponent->GetWorldRotation();
	mRootComponent->SetWorldRotationZ(Rotation.z + deltaTime * 90.f);
}

void CPlayerObject::RotationZInverse(float deltaTime)
{
	FVector3D Rotation = mRootComponent->GetWorldRotation();
	mRootComponent->SetWorldRotationZ(deltaTime * -90.f);
}
