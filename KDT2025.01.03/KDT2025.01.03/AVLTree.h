#pragma once

/*
	트리의 균형을 맞추기 위해 노드를 기준으로 왼/오른쪽의 높이 차이를 구하여,
	높이 차이가 2이상 발생할 경우 트리의 균형이 무너진 것으로 판단.
	
	균형의 무너진 종류는 총 4가지가 있다.
	균형이 무너진 경우 트리의 회전을 이용하여 균형을 맞춘다.
	회전은 왼쪽회전, 오른쪽 회전 2가지가 있다.

	오른쪽회전 : 기준이 되는 노드의 왼쪽 자식노드를 기준노드의 위치로 올리고,
				왼쪽 자식노드의 오른쪽 자식노드를 기준노드의 왼쪽 자식노드로 붙여준다.
				왼쪽 자식노드의 부모를 기준노드의 부모로 변경한다.

	왼쪽 회전 : 기준노드의 오른쪽 자식노드를 기준노드의 위치로 올리고,
				오른쪽 자식노드의 왼쪽 자식노드를 기준 노드의 오른쪽 자식노드로 붙인다.
				오른쪽 자식노드의 왼쪽 자식노드로 기준노드를 붙여주고,
				오른쪽 자식노드의 부모를 기준노드의 부모로 변경한다.

	※ 방향 (가지)
	1. 왼 -> 왼	:	1. 기준노드를 오른쪽으로 회전한다. 3-> 2-> 1이였다면 2->1(왼) 2->3(오)로 변경.
	2. 왼 -> 오	:	1. 기준노드의 왼쪽 자식노드를 왼쪽으로 회전.
					2. 기준노드를 오른쪽으로 회전.
	3. 오 -> 오	:	1. 기준노드를 왼쪽으로 회전.
	4. 오 -> 왼	:	1. 기준노드의 오른쪽 자식노드를 오른쪽으로 회전.
					2. 기준노드를 왼쪽으로 회전.

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
		if (!iter.mNode->mLeft && iter.mNode->mRight)
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

		NODE* Prev = DeleteNode->mPrev;
		NODE* Next = DeleteNode->mNext;

		// 서로의 값을 교환.
		Prev->mNext = Next;
		Next->mPrev = Prev;

		ReBalance(DeleteNode->mParent);

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

	// 후위 : 왼쪽 -> 오른쪽 -> 루트
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
			std::cout << "없음" << std::endl;

		std::cout << "Left : ";
		if (Node->mLeft)
			std::cout << Node->mLeft->mKey << std::endl;
		else
			std::cout << "없음" << std::endl;

		std::cout << "Right : ";
		if (Node->mRight)
			std::cout << Node->mRight->mKey << std::endl;
		else
			std::cout << "없음" << std::endl;

		OutputTreeInfo(Node->mLeft);
		OutputTreeInfo(Node->mRight);
	}


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

				ReBalance(Node->mParent);
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
		// Child가 더 이상 존재하지 않으면 nullptr이 나올 것이다.
		if (!Node)
			return 0;

		int Left = GetHeight(Node->mLeft);
		int Right = GetHeight(Node->mRight);

		return Left < Right ? Right + 1 : Left + 1;		
	}

	// 인자로 들어온 노드를 기준으로 왼쪽과 오른쪽의 높이차이를 구한다.
	int BalanceFactor(NODE* Node)
	{
		if (!Node)
			return 0;

		// 절대값이 필요하다.
		// 왼쪽에서 0이나오고 오른쪽에서 -2가 나오면 음수가 되지만,
		// 왼쪽에서 2가 나오고 오른족에서 0이나오면 +2가 되기에,
		// 절대값으로 계산을 해줘야한다.
		return GetHeight(Node->mLeft) - GetHeight(Node->mRight);
	}

	NODE* Balance(NODE* Node)
	{
		int Factor = BalanceFactor(Node);

		// 균형이 망가졌는지 체크
		if (abs(Factor) < 2)
			return;

		// 균형이 무너졌을 경우 왼쪽인지 오른쪽인지 판단.
		// 이 경우 양수 (왼2 오0 2 - 0의 경우)가 되기 때문에
		// 왼쪽의 균형이 무너졌음을 의미한다.
		if (Factor > 0)
		{
			// 기준노드의 왼쪽자식 노드를 넣었고,
			// 여기서도 +가 나오면 왼쪽에 자식노드가 있음을,
			// -가 나오면 오른쪽에 자식노드가 있음을 의미한다.

			// 0보다 낮음을 의미하는 것은,
			// 오른쪽에 자식노드가 있는지를 체크하는 것을 의미한다.
			if (BalanceFactor(Node->mLeft) < 0)
			{
				// 왼쪽 자식 노드를 왼쪽으로 회전.
				RotationLeft(Node->mLeft);
			}

			Node = RotationLeft(Node);
		}
		// 오른쪽 균형이 무너졌음을 의미한다.
		else
		{
			// 오른쪽 -> 왼쪽으로 균형이 무너진 경우
			if (BalanceFactor(Node->mRight) > 0)
			{
				// 오른쪽 자식노드를 오른쪽으로 회전시킨다.
				RotationRight(Node->mRight);
			}

			// 기준노드를 왼쪽으로 회전시킨다.
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




