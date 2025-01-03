#pragma once

template <typename Key, typename Value>
class CBinarySearchTreeNode
{
	template <typename Key, typename Value>
	friend class CBinarySearchTree;

	template <typename Key, typename Value>
	friend class CBinarySearchTreeIterator;

private:
	CBinarySearchTreeNode() {}
	~CBinarySearchTreeNode() {}

public:
	Key		mKey;
	Value	mData;

private:
	CBinarySearchTreeNode<Key, Value>* mParent = nullptr;		
	CBinarySearchTreeNode<Key, Value>* mLeft = nullptr;			
	CBinarySearchTreeNode<Key, Value>* mRight = nullptr;		
	CBinarySearchTreeNode<Key, Value>* mNext = nullptr;			
	CBinarySearchTreeNode<Key, Value>* mPrev = nullptr;
};

template <typename Key, typename Value>
class CBinarySearchTreeIterator
{
	template <typename Key, typename Value>
	friend class CBinarySearchTree;

public:
	CBinarySearchTreeIterator() {}
	~CBinarySearchTreeIterator() {}

private:
	CBinarySearchTreeNode<Key, Value>* mNode = nullptr;

public:
	bool operator == (const CBinarySearchTreeIterator<Key, Value>& iter)	const
	{
		return mNode == iter.mNode;
	}

	bool operator != (const CBinarySearchTreeIterator<Key, Value>& iter)	const
	{
		return mNode != iter.mNode;
	}

	const CBinarySearchTreeIterator<Key, Value>& operator ++ ()
	{
		mNode = mNode->mNext;
		return *this;
	}

	const CBinarySearchTreeIterator<Key, Value>& operator ++ (int)
	{
		mNode = mNode->mNext;
		return *this;
	}

	const CBinarySearchTreeIterator<Key, Value>& operator -- ()
	{
		mNode = mNode->mPrev;
		return *this;
	}

	const CBinarySearchTreeIterator<Key, Value>& operator -- (int)
	{
		mNode = mNode->mPrev;
		return *this;
	}

	const CBinarySearchTreeNode<Key, Value>* operator -> ()	const
	{
		return mNode;
	}
};


template <typename Key, typename Value>
class CBinarySearchTree
{
private:
	typedef CBinarySearchTreeNode<Key, Value>	NODE;

public:
	typedef CBinarySearchTreeIterator<Key, Value>	iterator;

public:
	CBinarySearchTree()
	{
		mBegin = new NODE;
		mEnd = new NODE;

		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
	}

	~CBinarySearchTree()
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
		if (!iter.mNode->mLeft && !iter.mNode->mRight)
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
		}

		NODE* Prev = iter.mNode->mPrev;
		NODE* Next = iter.mNode->mNext;

		// ������ ���� ��ȯ.
		Prev->mNext = Next;
		Next->mPrev = Prev;

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

	// ���� : 
	void PostOrder()
	{
		PostOrder(mRoot);
	}


private:
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
};

