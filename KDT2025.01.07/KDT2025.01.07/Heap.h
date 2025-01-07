#pragma once
#include "Array.h"


template <typename T>
class CHeap
{
public:
	CHeap() {}
	~CHeap()
	{

	}

private:
	CArray<T> mArray;
	bool (*mFunc)(const T&, const T&) = nullptr;

public:
	void SetSortFunction(bool(*Func)(const T&, const T&))
	{
		mFunc = Func;
	}

public:
	void insert(const T& Data)
	{
		if (!mFunc)
			return;

		mArray.push_back(Data);

		insert(mArray.size() / 2 - 1, mArray.size() - 1);
	}

	void insert(const T* Array, int Count)
	{
		for (int i = 0; i < Count; i++)
		{
			mArray.push_back(Array[i]);

			insert(mArray.size() / 2 - 1, mArray.size() - 1);
		}
	}

	const T& front()
	{
		return mArray[0];
	}

	void pop()
	{
		mArray[0] = mArray[mArray.size() - 1];
		mArray.pop_back();

		erase(0);
	}

	int size() const
	{
		return mArray.size();
	}

	bool empty()	const
	{
		return mArray.empty();
	}

private:
	void insert(int ParentIndex, int CurrentIndex)
	{
		if (ParentIndex < 0)
			return;

		if (mFunc(mArray[ParentIndex], mArray[CurrentIndex]))
		{
			T Temp = mArray[ParentIndex];
			mArray[ParentIndex] = mArray[CurrentIndex];
			mArray[CurrentIndex] = Temp;

			insert((ParentIndex + 1) / 2 - 1, ParentIndex);
		}
	}
		
	void erase(int CurrentIndex)
	{
		int Count = mArray.size();
		int LeftChild = CurrentIndex * 2 + 1;

		// 자식노드가 없을 경우
		if (LeftChild >= Count)
			return;

		int RightChild = LeftChild + 1;
		int ChildIndex = LeftChild;

		if (RightChild < Count)
		{
			// 왼/오른쪽 자식 중 연산할 자식을 구한다.
			// 최소힙 : 작은 숫자
			// 최대힙 : 큰 숫자
			if (mFunc(mArray[LeftChild], mArray[RightChild]))
			{
				ChildIndex = RightChild;
			}

			if (mFunc(mArray[CurrentIndex], mArray[ChildIndex]))
			{
				T Temp = mArray[ChildIndex];
				mArray[ChildIndex] = mArray[CurrentIndex];
				mArray[CurrentIndex] = Temp;

				erase(ChildIndex);
			}
		}
	}
};

