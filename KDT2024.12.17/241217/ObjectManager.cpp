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
	for (int i = 0; i < mObjectCount; ++i)
	{
		SAFE_DELETE(mObjectList[i]);
	}
}

bool CObjectManager::Init()
{
	mPlayer = new CPlayer;

	mPlayer->Init();

	mObjectList[0] = mPlayer;

	++mObjectCount;

	CreateMonsterList();

	CreateItemList();

	return true;
}

void CObjectManager::Output()
{
	for (int i = 0; i < mObjectCount; ++i)
	{
		mObjectList[i]->Output();
	}
}

CObject* CObjectManager::FindMonster(
	EBattleType Type)
{
	for (int i = 0; i < mObjectCount; ++i)
	{
		// 몬스터 클래스를 이용하여 생성된 객체가
		// 맞는지 확인하기 위해 dynamic_cast 를 
		// 이용하여 형변환을 진행한다.
		CMonster* Monster = 
			dynamic_cast<CMonster*>(mObjectList[i]);

		if (nullptr != Monster)
		{
			if (Monster->GetBattleType() == Type)
				return mObjectList[i];
		}
	}

	return nullptr;
}

void CObjectManager::CreateMonsterList()
{
	FILE* File = nullptr;

	fopen_s(&File, "MonsterList.mls", "rb");

	if (!File)
		return;

	int	MonsterCount = 0;
	fread(&MonsterCount, sizeof(int), 1, File);

	for (int i = 0; i < MonsterCount; ++i)
	{
		EBattleType	Type;
		fread(&Type, sizeof(EBattleType), 1,
			File);

		mObjectList[mObjectCount] = new CMonster;
		((CMonster*)mObjectList[mObjectCount])->SetBattleType(Type);
		mObjectList[mObjectCount]->Init(File);
		++mObjectCount;
	}

	fclose(File);

	/*mObjectList[mObjectCount] = new CMonster;
	mObjectList[mObjectCount]->Init();
	++mObjectCount;

	mObjectList[mObjectCount] = new CMonster;
	mObjectList[mObjectCount]->Init();
	++mObjectCount;

	mObjectList[mObjectCount] = new CMonster;
	mObjectList[mObjectCount]->Init();
	++mObjectCount;*/
}

void CObjectManager::CreateItemList()
{
	/*FILE* File = nullptr;

	fopen_s(&File, "WeaponStore.sto", "rb");

	if (!File)
		return;

	int	WeaponCount = 0;
	fread(&WeaponCount, sizeof(int), 1, File);

	for (int i = 0; i < WeaponCount; ++i)
	{
		mObjectList[mObjectCount] = new CItemWeapon;
		mObjectList[mObjectCount]->Init(File);
		++mObjectCount;
	}

	fclose(File);

	fopen_s(&File, "ArmorStore.sto", "rb");

	if (!File)
		return;

	int	ArmorCount = 0;
	fread(&ArmorCount, sizeof(int), 1, File);

	for (int i = 0; i < ArmorCount; ++i)
	{
		mObjectList[mObjectCount] = new CItemArmor;
		mObjectList[mObjectCount]->Init(File);
		++mObjectCount;
	}

	fclose(File);*/
}
