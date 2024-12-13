#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "ObjectManager.h"

namespace EInventoryMenu
{
	enum Type
	{
		None,
		Equip,
		Sell,
		Back
	};
}

CInventory* CInventory::mInst = nullptr;

CInventory::CInventory()
{
}

CInventory::~CInventory()
{
	for (int i = 0; i < mCount; ++i)
	{
		SAFE_DELETE(mItem[i]);
	}
}

void CInventory::AddItem(CItem* Item)
{
	mItem[mCount] = Item;
	++mCount;
}

void CInventory::Run()
{
	CPlayer* Player = 
		CObjectManager::GetInst()->GetPlayer();

	while (true)
	{
		system("cls");
		for (int i = 0; i < mCount; ++i)
		{
			std::cout << i + 1 << " .";
			mItem[i]->Output();
		}

		std::cout << mCount + 1 << ". 뒤로가기" <<
			std::endl;

		// 장착아이템 출력
		std::cout << "장착무기 : ";
		CItem* Equip = Player->GetEquipItem(EEquip::Weapon);

		if (Equip)
			std::cout << Equip->GetName();

		else
			std::cout << "없음";

		std::cout << "\t장착방어구 : ";

		Equip = Player->GetEquipItem(EEquip::Armor);

		if (Equip)
			std::cout << Equip->GetName() << std::endl;

		else
			std::cout << "없음" << std::endl;


		std::cout << "아이템을 선택하세요 : ";
		int	Input;
		std::cin >> Input;

		if (Input == mCount + 1)
			return;

		else if (Input < 1 || Input > mCount + 1)
			continue;

		std::cout << "1. 장착" << std::endl;
		std::cout << "2. 판매" << std::endl;
		std::cout << "3. 다시선택" << std::endl;
		std::cout << "메뉴를 선택하세요 : ";
		int	InvenMenu = 0;

		std::cin >> InvenMenu;

		if (InvenMenu >= EInventoryMenu::Back ||
			InvenMenu <= EInventoryMenu::None)
			continue;

		int	Index = Input - 1;

		switch (InvenMenu)
		{
		case EInventoryMenu::Equip:
			EquipFunction(Player, Index);
			break;
		case EInventoryMenu::Sell:
			ItemSell(Player, Index);
			break;
		}
	}
}

void CInventory::EquipFunction(CPlayer* Player,
	int Index)
{
	CItem* EquipItem = Player->Equip(mItem[Index]);

	if (nullptr == EquipItem)
	{
		mItem[Index] = mItem[mCount - 1];
		mItem[mCount - 1] = nullptr;
		--mCount;
	}

	else
	{
		mItem[Index] = EquipItem;
	}
}

void CInventory::ItemSell(CPlayer* Player, 
	int Index)
{
	Player->AddGold(mItem[Index]->GetSell());
	
	CItem* DeleteItem = mItem[Index];

	if (mCount >= 2)
	{
		mItem[Index] = mItem[mCount - 1];
		mItem[mCount - 1] = nullptr;
	}

	else
		mItem[Index] = nullptr;

	--mCount;

	delete DeleteItem;
}
