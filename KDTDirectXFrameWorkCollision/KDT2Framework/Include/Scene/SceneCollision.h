#pragma once

#include "../GameInfo.h"

class CSceneCollision
{
	// Scene에서 이 헤더 데이터를 사용할 수 있도록 만듦
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	// 2D & 3D 충돌체 보관용 데이터
	std::vector<CSharedPtr<class CColliderBase>>	mColliderList2D;
	std::vector<CSharedPtr<class CColliderBase>>	mColliderList3D;
	// 전방선언한 쿼드트리 데이터 (계산기능 빠르게 할려고 만들어줬나 그럼)
	class CCollisionQuadTree* mQuadTree;

public:
	// 씬에 충돌체 추가
	void AddCollider(class CColliderBase* Collider);

public:
	bool Init();
	void Update(float DeltaTime);
};

