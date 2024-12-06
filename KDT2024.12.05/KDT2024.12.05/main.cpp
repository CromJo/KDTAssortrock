#include <iostream>
#include <string>

/*
	�迭 : �ϳ��� Ÿ���� ���� �̸����� ������ ����� ��.
	����ü : N���� �ڷ��� ������ �ϳ��� �׷����� ����� ��.
		struct Type
		{ 
			int a = 0; 
			float b = 0.1f; 
			double c = 0.002f; 
		};
*/

enum class EItemType : unsigned char
{
	Weapon = 0,
	Armor,

	MAX
};

struct FState
{
	// ����ü ��� ������ �⺻������ �Ǿ��ִٸ�,
	// ���� ������ �ڷ����� ���� ū ����Ʈ�� ������ ��������,
	// ũ�⵵ ���㿡 �°� �ö󰣴�.
	// ������ ���� ��ġ�� ���� ����Ʈ�� ������ �޶��� �� �ִ�.
	bool a;
	bool b;
	bool c;
	double ccc;
	bool d;
	int ef;
	bool e;
};

struct FItem
{
	// ���ڿ� ���� ���ڿ� �迭�� ���� 0(null)�� ����Ǿ�� �Ѵ�.
	char Name[32];
	int Option;
	int Price;
	short shortty;
	EItemType ItemType;
};

// �Լ��� ����
void OutputItem(FItem& item);
void OutputItem(const FItem& item);		// 8byte�̻��� �ڷ����� ����Ҷ� ���۷����� �����Ͽ� ����ϸ� �ӵ����� ������ ��� ��ų �� �ִ�. 


int main()
{
	FItem item;
	FItem item2 = {"���� ���̾�", 2, 4, 2, EItemType::Weapon };
	FItem& item3 = item;
	item.ItemType = EItemType::Weapon;
	item.Option = 100;
	item.Price = 1000;
	// strcpy : ���ڿ� �����Լ�. 2��° �Ű������� ���ڿ��� ù��°���� �ٿ��־��ִ� ����̴�.
	strcpy_s(item.Name, "��ġ ������");

	// ���۷��� : ����, �ٸ� ������ �����ϴ� ������ ���� �� �ִ�.
	//			������ �ϰԵǸ� �ش� ������ ���� ������ �� �ְ� �ȴ�.
	//			���� ����� �ݵ�� ���۷��� ����� ���ÿ� �����Ǿ�� �Ѵ�.

	// RefNumber�� Number������ �����ϰ� �Ǿ� RefNumber�� �̿��Ͽ� Number�� ���� ������ �� �ְ� �ȴ�.
	int Number = 500;
	int Number1 = 100;
	int& RefNumber = Number;

	// �Ʒ��� ������ �ƴ϶� RefNumber�� �����ϰ� �ִ� Number ������ ���� 
	// Number1�� ������ "����"���ִ� ���̴�.
	RefNumber = Number1;

	OutputItem(item3);

	return 0;
}

// �Լ��� ����
void OutputItem(const FItem& item)
{

}