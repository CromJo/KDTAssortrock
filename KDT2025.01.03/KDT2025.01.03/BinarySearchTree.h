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

	// 키값 삭제
	iterator erase(const Key& key)
	{
		iterator iter = find(key);

		return erase(iter);
	}
	// 이터레이터 값 삭제.
	// const를 쓰는 이유는 도중에 값이 변경되어 반환되면 안되기 때문.
	iterator erase(iterator& iter)
	{
		if (iter.mNode == mEnd)
			return iter;

		NODE* DeleteNode = nullptr;
		NODE* ResultNode = nullptr;

		// 지울 Node가 leaf Node일 경우
		if (!iter.mNode->mLeft && !iter.mNode->mRight)
		{
			// 지울 Node가 부모Node의 왼쪽인지 오른쪽인지 판단하여 링크를 제거.
			// 그전에 Parent가 있는지부터 체크해야 한다.
			NODE* Parent = iter.mNode->mParent;

			if (Parent)
			{
				// 부모의 왼쪽 (부모보다 낮은 값을 가지는 Node)
				if (iter.mNode == Parent.mLeft)
				{
					Parent->mLeft = nullptr;
				}
				// 부모의 오른쪽 (부모보다 큰 값을 가지는 Node)
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

			// 왼쪽에서 가장큰 값 (즉 왼쪽 내에서 오른쪽 값)
			if (iter.mNode->mLeft)
			{
				// 왼쪽 노드가 있을 경우 왼쪽 노드에서 가장 큰 
				// 노드를 찾아서 삭제할 노드로 사용.
				DeleteNode = FindMax(iter.mNode->mLeft);
				ChildNode = DeleteNode->mLeft;
				ResultNode = iter.mNode->mNext;
			}
			// 오른쪽에서 가장 작은 값 (즉 오른쪽 내에서 왼쪽 값)
			else
			{
				// 오른쪽 노드가 있을 경우 오른쪽 노드에서 가장 작은
				// 노드를 찾아서 삭제할 노드로 사용.
				DeleteNode = FindMin(iter.mNode->mRight);
				ChildNode = DeleteNode->mRight;
				ResultNode = iter.mNode;
			}
			// 위에서 찾은 노드의 값으로 iterator가 
			// 가지고있는 Node의 값을 대체한다.
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

		// 서로의 값을 교환.
		Prev->mNext = Next;
		Next->mPrev = Prev;

		delete DeleteNode;

		mSize--;

		iterator result;
		result.mNode = ResultNode;

		return result;
	}

	// 전위 중위 후위 순회 3가지 방식
	// 전위 : 루트 > 왼쪽 > 오른쪽 순으로 읽어가는 방식.
	void PreOrder()
	{
		PreOrder(mRoot);
	}

	// 중위 : 왼쪽 -> 루트 -> 오른족
	void InOrder()
	{
		InOrder(mRoot);
	}

	// 후위 : 
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

		// 인자로 들어온 키와 노드의 키를 비교하여
		// 왼쪽인지 오른쪽인지 판단한다.
		if (key < Node->mKey)
		{
			// 왼쪽에 추가해야 하는데 왼쪽 노드가 없을 경우
			if (!Node->mLeft)
			{
				NODE* NewNode = new NODE;

				NewNode->mKey = key;
				NewNode->mData = Data;

				// 부모노드의 왼쪽 노드로 추가한다.
				Node->mLeft = NewNode;
				// 새로 생성한 노드의 부모로 추가한다.
				NewNode->mParent = Node;

				// 왼쪽에 추가될때는 부모노드와 부모노드의
				// 이전노드 사이에 추가한다.
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
			// 오른쪽에 추가해야 할 경우
			if (!Node->mRight)
			{
				NODE* NewNode = new NODE;

				NewNode->mKey = key;
				NewNode->mData = Data;

				// 부모노드의 오른쪽 노드로 추가한다.
				Node->mRight = NewNode;
				// 새로 생성한 노드의 부모로 추가한다.
				NewNode->mParent = Node;

				// 오른쪽에 추가될때는 부모노드와 부모노드의
				// 다음노드 사이에 추가한다.
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
		// 둘중 택1
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
		// 두가지 방법 중 택1
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
		// 노드 없으면 종료
		if (!Node)
			return;

		std::cout << "Key : " << Node->mKey << ", \tValue : " << Node->mData << std::endl;
		PreOrder(Node->mLeft);
		PreOrder(Node->mRight);
	}

	void InOrder(NODE* Node)
	{
		// 노드 없으면 종료
		if (!Node)
			return;

		InOrder(Node->mLeft);
		std::cout << "Key : " << Node->mKey << ", \tValue : " << Node->mData << std::endl;
		InOrder(Node->mRight);
	}

	void PostOrder(NODE* Node)
	{
		// 노드 없으면 종료
		if (!Node)
			return;

		PostOrder(Node->mLeft);
		PostOrder(Node->mRight);
		std::cout << "Key : " << Node->mKey << ", \tValue : " << Node->mData << std::endl;
	}
};

