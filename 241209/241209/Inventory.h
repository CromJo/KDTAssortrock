#pragma once

#include "GameInfo.h"

extern FItem* gInventory[INVENTORY_MAX];
extern int gInventoryCount;
//static int gTestStatic = 300;

bool InitInventory();
void DestroyInventory();
void RunInventory(FPlayer* Player);