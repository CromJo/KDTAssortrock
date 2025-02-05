#pragma once

#include "../GameInfo.h"

class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	// 2D & 3D 충돌체 데이터 저장용 변수 생성
	std::vector<CSharedPtr<class CColliderBase>>	mColliderList2D;
	std::vector<CSharedPtr<class CColliderBase>>	mColliderList3D;
	// 쿼드트리 데이터 저장용 변수 생성
	class CCollisionQuadTree* mQuadTree;
	// 현재 씬이 어디인지 저장용 변수 생성
	class CScene* mScene = nullptr;

public:
	void AddCollider(class CColliderBase* Collider);

public:
	bool Init();
	void Update(float DeltaTime);
};

