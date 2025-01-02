#pragma once
#include "Array.h"
#include <iostream>

/*
	��Ʈ���		: �ֻ��� Tree Node�� ���Ѵ�.
	�������		: ������ Node�� ���Ѵ�.
	����(����)	: �ֻ�ܺ��� 1 �Ʒ��� ���������� ���ڰ� 1�� �����Ѵ�.
	���� Ʈ��		: 4������ �߶� ���ϴ� �κ��� �˻��Ҷ� 1���Ǹ� �˻��ϴ� ��� (�ּ� 75%�� ����ȭ ���)
	�� Ʈ��		: 3���� ������ ����ȭ �Ҷ� ����Ʈ���� 3D�������� �˻��ϴ� ��� (�ּ� 87.5% ����ȭ ���)

	Ʈ�������� ��ũ�� ����Ʈ ������� �����ϴ°� ���ϴ�.
	3D���ӵ��� ��ü�� Ʈ�������� �Ǿ����� 
	Ex) ĳ���� ���� ����
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

// Key : ��带 Ž���ϱ� ���� Ÿ��
// Value : ���� ��忡 �����ϱ� ���� Ÿ��.
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

		// ��Ʈ���� ��� ��带 Ž���Ͽ� �θ��带 ã�ƿ´�.
		CTreeNode<Key, Value>* Parent = FindNode(ParentKey, mRoot);

		// Parent ��尡 ���� �� ��Ʈ�� ��ü.
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
		// Node�� nullptr�� ��� �� �̻� Ž���� �� ����.
		if (!Node)
			return nullptr;
		else if (Node->mKey == key)
			return Node;

		int ChildSize = Node->mChildArray.size();

		for (int i = 0; i < ChildSize; i++)
		{
			CTreeNode<Key, Value>* Find = FindNode(key, Node->mChildArray[i]);

			// Find�� �����Ѵٸ� (null�� �ƴ϶��)
			if (Find)
				return Find;
		}

		return nullptr;
	}
};

