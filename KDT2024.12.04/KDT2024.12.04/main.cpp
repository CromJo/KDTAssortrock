#include <iostream>

void CreateCardBoard(int size,int Number[])
{
	// ������ ����
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			Number[i * size + j] = i * size + j + 1;
		}
	}
}

// ����
void Shuffle(int size, int Number[])
{
	for (int i = 0; i < size * size; i++)
	{
		int randomShuffle = rand() % (size * size);
		int temp = Number[i];
		Number[i] = Number[randomShuffle];
		Number[randomShuffle] = temp;
	}
}

void PrintCardBoard(int size, int Number[])
{
	// ī���� ���
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (Number[i * size + j] == INT_MAX)
			{
				std::cout << "*\t";
			}
			else
			{
				std::cout << Number[i * size + j] << "\t";
			}
		}

		std::cout << std::endl;
	}
}

int InputCardNumber(unsigned int selectNumber)
{
	std::cout << "��ȣ�� �������ּ��� (0 : ����) : ";
	std::cin >> selectNumber;			// ���� ����

	return selectNumber;
}

void NumberChecking(int size, int Number[], int selectNumber)
{
	// ī���ǿ��� ���ڰ� �ִ��� üũ�ϴ� ���
	for (int i = 0; i < size * size; i++)
	{
		// ���ڰ� ���� �ϴٸ� ����
		if (selectNumber == Number[i])
		{
			Number[i] = INT_MAX;
		}
	}
}

int BingoChecking(int lineCount)
{
	std::cout << lineCount << "����" << std::endl;

	return lineCount;
}

void GamePlay(int size, int Number[], int ComNumber[])
{
	unsigned int lineCount = 0;										// ���� ����
	unsigned int selectNumber = 0;									// ���ÿ� ����
	unsigned int horizontalCheckCount = 0;							// ���� üũ 
	unsigned int verticalCheckCount = 0;							// ���� üũ 

	// ���� ����
	while (true)
	{
		system("cls");

		PrintCardBoard(size, Number);							// ������ ���
		
		if (BingoChecking(lineCount) >= 5)
			break;

		PrintCardBoard(size, ComNumber);						// ��ǻ�Ϳ� ������ ���

		selectNumber = InputCardNumber(selectNumber);			// �Է¹�ȣ ��� �� ����

		// 0���� �Է��߰ų�, 5ĭ�̻� ���� �Ǿ��ٸ� ����
		if (selectNumber <= 0)
			break;

		NumberChecking(size, Number, selectNumber);				// �Է� ���� ��ȣ�� �����ϴ��� üũ

		lineCount = 0;

		// ���� ���� üũ���
		for (int i = 0; i < size; i++)
		{
			horizontalCheckCount = 0;
			verticalCheckCount = 0;

			// ���� ���� ī��Ʈ
			for (int j = 0; j < size; j++)
			{
				if (Number[i * size + j] == INT_MAX)
				{
					horizontalCheckCount++;
				}
				if (Number[j * size + i] == INT_MAX)
				{
					verticalCheckCount++;
				}
			}

			if (horizontalCheckCount == size)
			{
				lineCount++;
			}
			if (verticalCheckCount == size)
			{
				lineCount++;
			}
		}

		horizontalCheckCount = 0;

		// �밢�� üũ ��� (��)
		for (int i = 0; i < size * size; i += 6)
		{
			if (Number[i] == INT_MAX)
			{
				horizontalCheckCount++;
			}

			if (horizontalCheckCount == size)
			{
				lineCount++;
			}
		}

		horizontalCheckCount = 0;

		// �밢�� üũ ��� (��)
		for (int i = 4; i < 21; i += 4)
		{
			if (Number[i] == INT_MAX)
			{
				horizontalCheckCount++;
			}

			if (horizontalCheckCount == size)
			{
				lineCount++;
			}
		}

	}
}

int main()
{
	/*
		1. 5 x 5 �迭�� ī���� ����	(��)
		2. ���ڴ� 1 ~ 25�� ����		(��)
		3. ���� ��� �߰�				(��)
		4. ���� �Է� ����߰�			(��)
		5. 0�� �Է� ������ ���� ����	(��)
		6. ������ ���ڴ� *�� ���		(��)
		7. ���� �̹� *�� �ٲ� ���ڸ� �����Ѵٸ� while ���������� �̵�	(�ڵ����� ��)
		8. ���� 5�� ���� 5�� �밢�� 2���� ���� �� �ִ�.				(��)
		9. ���� ���� �߰�.										(��)
		10. ���� 5�� �̻��̸� ���� ����							(��)
	*/
	const int CARDBOARD_SIZE = 5;									// ī�� ���� ũ��
	int Number[CARDBOARD_SIZE * CARDBOARD_SIZE] = {};				// ������ ����
	int ComNumber[CARDBOARD_SIZE * CARDBOARD_SIZE] = {};				// ��ǻ�Ϳ� ������ ����

	system("cls");

	CreateCardBoard(CARDBOARD_SIZE, Number);					// ����� �´� ī�庸�� ����
	CreateCardBoard(CARDBOARD_SIZE, ComNumber);					// �� ��ǻ�Ϳ����� ����
	srand(time(0));												// �������

	Shuffle(CARDBOARD_SIZE, Number);							// ī�����
	Shuffle(CARDBOARD_SIZE, ComNumber);							// �� ��ǻ�Ϳ����� ī�����

	GamePlay(CARDBOARD_SIZE, Number, ComNumber);							// �÷��̾� ���ӽ���

	std::cout << "���� ����" << std::endl;
	return 0;
}
