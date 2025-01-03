#pragma once

/*
	Ʈ���� ������ ���߱� ���� ��带 �������� ��/�������� ���� ���̸� ���Ͽ�,
	���� ���̰� 2�̻� �߻��� ��� Ʈ���� ������ ������ ������ �Ǵ�.
	
	������ ������ ������ �� 4������ �ִ�.
	������ ������ ��� Ʈ���� ȸ���� �̿��Ͽ� ������ �����.
	ȸ���� ����ȸ��, ������ ȸ�� 2������ �ִ�.

	������ȸ�� : ������ �Ǵ� ����� ���� �ڽĳ�带 ���س���� ��ġ�� �ø���,
				���� �ڽĳ���� ������ �ڽĳ�带 ���س���� ���� �ڽĳ��� �ٿ��ش�.
				���� �ڽĳ���� �θ� ���س���� �θ�� �����Ѵ�.

	���� ȸ�� : ���س���� ������ �ڽĳ�带 ���س���� ��ġ�� �ø���,
				������ �ڽĳ���� ���� �ڽĳ�带 ���� ����� ������ �ڽĳ��� ���δ�.
				������ �ڽĳ���� ���� �ڽĳ��� ���س�带 �ٿ��ְ�,
				������ �ڽĳ���� �θ� ���س���� �θ�� �����Ѵ�.

	�� ���� (����)
	1. �� -> ��	:	1. ���س�带 ���������� ȸ���Ѵ�. 3-> 2-> 1�̿��ٸ� 2->1(��) 2->3(��)�� ����.
	2. �� -> ��	:	1. ���س���� ���� �ڽĳ�带 �������� ȸ��.
					2. ���س�带 ���������� ȸ��.
	3. �� -> ��	:	1. ���س�带 �������� ȸ��.
	4. �� -> ��	:	1. ���س���� ������ �ڽĳ�带 ���������� ȸ��.
					2. ���س�带 �������� ȸ��.

*/

template <typename Key, typename Value>
class CAVLTreeNode
{
	template <typename Key, typename Value>
	friend class CAVLTree;

	template <typename Key, typename Value>
	friend class CAVLTreeIterator;

private:
	CAVLTreeNode() {}
	~CAVLTreeNode() {}

public:
	Key		mKey;
	Value	mData;

private:
	CAVLTreeNode<Key, Value>* mParent = nullptr;
	CAVLTreeNode<Key, Value>* mLeft = nullptr;
	CAVLTreeNode<Key, Value>* mRight = nullptr;
	CAVLTreeNode<Key, Value>* mNext = nullptr;
	CAVLTreeNode<Key, Value>* mPrev = nullptr;
};

template <typename Key, typename Value>
class CAVLTreeIterator
{
	template <typename Key, typename Value>
	friend class CAVLTree;

public:
	CAVLTreeIterator() {}
	~CAVLTreeIterator() {}

private:
	CAVLTreeNode<Key, Value>* mNode = nullptr;

public:
	bool operator == (const CAVLTreeIterator<Key, Value>& iter)	const
	{
		return mNode == iter.mNode;
	}

	bool operator != (const CAVLTreeIterator<Key, Value>& iter)	const
	{
		return mNode != iter.mNode;
	}

	const CAVLTreeIterator<Key, Value>& operator ++ ()
	{
		mNode = mNode->mNext;
		return *this;
	}

	const CAVLTreeIterator<Key, Value>& operator ++ (int)
	{
		mNode = mNode->mNext;
		return *this;
	}

	const CAVLTreeIterator<Key, Value>& operator -- ()
	{
		mNode = mNode->mPrev;
		return *this;
	}

	const CAVLTreeIterator<Key, Value>& operator -- (int)
	{
		mNode = mNode->mPrev;
		return *this;
	}

	const CAVLTreeNode<Key, Value>* operator -> ()	const
	{
		return mNode;
	}
};


template <typename Key, typename Value>
class CAVLTree
{
private:
	typedef CAVLTreeNode<Key, Value>	NODE;

public:
	typedef CAVLTreeIterator<Key, Value>	iterator;

public:
	CAVLTree()
	{
		mBegin = new NODE;
		mEnd = new NODE;

		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
	}

