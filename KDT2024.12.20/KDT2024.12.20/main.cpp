
#include "GameManager.h"

int main()
{
	/*int Key = _getch();

	std::cout << Key << std::endl;

	Key = _getch();

	std::cout << Key << std::endl;

	return 0;*/


	/*int	Array[10];

	// 1�����ڿ� ���� �޸� �ּҷκ���
	// 3�����ڿ� ���� �޸� ũ�⸸ŭ��
	// 2�����ڿ� ���� ������ ä���ش�.
	// memset�� ���� ä�� �� 1����Ʈ ������ ����
	// ä���ش�.
	// 0000 0001 0000 0001 0000 0001 0000 0001
	memset(Array, 2, sizeof(int) * 10);

	for (int i = 0; i < 10; ++i)
	{
		std::cout << Array[i] << std::endl;
	}

	return 0;*/

	if (!CGameManager::GetInst()->Init())
	{
		CGameManager::DestroyInst();
		return 0;
	}

	CGameManager::GetInst()->Run();

	CGameManager::DestroyInst();

	return 0;
}
