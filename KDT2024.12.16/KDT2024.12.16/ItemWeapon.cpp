#include "ItemWeapon.h"

CItemWeapon::CItemWeapon()
{
}

CItemWeapon::CItemWeapon(const CItemWeapon& Obj) : CItem(Obj)
{
}

CItemWeapon::~CItemWeapon()
{
}

bool CItemWeapon::Init()
{
	return true;
}

bool CItemWeapon::Init(FILE* File)
{
	return true;
}

void CItemWeapon::Output()
{
	CObject::Output();
	std::cout << "���� : ���� " << std::endl;
	std::cout << "���ݷ� :  " << mOption << std::endl;

	CItem::Output();
}

CItemWeapon* CItemWeapon::Clone()
{
	return new CItemWeapon(*this);
}
