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
    /*for (int i = 0; i < 3; ++i)
    {
        mItemList[i] = CObjectManager::GetInst()->GetObject(7 + i);
    }*/

    return true;
}

CObject* CStoreArmor::CreateItem()
{
    return new CItemArmor;
}
