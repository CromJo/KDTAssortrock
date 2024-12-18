#include <iostream>

class CTemp
{
private:
	int mTemp = 100;

public:
	CTemp();
	CTemp(int num)
	{
		int num;
	}
	~CTemp();

	/*
		�̵������� : ��ü�� ����ִ� ���¿��� ��� ���Ѵٴ°���
					������ �� �ִ� ��Ȳ�� �� ����Ѵ�.
					&&�� ���� �Ǹ� ������ ���۷����̴�.
	*/
	CTemp(CTemp&& ref)
	{
		std::cout << "�̵� ������" << std::endl;
	}

	CTemp(const CTemp& Temp)
	{
		mTemp = Temp.mTemp;
	}


private:
}

int TestFunc(const int& Num)
{
	std::cout << Num << std::endl;

	return Num;
}

int main()				// ����, ������ ����
{
	// lvalue(������) : & �����ڸ� �̿��Ͽ� �޸��� �ּҸ� ������ �� �ִ� ���̴�.
	// rvalue(������) : �ּҸ� ������ �� ���� ��.
	// �Ʒ����� Number�� ��������, 10�� �������� �ǹ��Ѵ�.
	int Number = 10;
	TestFunc(Number);

	CTemp temp;
	CTemp temp1(20);
	// 1. �ӽð�ü����
	// 2. ����
	// 3. ������ ���� �� �ӽð�ü ����
	temp1 = CTemp(30);

	CTemp temp2 = temp;

	const CTemp& ref1 = CTemp(70);

	CTemp temp4 = CTemp(90);
	temp4 = CTemp(200);
	
	temp4 = temp.Create();

	return 0;
}