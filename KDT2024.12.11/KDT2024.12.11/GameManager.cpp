#include "GameManager.h"

CGameManager* CGameManager::mInstance = nullptr;

CGameManager::CGameManager()
{

}

CGameManager::~CGameManager()
{
	SAFE_DELETE(mPlayer);		// 플레이어 제거
	SAFE_DELETE(mAI);
}

bool CGameManager::Init()
{
	srand(time(0));
	rand();

	// 플레이어 및 AI 생성
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
			std::cout << "인간찬가!" << std::endl;
			break;
		}
		
		if (mAI->GetLineCount() >= 5)
		{
			std::cout << "인간시대의 끝이 도래했다." << std::endl;
			break;
		}

		// 플레이어의 빙고 입력 기능
		int Input = 0;
		std::cout << "숫자를 입력하세요 (0 : 종료) : ";
		std::cin >> Input;
		

		// 0입력시 종료
		if (Input == 0)
			break;
		else if (Input < 0 || Input > 25)
			continue;

		// AI 짝맞추기 기능 추가.
		int AIInputCount = 25;
		int AIInput = 0;
		AIInput = (rand() % AIInputCount) + 1;
		std::cout << "AI가 선택한 번호 : " << Input << std::endl;

		for (int i = 0; i < AIInputCount; ++i)
		{
			if (mAI->mNumber[i] == Input)
			{
				// 현재 i번째 위치의 값과 배열의 사용할 수 있는
				// 부분 중 마지막 값을 바꾼다.
				mAI->mNumber[i] = mAI->mNumber[AIInputCount - 1];
				--AIInputCount;
				break;
			}
		}

		// 플레이어가 가지고 있는 숫자 중
		// 입력받은 숫자를 찾아서 *로 바꿔준다.
		if (mPlayer->ChangeNumber(Input))
			continue;

		if (mAI->ChangeNumber(Input))
			continue;

		if (mPlayer->ChangeNumber(AIInput))
			continue;

		if (mAI->ChangeNumber(AIInput))
			continue;
		
		// 플레이어의 줄이 몇 줄인지를 체크한다.
		mPlayer->CheckLine();
		mAI->CheckLine();
	}
}
