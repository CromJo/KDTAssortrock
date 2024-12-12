#include "StoreManager.h"
#include "Store.h"

EStoreMenu::Type CStoreManager::Menu()
{
	system("cls");
	std::cout << "1. ����" << std::endl;
	std::cout << "2. ����" << std::endl;
	std::cout << "3. ����" << std::endl;
	std::cout << "4. ����" << std::endl;
	std::cout << "�޴� ���� : ";

	int SelectMenu = 0;

	std::cin >> SelectMenu;

	// �߸��� �޴��� �������� ���
	if (SelectMenu <= EStoreMenu::None ||
		SelectMenu > EStoreMenu::Back)
		return EStoreMenu::None;

	return (EStoreMenu::Type)SelectMenu;
}

bool CStoreManager::Init()
{
	mStore[EStoreType::Weapon] = new CStore;
	mStore[EStoreType::Weapon]->Init(EStoreType::Weapon);
	mStore[EStoreType::Armor] = new CStore;
	mStore[EStoreType::Armor] = new CStore;

	return false;
}

void CStoreManager::Run()
{
	while (true)
	{
		switch (Menu())
		{
		case EStoreMenu::Weapon:
			mStore[EStoreType::Weapon]->Run();
			break;
		case EStoreMenu::Armor:
			mStore[EStoreType::Armor]->Run();
			break;
		case EStoreMenu::Back:
			return;
		}
	}
}
