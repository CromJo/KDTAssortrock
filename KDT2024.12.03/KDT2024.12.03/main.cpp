#include <iostream>
#include <time.h>

int main()
{
	/*
	if��			: ���� ���� �� Ư���� �ϳ��� ó���ϴ� ���
		if(����)
		{
			���� üũ �� true�� ���๮
		}
	switch��		: 
	*/

#pragma region ���ǹ�
	{
		int BossHP = 29;

		if (BossHP <= 30)
			std::cout << "�� Ʈ��� " << std::endl;
		else if (BossHP == 0)
			printf("�� ����̾� \n");
		else
			std::cout << "�� �����̾� " << std::endl;
	}
#pragma endregion

#pragma region ����
	{
		// �ּ� : 200 | �ִ� : 300
		// rand() % (�ִ� - �ּ� + 1) + �ּ�
		srand(time(0));
		std::cout << "���� : " << rand() << std::endl;
		std::cout << "Ư�� ���� ���� 100 ~ 200 : " << rand() % 101 + 100 << std::endl;
		std::cout << "�Ҽ��� ���� 2�ڸ��� : " << rand() % 10001 * 0.01f << std::endl;
	}
#pragma endregion

#pragma region if�� ��������
	/*
		1. ��ȭ��ġ�� �����ϴ� int ������ �ϳ� ����
		2. ��ȭ ��ġ�� 0 ~ 3 ���̸� 100% Ȯ���� ����
		3. 4 ~ 6 �ϰ�� 50% Ȯ���� ����
		4. 7 ~ 9 �ϰ�� 20% Ȯ���� ����
		5. 10 ~ 12 �ϰ�� 2% Ȯ���� ����
		6. 13 �̻��� ��� 0.7% Ȯ���� ����
	*/
	{
		int level = 13;

		std::cout << "���� ��ȭ ��ġ : " << level << std::endl;
		if (level <= 3)
		{
			level++;
		}
		else if (level <= 6)
		{
			if (rand() % 101 >= 50)
			{
				level++;
			}
			else
				std::cout << "��ȭ ����" << std::endl;
		}
		else if (level <= 9)
		{
			if (rand() % 101 >= 80)
				level++;
			else
				std::cout << "��ȭ ����" << std::endl;
		}
		else if (level <= 12)
		{
			if (rand() % 101 >= 98)
				level++;
			else
				std::cout << "��ȭ ����" << std::endl;
		}
		else
		{
			int a = 0;
			while (true)
			{
				float b = rand() % 10001 * 0.0 1f;

				if (b >= 99.3f)
				{
					std::cout << "�������� �� Ȯ�� : " << "\t Ȯ�� : " << b << std::endl;
					level++;
					break;
				}
				else
					std::cout << "��ȭ ���� ���� Ƚ�� : " << a++ << "\t Ȯ�� : " << b << std::endl;
			}

		}
		std::cout << "���� : " << level << std::endl;
	}
#pragma endregion
	return 0;
}