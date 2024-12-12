#include "ObjectManager.h"
#include "Item.h"

CObjectManager* CObjectManager::mInst = nullptr;

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
	for (int i = 0; i < 3; ++i)
	{
		SAFE_DELETE(mMonster[i]);
	}

	for (int i = 0; i < EItemType::End; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			SAFE_DELETE(mItem[i][j]);
		}
	}

	SAFE_DELETE(mPlayer);
}

bool CObjectManager::Init()
{
	mPlayer = new CPlayer;

	if (false == mPlayer->Init())
		return false;

	if (false == LoadMonster())
		return false;

	if (false == LoadItem())
		return false;

	return true;
}

CMonster* CObjectManager::CreateMonster(EBattleType Type)
{
	return mMonster[(int)Type]->Clone();
}

bool CObjectManager::LoadMonster()
{
	FILE* File = nullptr;

	fopen_s(&File, "MonsterList.lst", "rb");

	if (!File)
		return false;

	for (int i = 0; i < 3; ++i)
	{
		// 몬스터 객체를 생성한다.
		mMonster[i] = new CMonster;

		mMonster[i]->Init(File);
	}

	fclose(File);

	return true;
}

bool CObjectManager::LoadItem()
{
	FILE* File = nullptr;

	fopen_s(&File, "WeaponStore.sto", "rb");

	if (!File)
		return false;

	int Count = 0;

	fread(&Count, sizeof(int), 1, File);

	for (int i = 0; i < Count; i++)
	{
		CItem* Item = new CItem;

		Item->Init(File);

		mItem[EItemType::Weapon][i] = Item;
	}

	fclose(File);

	fopen_s(&File, "ArmorStore.sto", "rb");

	if (!File)
		return false;

	fread(&Count, sizeof(int), 1, File);

	for (int i = 0; i < Count; ++i)
	{
		CItem* Item = new CItem;

		Item->Init(File);

		mItem[EItemType::Armor][i] = Item;
	}

	fclose(File);

	return true;
}
