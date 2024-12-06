#include <iostream>

int main()
{
	/*
		switch�� : �б�ó���� �����ϴ�. 
		������ ���� ���� case�� ����� ã�� �ڵ带 ���� ��Ų��.
		break�� ������ switch���� �����Ѵ�.
		default�� if���� else�� ����.
		case ������ ��� �߿��� ������ ���� ���� ����� ������� default�� �����Ѵ�.
	*/

	/*
		��������� ���� Ÿ�� : ���� �� ������Ʈ���� ������ ���� Ÿ���� ���� ����� ����� �� �ִ�. (Ŀ���� ����)
		Ex) ������(Enum), ����ü(Struct), Ŭ����(Class)

		������ (Enum) : ����� ���� ���� Ÿ���� ������ֱ� ���� �ϳ��� �����̴�.
		������ ���ӵ� ���� ����� ���� �� �ִ�.
		���ڿ� �̸��� �ο��� �� �ִ�.
		�������� �⺻���� 4byte�� ũ�⸦ ������ �ִ�.
	*/
	enum E���� : unsigned short
	{
		none = 0,
		�ü�,
		������,
		����,
		����,
		MAX
	};

	enum class E������ : unsigned char
	{
		���� = 0,
		��,
	};

	enum EBuf
	{
		Buf_Attack = 0x1,
		Buf_Defense,
		Buf_HP,
		Buf_MP,
		Buf_EXP
	};

	E���� Job = E����::�ü�;
	
	//sizeof : ��ȣ�ȿ� ���� Ÿ�� Ȥ�� ������ �޸� ũ�Ⱑ �� ����Ʈ���� �����ش�.
	std::cout << sizeof(E����) << std::endl;
	std::cout << sizeof(int) << std::endl;

	switch (Job)
	{
	case E����::�ü�:
	case E����::����:
		std::cout << "�ü� �Ǵ� ���� �Դϴ�. " << std::endl;
		break;
	case E����::������:
	case E����::����:
		std::cout << "������ �Ǵ� ���� �Դϴ�. " << std::endl;
		break;
	default:
		break;
	}

	E������ A = E������::����;
	std::cout << "���� : " << A << std::endl;
}