	~CAVLTree()
	{
		clear();
		delete mBegin;
		delete mEnd;
	}

private:
	NODE* mRoot = nullptr;
	NODE* mBegin;
	NODE* mEnd;
	int		mSize = 0;

public:
	void insert(const Key& key, const Value& Data)
	{
		if (!mRoot)
		{
			mRoot = new NODE;
			mRoot->mKey = key;
			mRoot->mData = Data;

			mBegin->mNext = mRoot;
			mRoot->mPrev = mBegin;

			mRoot->mNext = mEnd;
			mEnd->mPrev = mRoot;
		}

		else
		{
			insert(key, Data, mRoot);
		}

		++mSize;
	}

	bool empty()	const
	{
		return mSize == 0;
	}

	int size()	const
	{
		return mSize;
	}

	void clear()
	{		
		NODE* Node = mBegin->mNext;

		while (Node != mEnd)
		{
			NODE* Next = Node->mNext;
			delete Node;
			Node = Next;
		}

		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;

		mSize = 0;
	}

	iterator begin()	const
	{
		iterator	iter;
		iter.mNode = mBegin->mNext;
		return iter;
	}

	iterator end()	const
	{
		iterator	iter;
		iter.mNode = mEnd;
		return iter;
	}

	iterator find(const Key& key)	const
	{
		return find(key, mRoot);
	}

	// Ű�� ����
	iterator erase(const Key& key)
	{
		iterator iter = find(key);

		return erase(iter);
	}
	// ���ͷ����� �� ����.
	// const�� ���� ������ ���߿� ���� ����Ǿ� ��ȯ�Ǹ� �ȵǱ� ����.
	iterator erase(iterator& iter)
	{
		if (iter.mNode == mEnd)
			return iter;

		NODE* DeleteNode = nullptr;
		NODE* ResultNode = nullptr;

		// ���� Node�� leaf Node�� ���
		if (!iter.mNode->mLeft && iter.mNode->mRight)
		{
			// ���� Node�� �θ�Node�� �������� ���������� �Ǵ��Ͽ� ��ũ�� ����.
			// ������ Parent�� �ִ������� üũ�ؾ� �Ѵ�.
			NODE* Parent = iter.mNode->mParent;

			if (Parent)
			{
				// �θ��� ���� (�θ𺸴� ���� ���� ������ Node)
				if (iter.mNode == Parent.mLeft)
				{
					Parent->mLeft = nullptr;
				}
				// �θ��� ������ (�θ𺸴� ū ���� ������ Node)
				else
				{
					Parent->mRight = nullptr;
				}
			}
			else
			{
				mRoot = nullptr;
			}

			DeleteNode = iter.mNode;
			ResultNode = DeleteNode->mNext;

		}
		else
		{
			NODE* ChildNode = nullptr;

			// ���ʿ��� ����ū �� (�� ���� ������ ������ ��)
			if (iter.mNode->mLeft)
			{
				// ���� ��尡 ���� ��� ���� ��忡�� ���� ū 
				// ��带 ã�Ƽ� ������ ���� ���.
				DeleteNode = FindMax(iter.mNode->mLeft);
				ChildNode = DeleteNode->mLeft;
				ResultNode = iter.mNode->mNext;
			}
			// �����ʿ��� ���� ���� �� (�� ������ ������ ���� ��)
			else
			{
				// ������ ��尡 ���� ��� ������ ��忡�� ���� ����
				// ��带 ã�Ƽ� ������ ���� ���.
				DeleteNode = FindMin(iter.mNode->mRight);
				ChildNode = DeleteNode->mRight;
				ResultNode = iter.mNode;
			}
		}
		// ������ ã�� ����� ������ iterator�� 
		// �������ִ� Node�� ���� ��ü�Ѵ�.
		iter.mNode->mKey = DeleteNode->mKey;
		iter.mNode->mData = DeleteNode->mData;

		NODE* Parent = DeleteNode->mParent;

		if (Parent)
		{
			if (DeleteNode == Parent->mLeft)
			{
				Parent->mLeft = ChildNode;
			}
			else
			{
				Parent->mRight = ChildNode;
			}
		}

		if (ChildNode)
		{
			ChildNode->mParent = Parent;
		}

		NODE* Prev = DeleteNode->mPrev;
		NODE* Next = DeleteNode->mNext;

		// ������ ���� ��ȯ.
		Prev->mNext = Next;
		Next->mPrev = Prev;

		ReBalance(DeleteNode->mParent);

		delete DeleteNode;

		mSize--;

		iterator result;
		result.mNode = ResultNode;

		return result;
	}

	// ���� ���� ���� ��ȸ 3���� ���
	// ���� : ��Ʈ > ���� > ������ ������ �о�� ���.
	void PreOrder()
	{
		PreOrder(mRoot);
	}

