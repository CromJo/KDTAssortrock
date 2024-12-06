#include <iostream>

int main()
{
	/// :: : �������� ������.
	/// ex : std�ȿ� �ִ� cout ���
	/// std�� namespace�̴�. 
	/// namespace�� �Ҽ��� �������ش�.
	/// �ǹ������� namespace�� ������� �ʴ´�. ����.

	std::cout << "Output\n";
	printf("Hello World\n");

	/*
	Ÿ��		|	����������	|	�޸�ũ��	|	���� ǥ������
	char	|	����			|	1byte		|	-128 ~ 127 (0�ڸ� ǥ������ ���� 127)
	bool	|	�� / ����	|	1byte		|	false ~ true (0 ~ 1)
	short	|	����			|	2byte		|	-32768 ~ 32767
	int		|	����			|	4byte		|	-2147483648 ~ 2147483647
	__int	|	����			|	8byte		|
	float	|	�ε��Ҽ���	|	4byte		|	�Ҽ��� 7�ڸ�
	double	|	�ε��Ҽ���	|	8byte		|	�Ҽ��� 15�ڸ�
	unsigned|	���			|				|	����(-)�� ���� ���(+)�� ��ȯ���ش�. Ex) unsinged char 0 ~ 255
	*/

	unsigned short ShortNumber = 32768 + 32769;
	std::cout << ShortNumber << std::endl;

	// ���� Ÿ�� �տ� const�� ���̸� ����� �ȴ�. (����� ���� �����Ͱ��� ������ �� ����.
	const unsigned short CONST_NUMBER = 500;

	bool TestBool = -1;
	std::cout << "��/���� : " << TestBool << std::endl;

	char TestChar = 'A';
	// C��� ��Ÿ�� ����ȯ
	std::cout << "���� : " << (int)TestChar << std::endl;
	// C++ ��Ÿ�� ����ȯ
	std::cout << "���� : " << static_cast<int>(TestChar) << std::endl;

	// Warning�� ������ �������� ����. 
	// f�� �������� ������� ����� �ν���.
	float TestFloat = 3.14f;
	double TestDouble = 2222.4534953467779456912345678901234567890;
	std::cout << "�Ǽ� : " << TestFloat << std::endl << "���� : " << TestDouble << std::endl;
	printf("���� ��� : %d\n", (int)TestDouble);
	printf("�Ǽ� �ִ� ��� : %.32f\n", TestDouble);

	int TestData = 1234567;
	TestFloat = TestData;
	std::cout << "���� ���� : " << TestFloat << std::endl;

	/// ��Ģ ������ +, -, *, /, %			���ϱ�, ����, ���ϱ�, ������, ������
	///	
	std::cout << 10 / 3.f << std::endl;

	/// ���� ������ : <, >, <=, >=, ==	�������� ũ��, ������ ũ��, �������� ũ�ų� ����, ������ ũ�ų� ����, �����ϴ�.
	std::cout << "���� ������ : " << (70 <= 90) << std::endl;

	/// �� ������ : ||, &&, !			OR, AND, NOT
	std::cout << "�� ������ : " << (0 || 0) << std::endl;

	/// 2���� : 0, 1
	/// 10���� : 0 ~ 9 
	/// 16���� : 0 ~ 9 A(10) ~ F(15)

	/// ��Ʈ���� �� ������ : �� �� ���� �����ؼ� ����� ���� ������ �ȴ�.
	/// OR(|), AND(&), NOT(~), XOR(^)  

	int Buf = 0x1f;
	std::cout << Buf << std::endl;

	/// ����Ʈ ������ : <<, >> 
	/// �� �� ���� �����Ͽ� ����� ���� ������ �ȴ�.
	/// 10 << 3�� 10 * 2��3���� ���ϱ� ��� ���� ����.
	/// 10 >> 4�� 10 / 2��4���� ������ ��� ���� ����.
	/// 2�� n�� ������ ���ϱ�/������ ���꿡 Ưȭ�Ǿ� �ִ�.

	int Color = 0;
	unsigned char r = 255;
	unsigned char g = 128;
	unsigned char b = 0;
	unsigned char a = 200;

	Color = a;
	Color = Color << 8;
	Color = Color | r;
	Color = Color << 8;
	Color = Color | g;
	Color = Color << 8;
	Color = Color | b;

	std::cout << "�÷� : " << Color << std::endl;
	std::cout << "b = " << (Color & 0x000000ff) << std::endl;
	std::cout << "g = " << ((Color >> 8) & 0xff) << std::endl;
	std::cout << "r = " << ((Color >> 16) & 0xff) << std::endl;
	std::cout << "a = " << ((Color >> 24) & 0xff) << std::endl;

	int TestShift = 1;
	TestShift <<= 8;
	std::cout << "����Ʈ : " << TestShift << std::endl;

	return 0;
}