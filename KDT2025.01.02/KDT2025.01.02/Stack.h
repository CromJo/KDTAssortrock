#pragma once
#include <assert.h>


// �迭��� ���� �˰���
template <typename T>
class CStackDynamicArray
{
public:
	CStackDynamicArray() {}
	~CStackDynamicArray()
	{
		// nullptr�� �ƴϸ� (�ʱ�ȭ�� �Ǿ��ִٸ�)
		if (mStackArray)
		{
			delete[] mStackArray;
		}
	}

private:
	T* mStackArray = nullptr;
	int mSize = 0;
	int mCapacity = 0;

public:
	void push(const T& Data)
	{
		if (mCapacity == 0)
		{
			ReAlloc(1);
		}
		else if (mSize == mCapacity)
		{
			ReAlloc(mCapacity * 2);
		}

		mStackArray[mSize] = Data;
		mSize++;
	}

	// �������� ��� (�������� ���)
	T pop()
	{
		assert(mSize != 0);
		
		mSize--;

		return mStackArray[mSize];
	}

	// ����ִ��� üũ�ϱ� ���� �Լ�
	bool empty()	const
	{
		return mSize == 0;
	}

	int size()	const
	{
		return mSize;
	}

	int capacity()	const
	{
		return mCapacity;
	}

	void clear()
	{
		mSize = 0;
	}

private:
	void ReAlloc(int NewCapacity)
	{
		mCapacity = NewCapacity;

		T* Array = new T[mCapacity];

		if (nullptr != mStackArray)
		{
			memcpy(Array + 1, mStackArray + 1, sizeof(T) * mSize);
			delete[] mStackArray;
		}
		
		mStackArray = Array;
	}

};

template<typename T, int Count = 100>
class CStackStaticArray
{
public:
	CStackStaticArray() {}
	~CStackStaticArray()
	{

	}

private:
	// �������ϸ� Count (100���� ����)�� ������ �ʱ�ȭ
	// �����ϴ� �� : Ŭ���� �����Ҷ� �̸�<�ڷ���, ����>
	T* mStackArray[Count] = {};
	int mSize = 0;
	int mCapacity = 0;

public:
	void push(const T& Data)
	{
		assert(mSize != Count);

		mStackArray[mSize] = Data;
		mSize++;
	}

	T pop()
	{
		assert(mSize != 0);

		mSize--;

		return mStackArray[mSize];
	}

	// ����ִ��� üũ�ϱ� ���� �Լ�
	bool empty()	const
	{
		return mSize == 0;
	}

	int size()	const
	{
		return mSize;
	}

	int capacity()	const
	{
		return mCapacity;
	}

	void clear()
	{
		mSize = 0;
	}
};

template <typename T>
class CStackNode
{
	// CStackList�� CStackNode�� ���ٰ����ϵ��� ó�����ִ� ���
	// ���ø� ó���� ���ִ� ������, ��� �ڷ������� ������ ��밡���ϰ� ���ֱ� ����.
	template <typename T>
	friend class CStackList;

private:
	CStackNode() {}
	~CStackNode()
	{

	}

private:
	T mData;
	CStackNode<T>* mNext = nullptr;
};

template <typename T>
class CStackList
{
public:
	CStackList() {}
	~CStackList()
	{
		clear();
	}

private:
	CStackNode<T>* mEnd = nullptr;
	int mSize = 0;
	int mCapacity = 0;

public:
	void push(const T& Data)
	{
		CStackNode<T>* Node = new CStackNode<T>;
		
		Node->mData = Data;
		Node->mNext = mEnd;

		mEnd = Node;

		mSize++;
	}

	T pop()
	{
		assert(mSize != 0);

		CStackNode<T>* NextNode = mEnd->mNext;

		T Data = mEnd->mData;

		delete mEnd;

		mEnd = NextNode;

		mSize--;

		return Data;
	}

	// ����ִ��� üũ�ϱ� ���� �Լ�
	bool empty()	const
	{
		return mSize == 0;
	}

	int size()	const
	{
		return mSize;
	}

	int capacity()	const
	{
		return mCapacity;
	}

	void clear()
	{
		while (mEnd)
		{
			CStackNode<T>* Next = mEnd->mNext;
			
			delete mEnd;
			
			mEnd = Next;
		}

		mSize = 0;
	}
};