#include "StoreManager.h"
#include "StoreWeapon.h"
#include "StoreArmor.h"

DEFINITION_SINGLE(CStoreManager)

bool CStoreManager::Init()
{
	mStoreList[0] = new CStoreWeapon;
	mStoreList[1] = new CStoreArmor;

	return true;
}
