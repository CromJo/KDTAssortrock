
#include "Store.h"
#include "Inventory.h"

//FItem	gStoreWeapon[3];
//FItem	gStoreArmor[3];

// 포인터 타입을 2차원 배열로 선언하였다.
FItem* gStore[Item_End][3] = {};

FItem gOriginItem[2][3];

FItem* CreateItem(const char* Name, EItemType Type,
	int Option, int Buy, int Sell)
{
	FItem* Item = new FItem;

	strcpy_s(Item->Name, Name);
	Item->Type = Type;
	Item->Option = Option;
	Item->Buy = Buy;
	Item->Sell = Sell;

	return Item;
}

bool InitStore()
{
	FILE* File = nullptr;

	fopen_s(&File, "ItemList.lst", "rb");

	if (!File)
		return false;

	fread(gOriginItem, sizeof(FItem), 6, File);

	fclose(File);

	for (int i = 0; i < 3; i++)
	{
		gStore[Item_Weapon][i] = &gOriginItem[Item_Weapon][i];
		gStore[Item_Armor][i] = &gOriginItem[Item_Armor][i];
	}

	/*
	gStore[Item_Weapon][0] = CreateItem("목검",
		EItemType::Item_Weapon, 10, 1000, 500);
	gStore[Item_Weapon][1] = CreateItem("강철검",
		EItemType::Item_Weapon, 50, 12000, 6000);
	gStore[Item_Weapon][2] = CreateItem("검",
		EItemType::Item_Weapon, 100, 40000, 20000);

	gStore[Item_Armor][0] = CreateItem("천갑옷",
		EItemType::Item_Armor, 5, 1000, 500);
	gStore[Item_Armor][1] = CreateItem("가죽갑옷",
		EItemType::Item_Armor, 25, 12000, 6000);
	gStore[Item_Armor][2] = CreateItem("판금갑옷",
		EItemType::Item_Armor, 50, 40000, 20000);
	*/
	return true;
}

void DestroyStore()
{
	for (int i = 0; i < Item_End; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			delete gStore[i][j];
		}
	}
}

void RunStore(FPlayer* Player, EItemType Type)
{
	char	StoreName[32] = {};
	char	OptionName[32] = {};

	switch (Type)
	{
	case Item_Weapon:
		strcpy_s(StoreName, "무기");
		strcpy_s(OptionName, "공격력");
		break;
	case Item_Armor:
		strcpy_s(StoreName, "방어구");
		strcpy_s(OptionName, "방어력");
		break;
	}

	while (true)
	{
		system("cls");
		std::cout << "================== ";
		std::cout << StoreName << "상점";
		std::cout << " ==================" << std::endl;
		

		for (int i = 0; i < 3; ++i)
		{
			std::cout << i + 1 << ". " <<
				gStore[Type][i]->Name << std::endl;
			std::cout << "종류 : " << StoreName <<
				std::endl;
			std::cout << OptionName << " : " <<
				gStore[Type][i]->Option << std::endl;
			std::cout << "구매금액 : " <<
				gStore[Type][i]->Buy << std::endl;
			std::cout << "판매금액 : " <<
				gStore[Type][i]->Sell << std::endl;

			/*
			std::cout << i + 1 << ". " <<
				gStore[Type][i]->Name << std::endl;
			std::cout << "종류 : " << StoreName <<
				std::endl;
			std::cout << OptionName << " : " <<
				gStore[Type][i]->Option << std::endl;
			std::cout << "구매금액 : " <<
				gStore[Type][i]->Buy << std::endl;
			std::cout << "판매금액 : " <<
				gStore[Type][i]->Sell << std::endl;
			*/
		}

		std::cout << "4. 뒤로가기" << std::endl;
		std::cout << "소지금 : " <<
			Player->Gold << std::endl;
		std::cout << "아이템을 선택하세요 : ";
		int	Input;
		std::cin >> Input;

		if (4 == Input)
			return;

		else if (Input < 1 || Input > 4)
			continue;

		// 1 ~ 3번까지 선택.
		// 선택한 번호를 인덱스로 만들어준다.
		int	ItemIndex = Input - 1;

		// 1. 돈 부족할때
		// 2. 인벤토리에 자리 없을때
		if (gStore[Type][ItemIndex]->Buy >
			Player->Gold)
		{
			std::cout << "보유금액이 부족합니다." <<
				std::endl;
			system("pause");
			continue;
		}

		// 인벤토리에 자리가 없는지 판단한다.
		else if (gInventoryCount ==
			INVENTORY_MAX)
		{
			std::cout << "인벤토리 공간이 부족합니다." <<
				std::endl;
			system("pause");
			continue;
		}

		// 아이템을 구매한다.
		FItem* BuyItem = new FItem;

		// 1번인자의 주소로부터 2번인자의 크기만큼
		// 3번인자의 주소로부터 4번인자의 크기만큼을
		// 메모리 복사한다.
		memcpy_s(BuyItem, sizeof(FItem),
			gStore[Type][ItemIndex], sizeof(FItem));

		/*strcpy_s(BuyItem->Name, gStore[Type][ItemIndex]->Name);
		BuyItem->Type = gStore[Type][ItemIndex]->Type;
		BuyItem->Option = gStore[Type][ItemIndex]->Option;
		BuyItem->Buy = gStore[Type][ItemIndex]->Buy;
		BuyItem->Sell = gStore[Type][ItemIndex]->Sell;*/

		gInventory[gInventoryCount] = BuyItem;
		++gInventoryCount;

		Player->Gold -= BuyItem->Buy;

		system("pause");
	}
}
