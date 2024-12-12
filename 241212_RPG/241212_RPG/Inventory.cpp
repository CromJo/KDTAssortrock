#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "ObjectManager.h"

CInventory* CInventory::mInst = nullptr;

CInventory::CInventory()
{
}

CInventory::~CInventory()
{
}

bool CInventory::Init()
{
	return true;
}

void CInventory::Run()
{
	CItem* Item = CObjectManager::GetInst()->GetPlayer();
	
	while (true)
	{
		system("cls");

		int inventorySize = sizeof(GetInventoryItem()) / sizeof(int);
		for (int i = 0; i < inventorySize; i++)
		{
			std::cout << i + 1 << ". ";
			Item[i]->Output();
		}
		std::cout << "4. 뒤로가기" << std::endl;
		std::cout << "아이템을 선택하세요 : ";

		int Input;
		std::cin >> Input;

		if (Input == 4)
			break;
		else if (Input < 1 || Input > 4)
			continue;
	}

}

void CInventory::Output()
{
	std::cout << "이름 : " << mName << std::endl;

	switch (mItemType)
	{
	case EItemType::Weapon:
		std::cout << "종류 : 무기" << std::endl;
		std::cout << "공격력 : " << mOption << std::endl;
		break;
	case EItemType::Armor:
		std::cout << "종류 : 방어구" << std::endl;
		std::cout << "방어력 : " << mOption << std::endl;
		break;
	}

	std::cout << "판매금액 : " << mSell << std::endl;
}
