#include "Battle.h"

bool InitBattle()
{
	FMonster Monster;

	if (!MonsterInit(&Monster))
		return false;


	// ���� �ʱ�ȭ�� �����ϸ� ���� ���� ����.
	std::cout << "���� �̸� : " << Monster.Name << std::endl;
	std::cout << "���� ü�� : " << Monster.HP << std::endl;
	std::cout << "���� ���ݷ� : " << Monster.Attack << std::endl;
	std::cout << "���� ���� : " << Monster.Defense << std::endl;

	return true;
}

EMode BattleMenu()
{
	system("cls");
	std::cout << "1. ����" << std::endl;
	std::cout << "2. ����" << std::endl;
	std::cout << "3. �����" << std::endl;
	std::cout << "4. �ڷΰ���" << std::endl;
	std::cout << "�޴� ���� : ";

	int SelectLevel = 0;

	std::cin >> SelectLevel;

	if (SelectLevel <= EMode::None || SelectLevel > EMode::Back)
		return EMode::None;

	// ���������� ������ �ߴٸ�,
	return (EMode)SelectLevel;
}

/*
	1. ���� ����, ���� ����� ���� ���� �ɷ�ġ�� �ٸ��� ����.
	2. �÷��̾ ���� ������ �ϸ� �÷��̾� ���ݷ� - ���� ���� ��ŭ ���� ü�� ����.
	3. �̶�, �÷��̾��� ���ݷº��� ������ ������ ���ٸ� - ���� �����Ƿ�, �� ��� �ּ� ����� 1�� ������ �Ѵ�.
*/

bool MonsterInit(FMonster* Monster)
{
	srand(time(0));

	EMode Level = BattleMenu();
	switch (Level)
	{
	case Easy:
		strcpy_s(Monster->Name, "������");		// �̸� ����
		Monster->Attack = 10;					// ���ݷ� ����
		Monster->Defense = 2;					// ���� ����
		Monster->HPMax = 100;						// �ִ� ü�� ����
		Monster->HP = Monster->HPMax;						// ü�� ����
		Monster->Gold = rand() % 100;	// ���̵��� ���� ��� �ݾ� ����
		break;
	case Normal:
		strcpy_s(Monster->Name, "���");		// �̸� ����
		Monster->Attack = 15;					// ���ݷ� ����
		Monster->Defense = 5;					// ���� ����
		Monster->HPMax = 120;						// �ִ� ü�� ����
		Monster->HP = Monster->HPMax;						// ü�� ����
		Monster->Gold = rand() % 125;	// ���̵��� ���� ��� �ݾ� ����

		break;
	case Hard:
		strcpy_s(Monster->Name, "��ũ");		// �̸� ����
		Monster->Attack = 30;					// ���ݷ� ����
		Monster->Defense = 10;					// ���� ����
		Monster->HPMax = 200;						// �ִ� ü�� ����
		Monster->HP = Monster->HPMax;						// ü�� ����
		Monster->Gold = rand() % 180;	// ���̵��� ���� ��� �ݾ� ����
		break;
	case Back:
		break;
	}
	
	return true;
}

/// <summary>
/// ��Ʋ ����� ������ �Լ�
/// ����� ��Ʋ�� �����մϴ�.
/// </summary>
void RunBattle()
{
	while (true)
	{
		switch (BattleMenu())
		{

		case Easy:
			InitBattle();

			break;
		case Normal:
			break;
		case Hard:
			break;
		case Back:
			break;
		default:
			return;
		}
	}
}