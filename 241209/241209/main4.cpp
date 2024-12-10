#include <iostream>
#include <fstream>

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
	std::ofstream ostream;

	ostream.open("testFile3.abc", std::ios::binary);

	if (ostream.is_open())
	{
		int Number = 100;
		ostream.write((const char*)&Number, sizeof(FItem));
		FItem Item;
		strcpy_s(Item.Name, "¸ñ°Ë");
		Item.ItemType = EItemType::Weapon;
		Item.Option = 10;
		Item.Buy = 1000;
		Item.Sell = 500;

		ostream.close();
	}

	std::ifstream istream;
	istream.open("testFile3.abc");

	if (istream.is_open())
	{
		int Number1 = 0;
		istream.read((char*)&Number1, sizeof(int));

		FItem Item1 = {};
		istream.read((char*)&Item1, sizeof(FItem));

		std::cout << Item1.Name << std::endl;
		std::cout << (int)Item1.ItemType << std::endl;
		std::cout << Item1.Option << std::endl;
		std::cout << Item1.Buy << std::endl;
		std::cout << Item1.Sell << std::endl;

		istream.close();
	}

	return 0;
}