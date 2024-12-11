#include "GameManager.h"

int main()
{
	if (!CGameManager::GetInstance()->Init())
	{
		// �ʱ�ȭ ���н� ������ ��ü�� ���� �� ����
		CGameManager::DestroyInstance();
		
		return 0;
	}

	CGameManager::GetInstance()->Run();

	// ������ ������ �޸𸮸� �����Ѵ�.
	CGameManager::DestroyInstance();

	return 0;
}