#include "StoreArmor.h"
#include "ObjectManager.h"
#include "ItemArmor.h"

CStoreArmor::CStoreArmor()
{
}

CStoreArmor::~CStoreArmor()
{
}

bool CStoreArmor::Init()
{
    LoadFromFile("ArmorStore.sto");

    return true;
}

CObject* CStoreArmor::CreateItem()
{
    return new CItemArmor;
}
