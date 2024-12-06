#include <iostream>

/*
	�޸� ����
	����		: ���������� ��������� ����.
	������	: ��������, ���� ������ ��������� ����.
				���������� ���������� �ʱ�ȭ ���� �������� ������, 0���� �ڵ� �ʱ�ȭ �ȴ�.
	�ڵ�		: ���α׷� ���� �� �ڵ尡 ����Ǵ� ����.
	��		: �����Ҵ��� ������ �޸𸮰� ��������� ����.

	- �Լ�ȣ��Ծ� �˾ƺ���

	��������	: �ڵ� ��� �ȿ� �����Ͽ� ����ϴ� ����.
				�Լ��� ���ڵ� ���������̴�.
				�Լ� ���� �� �޸𸮰� ���ŵȴ�.
*/

// ���� ���� : �ڵ��� �ٱ��� �����ϴ� �Լ�.
// ���α׷� ���� �� �޸𸮰� �����ǰ�,
// ���α׷� ���� �� �޸𸮰� ���ŵȴ�.
int gNumber = 1000;

void Test(int Number)
{
	int Number1;		// ��������

	// ���������� �ȴ�. �� ������ ó�� 1���� �ʱ�ȭ�ǰ�, 
	// �������ʹ� �ʱ�ȭ�� ���õȴ�.
	// �Ϲ�(����) ������ �Լ� ���� �� �޸𸮰� ���ŵ�����,
	// ���������� ���α׷��� ���������� ���� �ȴ�.
	static int staticNumber = 50;
}

int* CreateDynamicInt()
{
	return new int;
}

// bool Ÿ������ �����Ҵ��� �Ǿ������� üũ�Ѵ�.
bool CreateDynamicBool(int** Alloc)
{
	*Alloc = new int;

	return true;
}

bool CreateDynamicInt2(int*& Alloc)
{
	Alloc = new int;

	return true;
}

int main()
{
	/*
		���������͵� �޸� �ּҸ� �����ϴ� �����̴�.
		���������� : �Ϲ� ������ �޸� �ּҸ� ��Ƴ��� ����
		���������� : �Ϲ������� ������ �޸� �ּҸ� ��Ƴ��� ����
		���������� : ���������� ������ �޸� �ּҸ� ��Ƴ��� ����.
	*/

	int Number = 100;
	int* pNumber = &Number;
	int** ppNumber = &pNumber;

	std::cout << pNumber << " | " << &pNumber << " | " << ppNumber << " | " << &ppNumber << std::endl;

	std::cout << "Number \t\t: " << Number << std::endl;
	std::cout << "Number Addr\t: " << &Number << std::endl;
	std::cout << "pNumber \t: " << pNumber << std::endl;
	std::cout << "pNumber Addr \t: " << &pNumber << std::endl;
	std::cout << "pNumber Value \t: " << *pNumber << std::endl;
	std::cout << "ppNumber \t: " << ppNumber << std::endl;
	std::cout << "ppNumber Addr \t: " << &ppNumber << std::endl;
	std::cout << "ppNumber Value \t: " << *ppNumber << std::endl;

	// pNumber�� Number�� ������ �޸� �ּҸ� ������ �ֱ� ������, 
	// �������� ���� Number������ ���� ������ �� �ִ�.
	*pNumber = 500;
	std::cout << Number << std::endl;

	/*
		���� �Ҵ� : ��Ÿ�ӿ� �޸��� ������ ������ ��Ʈ�� �� �� �ִ� ���.
		C��� ��� : malloc, free�� �̿��Ͽ� �޸𸮸� ���� �� ����.	(Ŭ������ ������ ȣ�� X)
		C++ ��� :	new, delete�� �̿��Ͽ� �޸𸮸� ���� �� ����.	(Ŭ������ ������ ȣ�� O)
			- new �Ҵ��� Ÿ��;
				�� �Ҵ��� Ÿ���� �޸� ũ�⸸ŭ �� ������ �޸𸮸� �����ϰ� �� �ּҸ� ��ȯ.
				�� new�� �̿��Ͽ� �����Ҵ� �� �޸𸮴�,
					delete�� �̿��Ͽ� �޸𸮸� �������� ���� ���,
					�޸𸮰� �״�� �����ְ� �ȴ�. 
					�̷��� ������ "�޸� ��"�̶�� �Ѵ�.
	*/
	int* NumberAddr = new int;
	int** ppNumberAddr = new int*;
	*NumberAddr = 500;
	std::cout << "�ѹ��ּ� : " << NumberAddr << "\t�ѹ� �� : " << *NumberAddr << "\t���ۼ�Ʈ �ѹ� : " << &ppNumberAddr << std::endl;
	// ���� ������ ����
	delete NumberAddr;

	// ���� �迭 �Ҵ�
	int* pArray = new int[10];
	CreateDynamicBool(ppNumberAddr);
	pArray[1] = 300;
	// ���� �迭 ����
	delete[] pArray;


	return 0;
}