#include "GameManager.h"
#include "ObjectManager.h"
#include "StoreManager.h"

CGameManager* CGameManager::mInst = nullptr;

CGameManager::CGameManager()
{

}

CGameManager::~CGameManager()
{
	// 오브젝트 관리자 제거
	CObjectManager::DestroyInst();

	SAFE_DELETE(mBattleMgr);
	SAFE_DELETE(mStoreMgr);
}

bool CGameManager::Init()
{
	// 전투관리자 생성
	mBattleMgr = new CBattleManager;

	if (false == mBattleMgr->Init())
		return false;

	// 오브젝트 관리자 초기화
	if (false == CObjectManager::GetInst()->Init())
		return false;

	mStoreMgr = new CStoreManager;

	if (false == mStoreMgr->Init())
		return false;


	return true;
}

EMainMenu::Type CGameManager::Menu()
{
	system("cls");
	std::cout << "1. 전투" << std::endl;
	std::cout << "2. 상점" << std::endl;
	std::cout << "3. 가방" << std::endl;
	std::cout << "4. 종료" << std::endl;
	std::cout << "메뉴 선택 : ";

	int SelectMenu = 0;

	std::cin >> SelectMenu;

	// 잘못된 메뉴를 선택했을 경우
	if (SelectMenu <= EMainMenu::None ||
		SelectMenu > EMainMenu::Exit)
		return EMainMenu::None;

	return (EMainMenu::Type)SelectMenu;
}

void CGameManager::Run()
{
	while (true)
	{
		switch (Menu())
		{
		case EMainMenu::Battle:
			mBattleMgr->Run();
			break;
		case EMainMenu::Store:
			mStoreMgr->Run();
			break;
		case EMainMenu::Inventory:
			break;
		case EMainMenu::Exit:
			return;
		}
	}
}
