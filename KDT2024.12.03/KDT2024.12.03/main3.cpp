#include <iostream>

int main()
{
	int Array[20] = {};
 
	// 1~10���� 2�徿 �����ؼ� 20���� �迭�ȿ� �߰�
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			Array[i * 10 + j] = j + 1;
		}
	}

	// ������ Ƚ�� �Է�
	int input;
	std::cout << "��� �����Ͻǰǰ���? : ";
	std::cin >> input;

	int shuffle = 0;
	// �迭�� ���ִ� ������ ���� ���ִ� ����� �����.
	// �迭�ȿ� �ִ� ���ڵ��� 100���� �Ǹ� while�� ����.

	// ���� ���ִ� ���
	// 1. �����ϰ� ���� 0�迭 ~ 19�迭����
	// 2. �����ϰ� ���õ� ���� temp�� ����
	// 3. 0������ ������� 
	// 4. �����ϰ� ������ ��ȣ�� temp���� �־��ֱ�
	// 5. -1�� ���� �ߴ��ϵ��� ��� �߰�.

	// ����
	while (shuffle < input)
	{
		shuffle++;
		srand(time(0));

		// �� �ȵƴ� ���� ���� ���ϰ� ����������ߴµ�,
		// �úη��� ����ϸ鼭 �����ؼ� �׷���
		// 
 		for (int i = 0; i < 20; i++)
		{
			int shf = rand() % 20;
			int temp = Array[i];
			Array[i] = Array[shf];
			Array[shf] = temp;
		}
	}
	
	int score = 0;		// ���� (2000�� �Ǹ� �¸�)
	// �������� ���ӽ���
	while (true)
	{
		system("cls");				// DOS ��ɾ� ���� �Լ� (cls : ȭ�� Ŭ����)

		if (score >= 2000)
		{
			std::cout << "���� �¸�!" << std::endl;
			break;
		}

		// ���
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				std::cout << Array[i * 10 + j] << "\t";
			}
			std::cout << std::endl;
		}


		unsigned int index[2] = {};
		int size = sizeof(index) / sizeof(int);
		
		// ī�� ���ö�
		for (int i = 0; i < size; i++)
		{
			std::cout << i + 1 <<"��° ī�带 ����ּ��� : ";
			std::cin >> index[i];

			// -1 �Է¹����� ���� ����
			if (index[i] == -1)
			{
				std::cout << "���� ����";
				return 0;
			}
		}

		if (Array[index[0]] == Array[index[1]])
		{
			if (Array[index[0]] != 100 || Array[index[1]] != 100)
			{
				Array[index[0]] = 100;
				Array[index[1]] = 100;

				score += 200;
				std::cout << "ī�尡 ��ġ�մϴ�!" << std::endl;
			}
			else
			{
				std::cout << "�̹� ������ϴ�!" << std::endl;
			}
			
		}
		else
		{
			std::cout << "ī�尡 ��ġ���� �ʽ��ϴ�." << std::endl;
		}
	}

	std::cout << "���� ��" << std::endl;
}
