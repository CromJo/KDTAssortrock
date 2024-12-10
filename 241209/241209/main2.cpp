#include <iostream>

enum class EItemType : unsigned char
{
	Weapon,
	Armor
};

struct FItem
{
	char Name[32];
	EItemType ItemType;
	int Option;
	int Buy;
	int Sell;
};

int main()
{
	FILE* File = nullptr;

	fopen_s(&File, "TestFile1.abc", "wb");

	if (File)
	{
		int Number = 100;
		FItem Item;
		strcpy_s(Item.Name, "¸ñ°Ë");
		Item.ItemType = EItemType::Weapon;
		Item.Option = 10;
		Item.Buy = 1000;
		Item.Sell = 500;

		fwrite(&Number, sizeof(int), 1, File);
		fwrite(&Item, sizeof(FItem), 1, File);

		fclose(File);
	}

	fopen_s(&File, "TestFile1.abc", "rb");

	if (File);
	{
		int Number1 = 0;
		fread(&Number1, sizeof(int), 1, File);

		std::cout << Number1 << std::endl;

		FItem Item = {};
		fread(&Item, sizeof(FItem), 1, File);

		std::cout << Item.Name << std::endl;
		std::cout << (int)Item.ItemType << std::endl;
		std::cout << Item.Option << std::endl;
		std::cout << Item.Buy << std::endl;
		std::cout << Item.Sell << std::endl;
		
		fclose(File);
	}
}