#pragma once
#include "GameInfo.h"

class CObjectManager
{
private:
	std::list<class CObject*> mObjectList;

public:
	bool Init();
	void Update(float DeltaTime);
	void Output(char* OutputBuffer);

	template <typename T>
	T* CreateObj()
	{
		T* Obj = new T;

		if (!Obj->Init())
		{
			SAFE_DELETE(Obj);

			return nullptr;
		}

		mObjectList.emplace_back(Obj);

		return Obj;
	}

	DECLARE_SINGLE(CObjectManager)
};

