#pragma once
#include "SceneObject.h"

class CPlayerObject : public CSceneObject
{
	friend class CScene;

public:
	CPlayerObject();
	CPlayerObject(const CPlayerObject& Obj);
	CPlayerObject(CPlayerObject&& Obj);
	virtual ~CPlayerObject();

public:
	virtual bool Init();
};

