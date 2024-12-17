#include "StoreWeapon.h"
#include "ObjectManager.h"
#include "ItemWeapon.h"

CStoreWeapon::CStoreWeapon()
{
}

CStoreWeapon::~CStoreWeapon()
{
}

bool CStoreWeapon::Init()
{
    LoadFromFile("WeaponStore.sto");

    /*for (int i = 0; i < 3; ++i)
    {
        mItemList[i] = CObjectManager::GetInst()->GetObject(4 + i);
    }*/

    return true;
}

CObject* CStoreWeapon::CreateItem()
{
    return new CItemWeapon;
}