	// ���� : ���� -> ��Ʈ -> ������
	void InOrder()
	{
		InOrder(mRoot);
	}

	// ���� : ���� -> ������ -> ��Ʈ
	void PostOrder()
	{
		PostOrder(mRoot);
	}

	void OutputTreeInfo()
	{
		OutputTreeInfo(mRoot);
	}

private:
	void OutputTreeInfo(NODE* Node)
	{
		if (!Node)
			return;

		std::cout << "Key : " << Node->mKey << ", Value : " <<
			Node->mData << std::endl;
		std::cout << "Parent : ";
		if (Node->mParent)
			std::cout << Node->mParent->mKey << std::endl;
		else
			std::cout << "����" << std::endl;

		std::cout << "Left : ";
		if (Node->mLeft)
			std::cout << Node->mLeft->mKey << std::endl;
		else
			std::cout << "����" << std::endl;

		std::cout << "Right : ";
		if (Node->mRight)
			std::cout << Node->mRight->mKey << std::endl;
		else
			std::cout << "����" << std::endl;

		OutputTreeInfo(Node->mLeft);
		OutputTreeInfo(Node->mRight);
	}


	void insert(const Key& key, const Value& Data,
		NODE* Node)
	{
		if (!Node)
			return;

		// ���ڷ� ���� Ű�� ����� Ű�� ���Ͽ�
		// �������� ���������� �Ǵ��Ѵ�.
		if (key < Node->mKey)
		{
			// ���ʿ� �߰��ؾ� �ϴµ� ���� ��尡 ���� ���
			if (!Node->mLeft)
			{
				NODE* NewNode = new NODE;

				NewNode->mKey = key;
				NewNode->mData = Data;

				// �θ����� ���� ���� �߰��Ѵ�.
				Node->mLeft = NewNode;
				// ���� ������ ����� �θ�� �߰��Ѵ�.
				NewNode->mParent = Node;

				// ���ʿ� �߰��ɶ��� �θ���� �θ�����
				// ������� ���̿� �߰��Ѵ�.
				NODE* Prev = Node->mPrev;

				Prev->mNext = NewNode;
				NewNode->mPrev = Prev;

				NewNode->mNext = Node;
				Node->mPrev = NewNode;

				ReBalance(Node->mParent);
			}

			else
			{
				insert(key, Data, Node->mLeft);
			}
		}

		else
		{
			// �����ʿ� �߰��ؾ� �� ���
			if (!Node->mRight)
			{
				NODE* NewNode = new NODE;

				NewNode->mKey = key;
				NewNode->mData = Data;

				// �θ����� ������ ���� �߰��Ѵ�.
				Node->mRight = NewNode;
				// ���� ������ ����� �θ�� �߰��Ѵ�.
				NewNode->mParent = Node;

				// �����ʿ� �߰��ɶ��� �θ���� �θ�����
				// ������� ���̿� �߰��Ѵ�.
				NODE* Next = Node->mNext;

				Node->mNext = NewNode;
				NewNode->mPrev = Node;

				NewNode->mNext = Next;
				Next->mPrev = NewNode;

				ReBalance(Node->mParent);
			}

			else
			{
				insert(key, Data, Node->mRight);
			}
		}
	}

	iterator find(const Key& key, NODE* Node)	const
	{
		if (!Node)
			return end();

		if (key == Node->mKey)
		{
			iterator	iter;
			iter.mNode = Node;
			return iter;
		}

		else if (key < Node->mKey)
			return find(key, Node->mLeft);

		return find(key, Node->mRight);
	}

	NODE* FindMin(NODE* Node)
	{
		// ���� ��1
		/*
		while (Node->mLeft)
		{
			Node = Node->mLeft;
		}

		return Node;
		*/

		if (!Node->mLeft)
			return Node;

		return FindMin(Node->mLeft);
	}

	NODE* FindMax(NODE* Node)
	{
		// �ΰ��� ��� �� ��1
		while (Node->mRight)
		{
			Node = Node->mRight;
		}

		return Node;

		/*
		if (!Node->mRight)
			return Node;

		return FindMax(Node->mRight);
		*/
	}

	void PreOrder(NODE* Node)
	{
		// ��� ������ ����
		if (!Node)
			return;

		std::cout << "Key : " << Node->mKey << ", \tValue : " << Node->mData << std::endl;
		PreOrder(Node->mLeft);
		PreOrder(Node->mRight);
	}

	void InOrder(NODE* Node)
	{
		// ��� ������ ����
		if (!Node)
			return;

		InOrder(Node->mLeft);
		std::cout << "Key : " << Node->mKey << ", \tValue : " << Node->mData << std::endl;
		InOrder(Node->mRight);
	}

