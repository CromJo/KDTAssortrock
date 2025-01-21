#pragma once
#include "SceneObject.h"

class CPlayerObject : public CSceneObject
{
	friend class CScene;

public:
	CPlayerObject();
	CPlayerObject(const CPlayerObject& Obj);
	CPlayerObject(CPlayerObject&& Obj) noexcept;
	virtual ~CPlayerObject();

protected:
	CSharedPointer<class CStaticMeshComponent> mRoot;
	CSharedPointer<class CSceneComponent> m;
	CSharedPointer<class CStaticMeshComponent> mSub;

public:
	virtual bool Init();
	void Update(float deltaTime);

private:
	void MoveUp(float deltaTime);
	void MoveDown(float deltaTime);

	void RotationZ(float deltaTime);
	void RotationZInverse(float deltaTime);
};

