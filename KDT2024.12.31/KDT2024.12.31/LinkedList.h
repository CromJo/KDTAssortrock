#pragma once
#include <assert.h>

template <typename T>
class CListNode
{
	template <typename T>
	friend class CListReverseIterator;

	template <typename T>
	friend class CListIterator;

	template <typename T>
	friend class CLinkedList;

private:
	CListNode()
	{
	}

	~CListNode()
	{
	}

private:
	T	mData;						// 어떤 데이터가 들어올지 모르기 때문에 memset으로만 초기화가 가능하다.
	CListNode<T>*	mNext = nullptr;
	CListNode<T>*	mPrev = nullptr;
};

template <typename T>
class CListIterator
{
	template <typename T>
	friend class CLinkedList;

public:
	CListIterator()
	{
	}

	~CListIterator()
	{
	}

private:
	CListNode<T>* mNode = nullptr;

public:
	// ==, !=, ++, --, *(역참조)
	bool operator == (const CListIterator<T>& iter) const
	{
		return mNode == iter.mNode;
	}

	bool operator != (const CListIterator<T>& iter) const
	{
		return mNode != iter.mNode;
	}

	const CListIterator<T>& operator ++ ()
	{
		mNode = mNode->mNext;
		assert(mNode != nullptr);

		return *this;
	}
	const CListIterator<T>& operator ++ (int)
	{
		mNode = mNode->mNext;
		assert(mNode != nullptr);

		return *this;
	}

	const CListIterator<T>& operator -- ()
	{
		mNode = mNode->mPrev;
		assert(mNode != nullptr);

		return *this;
	}

	const CListIterator<T>& operator -- (int)
	{
		mNode = mNode->mPrev;
		assert(mNode != nullptr);

		return *this;
	}

	T& operator * ()
	{
		assert(mNode != nullptr);
		return mNode->mData;
	}
};

template <typename T>
class CListReverseIterator
{
	template <typename T>
	friend class CLinkedList;

public:
	CListReverseIterator() {};
	~CListReverseIterator() {};

private:
	CListNode<T>* mNode = nullptr;


public:
	// ==, !=, ++, --, *(역참조)
	bool operator == (const CListReverseIterator<T>& riter) const
	{
		return mNode == riter.mNode;
	}

	bool operator != (const CListReverseIterator<T>& riter) const
	{
		return mNode != riter.mNode;
	}

	const CListReverseIterator<T>& operator ++ ()
	{
		mNode = mNode->mPrev;
		assert(mNode != nullptr);

		return *this;
	}
	const CListReverseIterator<T>& operator ++ (int)
	{
		mNode = mNode->mPrev;
		assert(mNode != nullptr);

		return *this;
	}

	const CListReverseIterator<T>& operator -- ()
	{
		mNode = mNode->mNext;
		assert(mNode != nullptr);

		return *this;
	}

	const CListReverseIterator<T>& operator -- (int)
	{
		mNode = mNode->mNext;
		assert(mNode != nullptr);

		return *this;
	}

	T& operator * ()
	{
		assert(mNode != nullptr);
		return mNode->mData;
	}
};


template <typename T>
class CLinkedList
{
private:
	// 이 클래스에서 CListNode<T> 대신 NODE를 쓸 수 있게 한다.
	typedef CListNode<T>	NODE;

public:
	typedef CListIterator<T> iterator;
	typedef const CListIterator<T> const_iterator;
	
	typedef CListReverseIterator<T> riterator;
	typedef const CListReverseIterator<T> const_riterator;

public:
	CLinkedList()
	{
		//CListNode<T>* Node = new cListNode<T>;
	
		mBegin = new NODE;
		mEnd = new NODE;

		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
	}

	~CLinkedList()
	{
		clear();
		delete mBegin;
		delete mEnd;
	}

private:
	NODE* mBegin;
	NODE* mEnd;
	int mSize = 0;		// 몇개나 추가가 되었는지 체크하기 위한 데이터

public:
	void push_back(const T& Data)
	{
		NODE* Node = new NODE;

		Node->mData = Data;

		// End와 End의 이전노드 사이에 추가해야한다.
		NODE* Prev = mEnd->mPrev;

		Prev->mNext = Node;
		Node->mPrev = Prev;

		mEnd->mPrev = Node;
		Node->mNext = mEnd;

		mSize++;
	}

