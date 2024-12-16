#pragma once
#include "GameInfo.h"

class CStoreManager
{
private:
	class CStore* mStoreList[2];

public:
	virtual bool Init();
	virtual void Run();

};

