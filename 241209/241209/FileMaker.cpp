#include "GameInfo.h"

void MonsterFileCreate()
{
	FMonster Monster[3] = {};

	strcpy_s(Monster[0].Name, "°íºí¸°");
	Monster[0].Attack = 30;
	Monster[0].Defense = 10;
	Monster[0].HP = 100;
	Monster[0].HPMax = 100;
	Monster[0].MP = 10;
	Monster[0].MPMax = 10;
	Monster[0].Level = 1;
	Monster[0].Exp = 1000;
	Monster[0].Gold = 1000;

	strcpy_s(Monster[1].Name, "¿ÀÅ©");
	Monster[1].Attack = 70;
	Monster[1].Defense = 40;
	Monster[1].HP = 600;
	Monster[1].HPMax = 600;
	Monster[1].MP = 100;
	Monster[1].MPMax = 100;
	Monster[1].Level = 5;
	Monster[1].Exp = 5000;
	Monster[1].Gold = 5000;

	strcpy_s(Monster[2].Name, "µå·¡°ï");
	Monster[2].Attack = 200;
	Monster[2].Defense = 150;
	Monster[2].HP = 2000;
	Monster[2].HPMax = 2000;
	Monster[2].MP = 1000;
	Monster[2].MPMax = 1000;
	Monster[2].Level = 10;
	Monster[2].Exp = 10000;
	Monster[2].Gold = 10000;
}

void PlayerFileCreate()
{
	FPlayer Player[3] = {};

	Player[0].Attack = 40;
	Player[0].Defense = 20;
	Player[0].HP = 500;
	Player[0].HPMax = 500;
	Player[0].MP = 100;
	Player[0].MPMax = 100;
	Player[0].Level = 0;
	Player[0].Exp = 0;
	Player[0].Gold = 0;

	Player[1].Attack = 50;
	Player[1].Defense = 15;
	Player[1].HP = 400;
	Player[1].HPMax = 400;
	Player[1].MP = 200;
	Player[1].MPMax = 200;
	Player[1].Level = 0;
	Player[1].Exp = 0;
	Player[1].Gold = 0;

	Player[2].Attack = 60;
	Player[2].Defense = 10;
	Player[2].HP = 300;
	Player[2].HPMax = 300;
	Player[2].MP = 300;
	Player[2].MPMax = 300;
	Player[2].Level = 0;
	Player[2].Exp = 0;
	Player[2].Gold = 0;

	/*
	FPlayerF`ileInfo FileInfo[3] = {};
	
	fread(FileInfo, sizeof(FPlayerFileInfo), 3, FileInfo);
	*/
}

struct FPlayerFileInfo
{
	int Attack;
	int Defense;
	int HP;
	int MP;
};

int main()
{
	FItem Item[2][3] = {};

	strcpy_s(Item[0][0].Name, "¸ñ°Ë");
	Item[0][0].Type = EItemType::Item_Weapon;
	Item[0][0].Option = 10;
	Item[0][0].Buy = 1000;
	Item[0][0].Sell = 500;
	
	strcpy_s(Item[0][1].Name, "°­Ã¶°Ë");
	Item[0][1].Type = EItemType::Item_Weapon;
	Item[0][1].Option = 50;
	Item[0][1].Buy = 12000;
	Item[0][1].Sell = 6000;

	strcpy_s(Item[0][2].Name, "°Ë");
	Item[0][2].Type = EItemType::Item_Weapon;
	Item[0][2].Option = 100;
	Item[0][2].Buy = 40000;
	Item[0][2].Sell = 20000;

	strcpy_s(Item[1][0].Name, "Ãµ°©¿Ê");
	Item[1][0].Type = EItemType::Item_Armor;
	Item[1][0].Option = 5;
	Item[1][0].Buy = 1000;
	Item[1][0].Sell = 500;

	strcpy_s(Item[1][1].Name, "°¡Á×°©¿Ê");
	Item[1][1].Type = EItemType::Item_Armor;
	Item[1][1].Option = 25;
	Item[1][1].Buy = 12000;
	Item[1][1].Sell = 6000;

	strcpy_s(Item[1][2].Name, "ÆÇ±Ý°©¿Ê");
	Item[1][2].Type = EItemType::Item_Armor;
	Item[1][2].Option = 50;
	Item[1][2].Buy = 40000;
	Item[1][2].Sell = 20000;

	FILE* File = nullptr;

	fopen_s(&File, "ItemList.lst", "wb");

	if (File)
	{
		fwrite(Item, sizeof(FItem), 6, File);

		fclose(File);
	}
}