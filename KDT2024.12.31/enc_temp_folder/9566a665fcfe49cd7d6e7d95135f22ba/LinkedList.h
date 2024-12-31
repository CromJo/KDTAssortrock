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
	T	mData;						// � �����Ͱ� ������ �𸣱� ������ memset���θ� �ʱ�ȭ�� �����ϴ�.
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
	// ==, !=, ++, --, *(������)
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
	// ==, !=, ++, --, *(������)
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
	// �� Ŭ�������� CListNode<T> ��� NODE�� �� �� �ְ� �Ѵ�.
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
	int mSize = 0;		// ��� �߰��� �Ǿ����� üũ�ϱ� ���� ������

public:
	void push_back(const T& Data)
	{
		NODE* Node = new NODE;

		Node->mData = Data;

		// End�� End�� ������� ���̿� �߰��ؾ��Ѵ�.
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

		// Begin���� Begin�� ������Ʈ�� ���̿� �߰��Ѵ�.
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
		// Begin�� End�� �����ϰ� ��� �������.
		NODE* Node = mBegin->mNext;

		while (Node != mEnd)
		{
			// ��������� ������带 �̸� ���´�.
			NODE* Next = Node->mNext;
			delete Node;
			Node = Next;
		}

		mBegin->mNext = mEnd;
		mEnd->mPrev = mBegin;
		mSize = 0;
	}

	// Begin����� ������带 ������ �ִ� iterator�� ��ȯ.
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
		int* a;		// ������
		int b = 0;		// ��
		a = &b;

		int& c = b;
		a = &c;


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
		rbegin�� ���
		rbegin�� �����̳��� ������ ��Ҹ� ����Ű�� ������ �ݺ��ڸ� ��ȯ�մϴ�13. �̴� �Ϲ����� begin()���� �ݴ�� �۵��մϴ�:
		����: rbegin()�� �����̳��� ������ �����Ͽ� �������� �̵��մϴ�2.
		���� ��ġ: �����̳��� ������ ��Ҹ� ����ŵ�ϴ�3.
		��� ����: �����̳ʸ� �������� ��ȸ�� �� ���˴ϴ�5.
	*/
	// Begin����� ������带 ������ �ִ� iterator�� ��ȯ.
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