	void push_front(const T& Data)
	{
		NODE* Node = new NODE;

		Node->mData = Data;

		// Begin노드와 Begin의 다음노트의 사이에 추가한다.
		NODE* Next = mBegin->mNext;

		Node->mNext = Next;
		Next->mPrev = Node;

		mBegin->mNext = Node;
		Node->mPrev = mBegin;

		mSize++;	
	}

	void pop_back()
	{
		assert(mSize != 0);

		NODE* DeleteNode = mEnd->mPrev;
		NODE* Prev = DeleteNode->mPrev;

		Prev->mNext = mEnd;
		mEnd->mPrev = Prev;

		delete DeleteNode;
		mSize--;
	}

	void pop_front()
	{
		assert(mSize != 0);

		NODE* DeleteNode = mBegin->mNext;
		NODE* Next = DeleteNode->mNext;

		mBegin->mNext = Next;
		mEnd->mPrev = mBegin;

		delete DeleteNode;
		mSize--;
	}

	bool empty() const
	{
		return mSize == 0;
	}
	
	int size() const
	{
		return mSize;
	}

	void clear()
	{
		// Begin과 End를 제외하고 모두 제괴딘다.
		NODE* Node = mBegin->mNext;

		while (Node != mEnd)
		{
			// 지우기전에 다음노드를 미리 얻어온다.
			NODE* Next = Node->mNext;
			delete Node;
			Node = Next;
		}

		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
		mSize = 0;
	}

	// Begin노드의 다음노드를 가지고 있는 iterator를 반환.
	iterator begin()	const
	{
		iterator iter;
		iter.mNode = mBegin->mNext;

		return iter;
	}

	iterator end()	const
	{
		iterator iter;
		iter.mNode = mEnd;

		return iter;
	}

	void insert(const iterator& iter, const T& Data)
	{
		NODE* Node = new NODE;
		Node->mData = Data;

		NODE* Prev = iter.mNode->mPrev;

		Prev->mNext = Node;
		Node->mPrev = Prev;

		Node->mNext = iter.mNode;
		iter.mNode->mPrev = Node;

		mSize++;
	}

	iterator erase(const iterator& iter)
	{
		if (mSize == 0)
			return end();

		NODE* Prev = iter.mNode->mPrev;
		NODE* Next = iter.mNode->mNext;

		delete iter.mNode;

		Prev->mNext = Next;
		Next->mPrev = Prev;

		iterator result;
		result.mNode = Next;

		return result;
	}

	iterator erase(const iterator& first, const iterator& second)
	{
		assert(first.mNode);
		assert(second.mNode);

		assert(first.mNode != mBegin);
		assert(second.mNode != mBegin);

		assert(first.mNode != mEnd);
		assert(second.mNode != mEnd);

		iterator Check = second;
		Check++;

		iterator iterEnd;
		iterEnd.mNode = mEnd;

		for (; Check != iterEnd; Check++)
		{
			if (Check == first)
			{
				assert(Check != first);
			}

			NODE* Prev = first.mNode->mPrev;

			iterator iter = first;

			while (iter != second)
			{
				NODE* Next = iter.mNode->mNext;
				delete iter.mNode;
				iter.mNode = Next;
				mSize--;
			}

			for (iterator iter = first; iter != second; iter++)
			{
				delete iter.mNode;
				mSize--;
			}

			Prev->mNext = second.mNode;
			second.mNode->mPrev = Prev;

			return second;
		}
	}
	/*
		rbegin의 기능
		rbegin은 컨테이너의 마지막 요소를 가리키는 역방향 반복자를 반환합니다13. 이는 일반적인 begin()과는 반대로 작동합니다:
		방향: rbegin()은 컨테이너의 끝에서 시작하여 앞쪽으로 이동합니다2.
		시작 위치: 컨테이너의 마지막 요소를 가리킵니다3.
		사용 목적: 컨테이너를 역순으로 순회할 때 사용됩니다5.
	*/
	// Begin노드의 다음노드를 가지고 있는 iterator를 반환.
	riterator rbegin()	const
	{
		riterator riter;
		riter.mNode = mEnd->mPrev;

		return riter;
	}

	riterator rend()	const
	{
		riterator riter;
		riter.mNode = mBegin;

		return riter;
	}


};
