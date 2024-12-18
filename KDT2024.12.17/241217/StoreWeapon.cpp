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

    return true;
}

CObject* CStoreWeapon::CreateItem()
{
    return new CItemWeapon;
}
