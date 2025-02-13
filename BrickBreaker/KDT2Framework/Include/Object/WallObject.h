#pragma once
#include "SceneObject.h"

class CWallObject : public CSceneObject
{
	friend class CScene;

protected:
	CWallObject();
	CWallObject(const CWallObject& Obj);
	CWallObject(CWallObject&& Obj);
	virtual ~CWallObject();

protected:
	CSharedPtr<class CStaticMeshComponent>  mRoot;
	CSharedPtr<class CColliderOBB2D>        mBody;
	CSharedPtr<class CColliderLine2D>       mLine;
	CSharedPtr<class CSceneComponent>       mRotationPivot;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void Damage(int Dmg);

};

