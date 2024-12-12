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
		std::cout << "4. �ڷΰ���" << std::endl;
		std::cout << "�������� �����ϼ��� : ";

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
	std::cout << "�̸� : " << mName << std::endl;

	switch (mItemType)
	{
	case EItemType::Weapon:
		std::cout << "���� : ����" << std::endl;
		std::cout << "���ݷ� : " << mOption << std::endl;
		break;
	case EItemType::Armor:
		std::cout << "���� : ��" << std::endl;
		std::cout << "���� : " << mOption << std::endl;
		break;
	}

	std::cout << "�Ǹűݾ� : " << mSell << std::endl;
}