	void PostOrder(NODE* Node)
	{
		// ��� ������ ����
		if (!Node)
			return;

		PostOrder(Node->mLeft);
		PostOrder(Node->mRight);
		std::cout << "Key : " << Node->mKey << ", \tValue : " << Node->mData << std::endl;
	}

	NODE* RotationLeft(NODE* Node)
	{
		NODE* RightChild = Node->mRight;
		NODE* RCLeftChild = RightChild->mLeft;
		NODE* Parent = Node->mParent;

		if(Parent)
		{
			if (Parent->mLeft == Node)
			{
				Parent->mLeft = RightChild;
			}
			else
			{
				Parent->mRight = RightChild;
			}
		}
		else
		{
			mRoot = RightChild;
		}

		RightChild->mParent = Parent;
		RightChild->mLeft = Node;
		Node->mParent = RightChild;
		Node->mRight = RCLeftChild;

		if (RCLeftChild)
		{
			RCLeftChild->mParent = Node;
		}

		return RightChild;
	}

	NODE* RotationRight(NODE* Node)
	{
		NODE* LeftChild = Node->mLeft;
		NODE* LCRightChild = LeftChild->mRight;
		NODE* Parent = Node->mParent;

		if (Parent)
		{
			if (Parent->mLeft == Node)
			{
				Parent->mLeft = LeftChild;
			}
			else
			{
				Parent->mRight = LeftChild;
			}
		}
		else
		{
			mRoot = LeftChild;
		}

		LeftChild->mParent = Parent;
		LeftChild->mLeft = Node;
		Node->mParent = LeftChild;
		Node->mRight = LCRightChild;

		if (LCRightChild)
		{
			LCRightChild->mParent = Node;
		}

		return LeftChild;
	}

	int GetHeight(NODE* Node)
	{
		// Child�� �� �̻� �������� ������ nullptr�� ���� ���̴�.
		if (!Node)
			return 0;

		int Left = GetHeight(Node->mLeft);
		int Right = GetHeight(Node->mRight);

		return Left < Right ? Right + 1 : Left + 1;		
	}

	// ���ڷ� ���� ��带 �������� ���ʰ� �������� �������̸� ���Ѵ�.
	int BalanceFactor(NODE* Node)
	{
		if (!Node)
			return 0;

		// ���밪�� �ʿ��ϴ�.
		// ���ʿ��� 0�̳����� �����ʿ��� -2�� ������ ������ ������,
		// ���ʿ��� 2�� ������ ���������� 0�̳����� +2�� �Ǳ⿡,
		// ���밪���� ����� ������Ѵ�.
		return GetHeight(Node->mLeft) - GetHeight(Node->mRight);
	}

	NODE* Balance(NODE* Node)
	{
		int Factor = BalanceFactor(Node);

		// ������ ���������� üũ
		if (abs(Factor) < 2)
			return;

		// ������ �������� ��� �������� ���������� �Ǵ�.
		// �� ��� ��� (��2 ��0 2 - 0�� ���)�� �Ǳ� ������
		// ������ ������ ���������� �ǹ��Ѵ�.
		if (Factor > 0)
		{
			// ���س���� �����ڽ� ��带 �־���,
			// ���⼭�� +�� ������ ���ʿ� �ڽĳ�尡 ������,
			// -�� ������ �����ʿ� �ڽĳ�尡 ������ �ǹ��Ѵ�.

			// 0���� ������ �ǹ��ϴ� ����,
			// �����ʿ� �ڽĳ�尡 �ִ����� üũ�ϴ� ���� �ǹ��Ѵ�.
			if (BalanceFactor(Node->mLeft) < 0)
			{
				// ���� �ڽ� ��带 �������� ȸ��.
				RotationLeft(Node->mLeft);
			}

			Node = RotationLeft(Node);
		}
		// ������ ������ ���������� �ǹ��Ѵ�.
		else
		{
			// ������ -> �������� ������ ������ ���
			if (BalanceFactor(Node->mRight) > 0)
			{
				// ������ �ڽĳ�带 ���������� ȸ����Ų��.
				RotationRight(Node->mRight);
			}

			// ���س�带 �������� ȸ����Ų��.
			Node = RotationLeft(Node);
		}

		return Node;
	}

	void ReBalance(NODE* Node)
	{
		while (Node)
		{
			Node = Balance(Node);

			Node = Node->mParent;
		}
	}
};




