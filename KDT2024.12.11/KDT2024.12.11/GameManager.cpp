#include "GameManager.h"

CGameManager* CGameManager::mInstance = nullptr;

CGameManager::CGameManager()
{

}

CGameManager::~CGameManager()
{
	SAFE_DELETE(mPlayer);		// �÷��̾� ����
	SAFE_DELETE(mAI);
}

bool CGameManager::Init()
{
	srand(time(0));
	rand();

	// �÷��̾� �� AI ����
	mPlayer = new CPlayer;
	mAI = new CAI;

	if (!mAI->Init())
		return false;

	if (!mPlayer->Init())
		return false;

	return true;
}

void CGameManager::Run()
{
	while (true)
	{
		system("cls");
		mAI->Output();
		std::cout << "Line : " << mAI->GetLineCount() << std::endl;

		mPlayer->Output();
		std::cout << "Line : " << mPlayer->GetLineCount() << std::endl;

		if (mPlayer->GetLineCount() >= 5)
		{
			std::cout << "�ΰ�����!" << std::endl;
			break;
		}
		
		if (mAI->GetLineCount() >= 5)
		{
			std::cout << "�ΰ��ô��� ���� �����ߴ�." << std::endl;
			break;
		}

		// �÷��̾��� ���� �Է� ���
		int Input = 0;
		std::cout << "���ڸ� �Է��ϼ��� (0 : ����) : ";
		std::cin >> Input;
		

		// 0�Է½� ����
		if (Input == 0)
			break;
		else if (Input < 0 || Input > 25)
			continue;

		// AI ¦���߱� ��� �߰�.
		int AIInputCount = 25;
		int AIInput = 0;
		AIInput = (rand() % AIInputCount) + 1;
		std::cout << "AI�� ������ ��ȣ : " << Input << std::endl;

		for (int i = 0; i < AIInputCount; ++i)
		{
			if (mAI->mNumber[i] == Input)
			{
				// ���� i��° ��ġ�� ���� �迭�� ����� �� �ִ�
				// �κ� �� ������ ���� �ٲ۴�.
				mAI->mNumber[i] = mAI->mNumber[AIInputCount - 1];
				--AIInputCount;
				break;
			}
		}

		// �÷��̾ ������ �ִ� ���� ��
		// �Է¹��� ���ڸ� ã�Ƽ� *�� �ٲ��ش�.
		if (mPlayer->ChangeNumber(Input))
			continue;

		if (mAI->ChangeNumber(Input))
			continue;

		if (mPlayer->ChangeNumber(AIInput))
			continue;

		if (mAI->ChangeNumber(AIInput))
			continue;
		
		// �÷��̾��� ���� �� �������� üũ�Ѵ�.
		mPlayer->CheckLine();
		mAI->CheckLine();
	}
}
