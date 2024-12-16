#include "StoreArmor.h"

bool CStoreArmor::Init()
{
    for (int i = 0; i < 3; i++)
    {
        mItemList[i] = CObjectManager::GetInst()->GetObject(i);
    }

    return true;
}
