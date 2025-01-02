#pragma once
#include <assert.h>


// 배열기반 스택 알고리즘
template <typename T>
class CStackDynamicArray
{
public:
	CStackDynamicArray() {}
	~CStackDynamicArray()
	{
		// nullptr이 아니면 (초기화가 되어있다면)
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

	// 내보내기 기능 (선입후출 기능)
	T pop()
	{
		assert(mSize != 0);
		
		mSize--;

		return mStackArray[mSize];
	}

	// 비어있는지 체크하기 위한 함수
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
	// 지정안하면 Count (100으로 설정)된 값으로 초기화
	// 지정하는 법 : 클래스 선언할때 이름<자료형, 갯수>
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

	// 비어있는지 체크하기 위한 함수
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
	// CStackList가 CStackNode에 접근가능하도록 처리해주는 기능
	// 템플릿 처리를 해주는 이유는, 어떠한 자료형으로 들어오든 사용가능하게 해주기 위함.
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

	// 비어있는지 체크하기 위한 함수
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