#pragma once
#include "SceneObject.h"

class CPenetratingBullet : public CSceneObject
{
private:
	// CScene에서 CPenetratingBullet을 사용할 수 있도록 설정
	friend class CScene;

private:
	CPenetratingBullet();
	CPenetratingBullet(const CPenetratingBullet& Obj);
	CPenetratingBullet(CPenetratingBullet&& Obj);
	~CPenetratingBullet();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

};

