#pragma once

#include <iostream>

#define	SAFE_DELETE(p)	if(p) { delete p; p = nullptr; }

#define	LEVEL_MAX	10

enum class EJob
{
	None,
	Knight,
	Archer,
	Magicion,
	End
};

enum class EBattleType : unsigned char
{
	Easy,
	Normal,
	Hard,
	End
};

namespace EStoreType
{
	enum Type
	{
		Weapon,
		Armor,
		End
	};
}

namespace EItemType
{
	enum Type
	{
		Weapon,
		Armor,
		End
	};
}

namespace EEquip
{
	enum Type
	{
		Weapon,
		Armor,
		End
	};
}
