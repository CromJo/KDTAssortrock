#include "Battle.h"

/// <summary>
/// ������ ���̵� State
/// </summary>
enum EMode
{
	None = 0,
	Easy,
	Normal,
	Hard,
	Back
};

bool InitBattle()
{
	// ���� ��ȭ�� ���õ� �ڵ带 �ۼ��Ѵ�.


	return true;
}

EMode BattleMenu()
{
	system("cls");
	std::cout << "1. ����" << std::endl;
	std::cout << "2. ����" << std::endl;
	std::cout << "3. ����" << std::endl;
	std::cout << "4. ����" << std::endl;
	std::cout << "�޴� ���� : " << std::endl;

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