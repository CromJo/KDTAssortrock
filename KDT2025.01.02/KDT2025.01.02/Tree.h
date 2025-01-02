#pragma once
#include "Array.h"
#include <iostream>

/*
	루트노드		: 최상위 Tree Node를 말한다.
	리프노드		: 최하위 Node를 말한다.
	높이(깊이)	: 최상단부터 1 아래로 내려갈수록 숫자가 1씩 증가한다.
	쿼드 트리		: 4조각씩 잘라서 원하는 부분을 검색할때 1섹션만 검색하는 방식 (최소 75%의 최적화 기능)
	옥 트리		: 3차원 공간을 최적화 할때 쿼드트리의 3D개념으로 검색하는 방식 (최소 87.5% 최적화 기능)

	트리구조는 링크드 리스트 방식으로 구현하는게 편리하다.
	3D게임들이 대체로 트리구조로 되어있음 
	Ex) 캐릭터 뼈대 구조
*/

template <typename Key, typename Value>
class CTreeNode
{
	template<typename Key, typename Value>
	friend class CTree;

public:
	CTreeNode() {}
	~CTreeNode()
	{

	}

private:
	Key mKey;
	Value mData;
	CTreeNode<Key, Value>* mParent = nullptr;
	CArray<CTreeNode<Key, Value>*>	mChildArray;
};

// Key : 노드를 탐색하기 위한 타입
// Value : 실제 노드에 저장하기 위한 타입.
template <typename Key, typename Value>
class CTree
{
public:
	CTree() {}
	~CTree()
	{
		clear();
	}

private:
	CTreeNode<Key, Value>* mRoot = nullptr;
	int mSize = 0;

public:
	void insert(const Key& key, const Value& Data, const Key& ParentKey)
	{
		CTreeNode<Key, Value>* Node = new CTreeNode<Key, Value>;

		Node->mKey = key;
		Node->mData = Data;

		// 루트부터 모든 노드를 탐색하여 부모노드를 찾아온다.
		CTreeNode<Key, Value>* Parent = FindNode(ParentKey, mRoot);

		// Parent 노드가 없을 시 루트를 대체.
		if (!Parent)
		{
			if (mRoot)
			{
				mRoot->mParent = Node;
				Node->mChildArray.push_back(mRoot);
			}

			mRoot = Node;
		}
		else
		{
			Parent->mChildArray.push_back(Node);
			Node->mParent = Parent;
		}

		mSize++;
	}

	void clear()
	{
		clear(mRoot);
		mSize = 0; 
		mRoot = nullptr;
	}

	void TestOutput()
	{
		TestOutput(mRoot);
	}

private:
	void clear(CTreeNode<Key, Value>* Node)
	{
		if (!Node)
			return;

		int ChildSize = Node->mChildArray.size();

		for (int i = 0; i < ChildSize; i++)
		{
			clear(Node->mChildArray[i]);
		}

		delete Node;
	}

	void TestOutput(CTreeNode<Key, Value>* Node)
	{
		if (!Node)
			return;

		std::cout << "Node : " << Node->mKey << std::endl;
		std::cout << "Parent : ";

		if (Node->mParent)
		{
			std::cout << Node->mParent->mKey << std::endl;
		}
		else
		{
			std::cout << "None" << std::endl;
		}

		int ChildSize = Node->mChildArray.size();

		for (int i = 0; i < ChildSize; i++)
		{
			std::cout << "Child" << i << " : " << Node->mChildArray[i]->mKey << std::endl;
		}

		std::cout << std::endl;

		for (int i = 0; i < ChildSize; i++)
		{
			TestOutput(Node->mChildArray[i]);
		}
	}

	CTreeNode<Key, Value>* FindNode(const Key& key, CTreeNode<Key, Value>* Node)
	{
		// Node가 nullptr일 경우 더 이상 탐색할 수 없다.
		if (!Node)
			return nullptr;
		else if (Node->mKey == key)
			return Node;

		int ChildSize = Node->mChildArray.size();

		for (int i = 0; i < ChildSize; i++)
		{
			CTreeNode<Key, Value>* Find = FindNode(key, Node->mChildArray[i]);

			// Find가 존재한다면 (null이 아니라면)
			if (Find)
				return Find;
		}

		return nullptr;
	}
};

