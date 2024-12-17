#include "Store.h"
#include "Item.h"

CStore::CStore()
{
}

CStore::~CStore()
{
	if (nullptr != mItemList)
	{
		for (int i = 0; i < mItemCount; ++i)
		{
			// 동적할당된 아이템 객체가 배열의
			// 각 요소에 주소가 저장되어 있으므로
			// 반드시 제거해야 한다.
			delete mItemList[i];
		}

		delete[] mItemList;
	}
}

bool CStore::Init()
{
    return true;
}

bool CStore::LoadFromFile(const char* FileName)
{
	FILE* File = nullptr;

	fopen_s(&File, FileName, "rb");

	if (!File)
		return false;

	fread(&mItemCount, sizeof(int), 1, File);

	// 동적할당된 아이템의 주소를 저장하기 위한
	// 포인터 배열을 만들어준다.
	mItemList = new CObject*[mItemCount];

	for (int i = 0; i < mItemCount; ++i)
	{
		mItemList[i] = CreateItem();
		mItemList[i]->Init(File);
	}

	fclose(File);

    return true;
}

void CStore::Run()
{
}
