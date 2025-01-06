#pragma once

template <typename T>
class CSort
{
public:
	CSort() {}
	~CSort()
	{
		if (mMergeArray)
			delete[] mMergeArray;
	}

private:
	bool (*mFunc)(const T&, const T&) = nullptr;
	T* mMergeArray = nullptr;

public:
	void SetSortFunction(bool(*Func)(const T&, const T&))
	{
		mFunc = Func;
	}

public:
	void QuickSort(T* Array, int Count)
	{
		if (!mFunc)
			return;

		QuickSort(Array, 0, Count - 1);

	}

private:
	void QuickSort(T* Array, int Left, int Right)
	{
		if (Left < Right)
		{
			int Pivot = Partition(Array, Left, Right);

			QuickSort(Array, Left, Pivot - 1);
			QuickSort(Array, Pivot + 1, Right);
		}
	}

	void Partition(T* Array, int Left, int Right)
	{
		int Low = Left;
		int High = Right + 1;
		T Pivot = Array[Left];

		do
		{
			do
			{
				Low++;
			} while (Low <= Right && mFunc(Pivot, Array[Low]));

			do
			{
				High--;
			} while (High >= Left && mFunc(Array[High], Pivot));

			if (Low < High)
			{
				T Temp = Array[Low];
				Array[Low] = Array[High];
				Array[High] = Temp;
			}
		} while (Low < High);
		
		T Temp = Array[Left];
		Array[Left] = Array[High];
		Array[High] = Temp;

		return High;
	}

public:
	void MergeSort(T* Array, int Count)
	{
		mMergeArray = new T[Count];

		MergeSort(Array, 0, Count - 1);

		delete[] mMergeArray;
		
		mMergeArray = nullptr;
	}

private:
	void MergeSort(T* Array, int Left, int Right)
	{
		if (Left < Right)
		{
			int Mid = (Left + Right) / 2;

			MergeSort(Array, Left, Mid);
			MergeSort(Array, Mid + 1, Right);
			Merge(Array, Left, Mid, Right);
		}
	}

	void Merge(T* Array, int Left, int Mid, int Right)
	{
		int SourceLeft = Left;
		int SourceRight = Mid + 1;
		int Dest = Left;

		while (SourceLeft <= Mid && SourceRight <= Right)
		{
			if (mFunc(Array[SourceLeft], Array[SourceRight]))
			{
				mMergeArray[Dest] = Array[SourceRight];
				SourceRight++;
				Dest++;
			}
			else
			{
				mMergeArray[Dest] = Array[SourceLeft];
				SourceLeft++;
				Dest++;
			}
		}

		if (SourceLeft <= Mid)
		{
			for (int i = SourceLeft; i <= Mid; i++)
			{
				mMergeArray[Dest] = Array[i];
				Dest++;
			}
		}
		else
		{
			for (int i = SourceRight; i <= Right; i++)
			{
				mMergeArray[Dest] = Array[i];
				Dest++;
			}
		}

		// 위에서 Left/Right까지 정렬을 새로운 배열에 해놨으므로,
		// 그 값으로 원본 배열의 값을 채운다.
		for (int i = Left; i <= Right; i++)
		{
			Array[i] = mMergeArray[i];
		}

	}
};

