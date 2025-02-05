#pragma once

#include "../GameInfo.h"

#define	QUADTREE_DIVISION_COUNT	10
#define	QUADTREE_DEPTH_MAX		4

// ����Ʈ�� ��� Ŭ����
class CCollisionQuadTreeNode
{
	// ����Ʈ������ Node�� ����� �� �ֵ��� ����
	friend class CCollisionQuadTree;

private:
	CCollisionQuadTreeNode();
	~CCollisionQuadTreeNode();

private:
	CCollisionQuadTreeNode* mParent = nullptr;
	CCollisionQuadTreeNode* mChild[4] = {};
	FVector2D		mCenter;
	FVector2D		mSize;
	int				mDepth = 0;
	int				mDivisionCount = QUADTREE_DIVISION_COUNT;
	std::vector<CSharedPtr<class CColliderBase>>	mColliderList;

public:
	void AddCollider(class CColliderBase* Collider,
		std::vector<CCollisionQuadTreeNode*>& NodePool);
	void CreateChild(std::vector<CCollisionQuadTreeNode*>& NodePool);

private:
	bool IsInCollider(class CColliderBase* Collider);
};

// ����Ʈ�� Ŭ����
class CCollisionQuadTree
{
	friend class CSceneCollision;

private:
	CCollisionQuadTree();
	~CCollisionQuadTree();

private:
	class CScene* mScene = nullptr;
	CCollisionQuadTreeNode* mRoot = nullptr;
	int		mDivisionCount = QUADTREE_DIVISION_COUNT;
	std::vector<CCollisionQuadTreeNode*>	mNodePool;

public:
	void SetDivisionCount(int Count);

public:
	bool Init();
	void AddCollider(class CColliderBase* Collider);
	void Update(float DeltaTime);
};

