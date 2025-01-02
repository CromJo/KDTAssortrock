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
};

