#include "Item.h"

CItem::CItem()
{
}

CItem::CItem(const CItem& Obj) :
    CObject(Obj)
{
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
    CItem::Init(File);
    fread(&mType, sizeof(EItemType::Armor), 1, File);

    return true;
}

void CItem::Output()
{
    CObject::Output();

    std::cout << "구매 금액 : " << mBuy << std::endl;
    std::cout << "판매 금액 : " << mSell << std::endl;
}

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
