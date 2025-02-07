#pragma once
#include "SceneObject.h"

class CPenetratingBullet : public CSceneObject
{
private:
	// CScene���� CPenetratingBullet�� ����� �� �ֵ��� ����
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

