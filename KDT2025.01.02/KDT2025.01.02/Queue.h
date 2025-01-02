#pragma once
#include <assert.h>

template<typename T>
class CQueueNode
{
	template <typename T>
	friend class CQueue;

private:
	CQueueNode() {}
	~CQueueNode()
	{

	}

private:
	T mData;
	CQueueNode<T>* mNext = nullptr; 
};

template <typename T>
class CQueue
{
public:
	CQueue() {}
	~CQueue()
	{
		clear();
	}

private:
	CQueueNode<T>* mFirst = nullptr;
	CQueueNode<T>* mLast = nullptr;
	int mSize = 0;
	
public:
	void push(const T& Data)
	{
		CQueueNode<T>* Node = new CQueueNode<T>;
		Node->mData = Data;

		// nullptr일 경우
		if (!mFirst)
		{
			mFirst = Node;
		}
		// First에 값이 있을 경우 (이 경우 Last도 들어가있음을 의미함)
		else
		{
			mLast->mNext = Node;
		}

		mLast = Node;
		mSize++;
	}

	T pop()
	{
		assert(mSize != 0);

		CQueueNode<T>* Next = mFirst->mNext;
		T	Data = mFirst->mData;

		delete mFirst;

		mFirst = Next;
		mSize--;

		if (mSize == 0)
		{
			mLast = nullptr;
		}

		return Data;
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
		// First가 있으면 동작하도록 구현함
		while (mFirst)
		{
			CQueueNode<T>* Next = mFirst->mNext;
			
			delete mFirst;

			mFirst = Next;
		}

		mSize = 0;
		mLast = nullptr;
	}
};

template <typename T, int Count = 100>
class CCircleQueue
{
public:
	CCircleQueue() {}
	~CCircleQueue()
	{
		clear();
	}

private:
	T mQueueArray[Count] = {};
	int mSize = 0;
	int mHead = 0;		// pop (빼는 용)
	int mTail = 0;		// push(추가 용)

public:
	void push(const T& Data)
	{
		// 꽉찬 상태면 에러나도록 (false를 출력)
		assert(mSize != Count);

		mQueueArray[mTail] = Data;
		mTail = (mTail + 1) % Count;
		mSize++;
	}

	T pop()
	{
		assert(mSize != 0);

		T Data = mQueueArray[mHead];

		mHead = (mHead + 1) % Count;
		mSize--;

		return Data;
	}

	bool empty()	const
	{
		return mSize == 0;
	}

	bool full()		const
	{
		return mSize == Count;
	}

	int size()	const
	{
		return mSize;
	}

	void clear()
	{
		mSize = 0; 
		mHead = 0; 
		mTail = 0;
	}
};