#include "GameManager.h"

/*
	����� �����.
	1. �÷��̾�� ó�� �׸� 1���� �����Ѵ�.
	2. Stage ������ �̿��Ͽ� ���� 15, ���� 15���� Stage�� ����� ��, ������, �÷��̾� ������ �����.
	3. �÷��̾�� ó�� ���� ��ġ�� �����Ǹ� �ڵ����� �� �������� ��� �̵��� �ϰ� �ȴ�.
	4. �̶� ����Ű�� �̿��Ͽ� �÷��̾�� ������ ������ �� �ִ�.
	5. ������ �����ϸ� �ش� �������� �̵��ϴ� ����̴�.
	6. �÷��̾�� ���� �ε����� �װԵǰ� ���� �޴��� �̵��Ѵ�.
	7. �������� ���� ��� �÷��̾��� �̵����� �ڿ� ������ 1�� �����Ǹ� ��� �������� �԰ԵǸ� �÷��̾ �¸��ϰ� �ȴ�.
*/


int main()
{
	if (!CGameManager::GetInst()->Init())
	{
		CGameManager::DestroyInst();
		return 0;
	}

	CGameManager::GetInst()->Run();

	CGameManager::DestroyInst();

	return 0;

}