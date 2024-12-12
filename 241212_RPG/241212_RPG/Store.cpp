#include "Store.h"
#include "Item.h"
#include "ObjectManager.h"

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
	while (true)
	{
		system("cls");

		for (int i = 0; i < 3; i++)
		{
			std::cout << i + 1 << ". ";
			mItem[i]->Output();
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
