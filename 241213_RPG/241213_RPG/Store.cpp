#include "Store.h"
#include "Item.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Inventory.h"

CStore::CStore()
{
}

CStore::~CStore()
{
}

bool CStore::Init(EStoreType::Type Type)
{
	mType = Type;

	switch (Type)
	{
	case EStoreType::Weapon:
		for (int i = 0; i < 3; ++i)
		{
			mItem[i] = 
				CObjectManager::GetInst()->GetItem(EItemType::Weapon, i);
		}
		break;
	case EStoreType::Armor:
		for (int i = 0; i < 3; ++i)
		{
			mItem[i] =
				CObjectManager::GetInst()->GetItem(EItemType::Armor, i);
		}
		break;
	}

	return true;
}

void CStore::Run()
{
	CPlayer* Player = 
		CObjectManager::GetInst()->GetPlayer();

	while (true)
	{
		system("cls");

		for (int i = 0; i < 3; ++i)
		{
			std::cout << i + 1 << ". ";
			mItem[i]->Output();
		}
		std::cout << "4. 뒤로가기" << std::endl;
		std::cout << "아이템을 선택하세요 : ";
		int	Input;
		std::cin >> Input;

		if (Input == 4)
			break;

		else if (Input < 1 || Input > 4)
			continue;

		int	Index = Input - 1;

		// 소지금이 부족한지 인벤토리에 공간이
		// 부족한지 체크한다.
		if (Player->GetGold() <
			mItem[Index]->GetBuy())
		{
			std::cout << "소지금이 부족합니다." <<
				std::endl;
			system("pause");
			continue;
		}

		else if (CInventory::GetInst()->IsFull())
		{
			std::cout << "인벤토리에 공간이 부족합니다." <<
				std::endl;
			system("pause");
			continue;
		}

		// 아이템 구매가 가능하다.
		CItem* Item = mItem[Index]->Clone();

		// 아이템의 금액만큼 플레이어의 돈을
		// 차감한다.
		Player->AddGold(-Item->GetBuy());

		CInventory::GetInst()->AddItem(Item);
	}
}
