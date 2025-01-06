#pragma once

#include <memory.h>
#include <assert.h>

template <typename T>
class CArrayIterator
{
	template <typename T>
	friend class CArray;

public:
	CArrayIterator()
	{
	}

	~CArrayIterator()
	{
	}

public:
	T& operator * ()
	{
		return mArray->mArray[mIndex];
	}

	void operator ++ ()
	{
		++mIndex;
		assert((mIndex <= mArray->mSize + 1 &&
			mIndex >= 1));
	}

	void operator ++ (int)
	{
		++mIndex;
		assert((mIndex <= mArray->mSize + 1 &&
			mIndex >= 1));
	}

	void operator -- ()
	{
		--mIndex;
		assert((mIndex <= mArray->mSize + 1 &&
			mIndex >= 1));
	}

	void operator -- (int)
	{
		--mIndex;
		assert((mIndex <= mArray->mSize + 1 &&
			mIndex >= 1));
	}

	CArrayIterator<T> operator + (int Num)	const
	{
		CArrayIterator<T>	iter;
		iter.mArray = mArray;
		iter.mIndex = mIndex + Num;
		assert((iter.mIndex <= mArray->mSize + 1 &&
			iter.mIndex >= 1));

		return iter;
	}

	CArrayIterator<T> operator - (int Num)	const
	{
		CArrayIterator<T>	iter;
		iter.mArray = mArray;
		iter.mIndex = mIndex - Num;
		assert((iter.mIndex <= mArray->mSize + 1 &&
			iter.mIndex >= 1));

		return iter;
	}

	const CArrayIterator<T>& operator += (int Num)
	{
		mIndex += Num;
		assert((mIndex <= mArray->mSize + 1 &&
			mIndex >= 1));

		return *this;
	}

	const CArrayIterator<T>& operator -= (int Num)
	{
		mIndex -= Num;
		assert((mIndex <= mArray->mSize + 1 &&
			mIndex >= 1));

		return *this;
	}

	// =, ->
	bool operator == (const CArrayIterator<T>& iter)	const
	{
		return mIndex == iter.mIndex;
	}

	bool operator != (const CArrayIterator<T>& iter)	const
	{
		return mIndex != iter.mIndex;
	}

private:
	int	mIndex = -1;
	CArray<T>* mArray;
	//T* mValue = nullptr;
};

template <typename T>
class CArray
{
	template <typename T>
	friend class CArrayIterator;

public:
	typedef CArrayIterator<T>	iterator;

public:
	CArray()
	{
	}

	CArray(const CArray<T>& Arr)
	{
	}

	CArray(CArray<T>&& Arr)
	{
	}

	~CArray()
	{
		if (nullptr != mArray)
			delete[] mArray;
	}

private:
	T* mArray = nullptr;
	int	mSize = 0;
	int	mCapacity = 0;

public:
	void push_back(const T& Data)
	{
		// �迭�� �� á���� �Ǵ��Ѵ�.
		if (mCapacity == mSize)
		{
			if (nullptr == mArray)
			{
				ReAlloc(1);
			}

			else
			{
				int	NewCapacity = (int)(mCapacity * 1.5f);

				if (NewCapacity == 1)
					NewCapacity = 2;

				ReAlloc(NewCapacity);
			}
		}

		mArray[mSize + 1] = Data;
		++mSize;
	}

	void push_back(T&& Data)
	{
		// �迭�� �� á���� �Ǵ��Ѵ�.
		if (mCapacity == mSize)
		{
			if (nullptr == mArray)
			{
				ReAlloc(1);
			}

			else
			{
				int	NewCapacity = (int)(mCapacity * 1.5f);

				if (NewCapacity == 1)
					NewCapacity = 2;

				ReAlloc(NewCapacity);
			}
		}

		mArray[mSize + 1] = Data;
		++mSize;
	}

	void pop_back()
	{
		assert(mSize != 0);

		--mSize;
	}

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

	// reserve�� ���� capacity���� �۰�
	// ������ ��� �ƹ��� �ϵ� ����.
	// Ŭ ��� ���� ������� �״�� �����ϸ�
	// capacity�� ������ ũ��� �þ��
	// �迭 ũ�⸸ �̸�ŭ ����� �ȴ�.
	// ������ ���� �״�� �����ȴ�.
	void reserve(int NewCapacity)
	{
		if (NewCapacity > mCapacity)
		{
			ReAlloc(NewCapacity);
		}
	}

	// resize�� ���� capacity���� �۰�
	// ������ ��� capacity�� �����ϸ�
	// size�� ���ҽ�Ų��.
	// Ŭ ��쿡�� capacity�� �÷��ش�.
	// ������ ���ִ� ���� �ִٸ� �����Ѵ�.
	void resize(int NewCapacity)
	{
		/*if (NewCapacity < mCapacity)
		{
			mSize = NewCapacity;
		}*/

		if (NewCapacity > mCapacity)
		{
			ReAlloc(NewCapacity);
		}

		mSize = NewCapacity;
	}

	T& operator [] (int Index)
	{
		assert(0 <= Index && Index < mSize);

		return mArray[Index + 1];
	}

	iterator begin()
	{
		iterator	iter;
		iter.mArray = this;
		iter.mIndex = 1;
		return iter;
	}

	iterator end()
	{
		iterator	iter;
		iter.mArray = this;
		iter.mIndex = mSize + 1;
		return iter;
	}

	iterator erase(const iterator& iter)
	{
		assert((iter.mIndex < mSize + 1 &&
			iter.mIndex >= 1));

		for (int i = iter.mIndex; i < mSize; ++i)
		{
			mArray[i] = mArray[i + 1];
		}

		--mSize;

		return iter;
	}

private:
	void ReAlloc(int NewCapacity)
	{
		mCapacity = NewCapacity;
		// Begin�� End�� ǥ���ϱ� ����
		// �������� 2���� �� �ʿ��ϴ�.
		T* Array = new T[mCapacity + 2];

		// ���� �����Ͱ� ���� ��� ����
		if (nullptr != mArray)
		{
			// ���� �����͸� ������ �� 1������
			// ������ŭ ����
			memcpy(Array + 1, mArray + 1,
				sizeof(T) * mSize);
			delete[] mArray;
		}

		mArray = Array;
	}
};

