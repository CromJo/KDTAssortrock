
#include "ItemWeapon.h"
#include "ItemArmor.h"

enum class EMenu
{
	None,
	ItemAdd,
	ItemDelete,
	ItemOutput,
	ItemSave,
	ItemLoad,
	Exit
};

CItem** gItemList;

// 실제 추가된 아이템 수
int		gItemCount = 0;

// 실제 할당된 배열의 수
int		gItemCapacity = 4;


void AddItem()
{
	// 현재 배열이 꽉 찼는지 판단한다.
	if (gItemCount == gItemCapacity)
	{
		// 새로운 배열을 전체 배열 수의 2배만큼
		// 할당해준다.
		gItemCapacity *= 2;
		CItem** Array = new CItem*[gItemCapacity];

		// 원래 있던 배열에서 데이터를 옮겨준다.
		for (int i = 0; i < gItemCount; ++i)
		{
			Array[i] = gItemList[i];
		}

		// 원래 배열을 제거한다.
		delete[] gItemList;

		// 새로운 배열의 주소를 저장한다.
		gItemList = Array;
	}

	EItemType	ItemType;

	while (true)
	{
		system("cls");
		// 무기, 방어구 둘중 어떤것을 생성할지 선택
		std::cout << "1. 무기" << std::endl;
		std::cout << "2. 방어구" << std::endl;
		std::cout << "선택 : ";
		int	Input;
		std::cin >> Input;

		if (Input < 1 || Input > 2)
			continue;

		ItemType = (EItemType)(Input - 1);
		break;
	}

	switch (ItemType)
	{
	case EItemType::Weapon:
		gItemList[gItemCount] = new CItemWeapon;
		break;
	case EItemType::Armor:
		gItemList[gItemCount] = new CItemArmor;
		break;
	}

	gItemList[gItemCount]->Init();
	++gItemCount;
}

void DeleteItem()
{
}

void OutputItem()
{
	system("cls");
	for (int i = 0; i < gItemCount; ++i)
	{
		gItemList[i]->Output();
	}

	system("pause");
}

void SaveItem()
{
}

void LoadItem()
{
}

int main()
{
	// 처음에 배열을 4개 할당한다.
	gItemList = new CItem*[gItemCapacity];

	while (true)
	{
		system("cls");
		std::cout << "1. 아이템추가" << std::endl;
		std::cout << "2. 아이템삭제" << std::endl;
		std::cout << "3. 아이템출력" << std::endl;
		std::cout << "4. 아이템저장" << std::endl;
		std::cout << "5. 아이템불러오기" << std::endl;
		std::cout << "6. 종료" << std::endl;
		std::cout << "메뉴를 선택하세요 : ";
		int	Input;
		std::cin >> Input;

		if (Input == (int)EMenu::Exit)
			break;

		else if (Input <= (int)EMenu::None ||
			Input > (int)EMenu::Exit)
			continue;

		switch ((EMenu)Input)
		{
		case EMenu::ItemAdd:
			AddItem();
			break;
		case EMenu::ItemDelete:
			DeleteItem();
			break;
		case EMenu::ItemOutput:
			OutputItem();
			break;
		case EMenu::ItemSave:
			SaveItem();
			break;
		case EMenu::ItemLoad:
			LoadItem();
			break;
		}
	}

	for (int i = 0; i < gItemCount; ++i)
	{
		delete gItemList[i];
	}
	delete[] gItemList;

	return 0;
}
