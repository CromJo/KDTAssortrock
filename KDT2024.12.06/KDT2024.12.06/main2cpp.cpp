#include <iostream>

/*
	�Լ������� : �Լ��� �ּҸ� �����ϱ� ���� �����̴�.
	�Լ��� ���´� ��ȯŸ�԰� ���ڷ� �����ȴ�.

	- ������
	��ȯŸ��(*�̸�)(����Ÿ��);

*/

void Output()
{
	std::cout << "�ƿ�ǲ ���" << std::endl;
}

void Outputtest()
{
	std::cout << "�ƿ�ǲ �׽�Ʈ ���" << std::endl;
}

int main()
{
	Output();

	std::cout << Output << std::endl;

	void(*FuncPointer)();
	FuncPointer = Output;

	return 0;
}