#include <iostream>
#include <time.h>
/*
	���� �˰���
	1. 

	�������� :
	�������� :
		�� ������ ���� : �����Ͱ� ������ �ӵ��� ������.

	�������� : ���� �� -> ū ���� ����
	�������� : ū �� -> ���� ���� ����

	������		: 2��Ʈ�� ���Ĺ��
	������		: 
	�պ�����		: 
*/

void BubbleSort(int* Array, int Count)
{
	for (int i = 0; i < Count - 1; i++)
	{
		for (int j = 0; j < Count - i - 1; j++)
		{
			if (Array[j] > Array[j + 1])
			{
				int Temp = Array[j];
				Array[j] = Array[j + 1];
				Array[j + 1] = Temp;
			}
		}
	}
}

void SelectionSort(int* Array, int Count)
{
	for (int i = 0; i < Count - 1; i++)
	{
		for (int j = i + 1; j < Count - i - 1; j++)
		{
			if (Array[i] > Array[j])
			{
				int Temp = Array[i];
				Array[i] = Array[j];
				Array[j] = Temp;
			}
		}
	}
}

int main()
{
	srand(time(0));
	rand();

	int Num[10] = {};

	for (int i = 0; i < 10; i++)
	{
		Num[i] = rand();
		std::cout << Num[i] << ", ";
	}

	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	BubbleSort(Num, 10);
	
	for (int i = 0; i < 10; i++)
	{
		std::cout << Num[i] << ", ";
	}


	return 0; 
}