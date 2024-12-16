#include "ObjectManager.h"
#include "Player.h"
#include "Monster.h"
#include "ItemWeapon.h"
#include "ItemArmor.h"

DEFINITION_SINGLE(CObjectManager)

CObjectManager::CObjectManager()
{

}

CObjectManager::~CObjectManager()
{

}

bool CObjectManager::Init()
{
	mPlayer = new CPlayer;
	mPlayer->Init();
	mObjectList[0] = mPlayer;
	mObjectCount++;

	return true;
}

void CObjectManager::Output()
{
	for (int i = 0; i < mObjectCount; i++)
	{
		mObjectList[i]->Output();
	}
}

void CObjectManager::Run()
{
}

void CObjectManager::CreateMonsterList()
{
	mObjectList[mObjectCount] = new CMonster();
	mObjectList[mObjectCount]->Init();
	mObjectCount++;

	mObjectList[mObjectCount] = new CMonster();
	mObjectList[mObjectCount]->Init();
	mObjectCount++;
	
	mObjectList[mObjectCount] = new CMonster();
	mObjectList[mObjectCount]->Init();
	mObjectCount++;
}

void CObjectManager::CreateItemList()
{
	FILE* File = nullptr;

	fopen_s(&File, "WeaponStore,sto", "rb");

	if (!File)
		return;

	int WeaponCount = 0;
	fread(&WeaponCount, sizeof(int), 1, File);

	for (int i = 0; i < WeaponCount; i++)
	{

		mObjectList[mObjectCount] = new CItemWeapon;
		mObjectList[mObjectCount]->Init(File);
		mObjectCount++;
	}

	mObjectList[mObjectCount] = new CItem();
	mObjectList[mObjectCount]->Init();
	mObjectCount++;

	mObjectList[mObjectCount] = new CItem();
	mObjectList[mObjectCount]->Init();
	mObjectCount++;

	mObjectList[mObjectCount] = new CItem();
	mObjectList[mObjectCount]->Init();
	mObjectCount++;

	mObjectList[mObjectCount] = new CItem();
	mObjectList[mObjectCount]->Init();
	mObjectCount++;
}
