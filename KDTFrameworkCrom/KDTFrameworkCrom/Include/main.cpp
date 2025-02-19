#include "GameManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	// �޸𸮸� üũ ���
	// Debug ��忡���� ����
	// ��� â���� Ȯ�ΰ���
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// "�Ű�����1"��ȣ�� �޸𸮸��� ����ִ� �Լ�.
	// ȣ�⽺�ÿ��� Ȯ�ΰ���
	// ȣ�⽺�ÿ��� ���� ���� ����� ã�Ƽ� 
	//	������ �ذ��ϸ� �ȴ�.
	// �� �ʿ��Ҷ� �ּ��� �����ؼ� �Ű������� �´�,
	//	�޸𸮸��� ã�Ƽ� �ذ��ϸ� �ȴ�.
	//_CrtSetBreakAlloc(211);

	if (!CGameManager::GetInstance()->Init(hInstance))
	{
		CGameManager::DestroyInstance();

		return 0;
	} 

	int Ret = CGameManager::GetInstance()->Run();

	CGameManager::DestroyInstance();

	return Ret;
}