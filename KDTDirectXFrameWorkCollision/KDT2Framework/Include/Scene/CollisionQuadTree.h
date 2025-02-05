#pragma once

#include "../GameInfo.h"

class CCollisionQuadTree
{
	friend class CSceneCollision;

private:
	CCollisionQuadTree();
	~CCollisionQuadTree();

public:
	bool Init();
	void AddCollider(class CColliderBase* Collider);
};

