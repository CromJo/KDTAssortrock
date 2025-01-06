#include <iostream>
#include <time.h>
#include <Windows.h>
#include "Heap.h"
#include "Sort.h"

#define ARRAY_COUNT 100000

bool SortFunc(const int& Source, const int& Dest)
{
	return Source < Dest;
}

int main()
{
	srand(time(0));
	rand();

	CHeap<int> heap;
	heap.SetSortFunction(SortFunc);

	CSort<int> sort;
	sort.SetSortFunction(SortFunc);

	int Array[ARRAY_COUNT] = {};

	LARGE_INTEGER	Start, End, Second;
	QueryPerformanceFrequency(&Second);
	QueryPerformanceCounter(&Start);

	for (int i = 0; i < ARRAY_COUNT; i++)
	{
		Array[i] = rand();
	}

	sort.MergeSort(Array, ARRAY_COUNT);

	QueryPerformanceCounter(&End);

	float	Time = (End.QuadPart - Start.QuadPart) /
		(float)Second.QuadPart;

	std::cout << "Time : " << Time << std::endl;

	return 0;
}