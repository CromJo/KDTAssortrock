#pragma once

#include "GameInfo.h"

class CStore abstract
{
	friend class CStoreManager;

protected:
	CStore();
	virtual ~CStore();

protected:
	// 일반 동적배열을 선언했을 경우 그 주소는
	// 포인터 변수에 저장이 가능하다.
	// 하지만 포인터 동적배열을 선언했을 경우
	// 그 주소는 이중포인터 변수에 저장이 가능하다.
	class CObject** mItemList = nullptr;
	int				mItemCount = 0;

public:
	virtual bool Init();
	bool LoadFromFile(const char* FileName);
	void Run();

protected:
	virtual CObject* CreateItem() = 0;
};

