#pragma once

#include "../GameInfo.h"

class CSceneCollision
{
	// Scene���� �� ��� �����͸� ����� �� �ֵ��� ����
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	// 2D & 3D �浹ü ������ ������
	std::vector<CSharedPtr<class CColliderBase>>	mColliderList2D;
	std::vector<CSharedPtr<class CColliderBase>>	mColliderList3D;
	// ���漱���� ����Ʈ�� ������ (����� ������ �ҷ��� ������ᳪ �׷�)
	class CCollisionQuadTree* mQuadTree;

public:
	// ���� �浹ü �߰�
	void AddCollider(class CColliderBase* Collider);

public:
	bool Init();
	void Update(float DeltaTime);
};

