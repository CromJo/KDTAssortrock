#pragma once
#include "SceneObject.h"
class CBulletObject : public CSceneObject
{
	friend class CScene;

public:
	CBulletObject();
	CBulletObject(const CBulletObject& Obj);
	CBulletObject(CBulletObject&& Obj);
	virtual ~CBulletObject();

public:
	virtual bool Init();
	void Update(float deltaTime);

};

