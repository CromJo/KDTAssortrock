#include "Item.h"

CItem::CItem()
{
}

CItem::CItem(const CItem& Obj)  :
    CObject(Obj)
{
    mType = Obj.mType;
}

CItem::~CItem()
{
}

bool CItem::Init()
{
    CObject::Init();

    return true;
}

bool CItem::Init(FILE* File)
{
    CObject::Init(File);

    fread(&mType, sizeof(EItemType), 1, File);
    fread(&mOption, sizeof(int), 1, File);
    fread(&mBuy, sizeof(int), 1, File);
    fread(&mSell, sizeof(int), 1, File);



    return true;
}

void CItem::Output()
{
    std::cout << "구매금액 : " << mBuy <<
        std::endl;
    std::cout << "판매금액 : " << mSell <<
        std::endl;
}

void CItem::OverrideTest()
{
}

//void CItem::OverrideTest(int Number)
//{
//}

void CItem::VirtualPure()
{
}

void CItem::VirtualPure1()
{
}

void CItem::VirtualPure2()
{
}

void CItem::VirtualPure3()
{
}

CItem* CItem::Clone()
{
    return new CItem(*this);
}
