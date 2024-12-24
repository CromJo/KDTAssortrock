#include <iostream>
#include <vector>

/*
	���ø��� Ȱ���
	�迭 Ŭ���� �����

	stl(Standard Template Library) : C++���� �����ϴ� ǥ�� ���ø� ���̺귯���̴�.
	std namespace �ȿ� ���ִ�.
	���ø��� �̿��ϱ� ������ ���ϴ� Ÿ���� �����ϰ� �����͸� ������ �� �ִ�.
	-------�ַ� �ٷ� 3����-------
	- ������ �����̳�
	1. vector		: �����迭�� �����س��� Ŭ����.
				Ư¡	: �ʿ信 ���� ũ�⸦ �ø��ų� ���� �� �ִ� �迭�̴�.
					random Access�� �����Ͽ� Index�� ������ �����ϴ�.
					���� ���� �߰��� ��� 0(1)�� ������ �����ش�.
					�߰��� �߰�/���� �� ��� 0(n)�� ������ �����ش�.

	2. list			: 
	
	- ���� �����̳�
	1. unordered_map: 
	---------------------------
*/


class CContainer
{
public:
	CContainer()
	{
		//std::cout << "������" << std::endl;
	}

	CContainer(int Num) :
		mNum(Num)
	{
		//std::cout << "���� ������" << std::endl;
	}

	CContainer(const CContainer& Con)
	{
		mNum = Con.mNum;
		//std::cout << "���������" << std::endl;
	}

	CContainer(CContainer&& Con)
	{
		mNum = Con.mNum;
		//std::cout << "�̵�������" << std::endl;
	}

	~CContainer()
	{
		//std::cout << "�Ҹ���" << std::endl;
	}

	int	mNum = 0;
};

int main()
{
	std::vector<CContainer> vectorCon;	
	std::vector<int> vectorInt;			// Int Ÿ���� �����ϴ� ����(�����迭)����.

	// ���ʹ� ����߰��� ���� ��� �迭ũ�Ⱑ
	// 0�̴�.
	std::cout << "ó�� Capacity : " << vectorInt.capacity() << std::endl;

	// push/emplace Back : �Ѵ� ���� ���� �߰�.
	// push_back�� ��������� Ȥ�� �̵������� ���� �ϳ��� ȣ��ȴ�.
	//	���ڷ� ���� ���� �ӽð�ü�� ��� "�̵�����"�� �ȴ�.
	int Index = 0;
	vectorInt.push_back(10);			// �̵�����
	vectorInt.push_back(Index);			// �������
	// pop_back�� ���� ������ �迭�� �����Ѵ�.
	vectorInt.pop_back();				//
	// clear�� ��ü ��Ҹ� �����Ѵ�.
	vectorInt.clear();
	// size�� �߰��� ������ ���´�.
	vectorInt.size();
	// capacity�� �迭 ��ü ������ ���´�.
	vectorInt.capacity();
	// empty�� �迭�� ���������� (������ �߱�Ȱ� ������) true, �ƴϸ� false
	vectorInt.empty();
	// at(�ε���)�ε� �迭�� ������ �� �ִ�.
	vectorInt.at(1);
	// front()�� ù��° ��Ҹ� �����´�.
	vectorInt.front();
	// back()�� ������ ��Ҹ� �����´�.
	vectorInt.back();
	// reserve : ���� ������ ���ϴ� ��ŭ �ø���.
	vectorInt.reserve(100);		// �迭 ������ Index���� �°� �����Ѵ�.
	// resize : �迭 ���� �� �߰��� ��ҵ� �� ������ŭ �Ѵ�.
	vectorInt.resize(100);
	// emplace_back : �����������.
	//���ڸ� �̿��Ͽ� �� ������ ���� �޸𸮿��� ��ü ������ �Ѵ�.
	vectorInt.emplace_back(20);			// ���ο��� ����/�̵��� ���� �ʴ´�.

	for (int i = 0; i < 10; i++)
	{
		vectorInt.push_back(i * 100);
		std::cout << "Size : " << vectorInt.size() << std::endl;
		std::cout << "Capacity : " << vectorInt.capacity() << std::endl;
	}


	/*
		iterator : �� ��Ҹ� ���ʴ�� �湮�� �� �ְ� ���ִ� ����̴�.
				�ݺ����̱� ������ �ݺ��ؼ� ��Ҹ� ���ʷ� �湮�Ͽ�,
				���� ���� �� �ְ�, ������ �� �ִ�.
	*/
	// reverse iterator : �ڿ������� ������ �ݺ��ϴ� �뵵�� ���.

	// �迭 ������ ���ϴ¸�ŭ �ø���.
	//vectorInt.reserve(100);
	// �迭 ������ �ø��� �߰��� ��ҵ�
	// �� ������ŭ���� �Ѵ�.
	vectorInt.resize(100);

	for (int i = 0; i < 10; ++i)
	{
		vectorInt.push_back(i * 100);
		std::cout << "Size : " << vectorInt.size() <<
			", Capacity : " << vectorInt.capacity() <<
			std::endl;
	}

	// �̳�Ŭ���� : Ŭ�����ȿ� Ŭ������ ����
	std::vector<int>::iterator iter;
	std::vector<int>::iterator iterEnd = vectorInt.end();

	// begin : �迭�� ù��° ��Ҹ� ������ �ִ�
	// iterator�� ��ȯ�Ѵ�.
	// end : �迭 ����������� ������ ������ �ִ�
	// iterator�̴�. ��������� ���� ǥ���ϱ�����
	// ���ȴ�.
	for (iter = vectorInt.begin(); iter != iterEnd; iter++)
	{
		// �������� �Ͽ� iterator�� ������
		// �ִ� ����� ���� �����´�.
		std::cout << *iter << std::endl;
	}
		
	// reverse iterator : �ڿ������� ������[
	// �ݺ��ϴ� �뵵�� ����Ѵ�.
	std::vector<int>::reverse_iterator iterReverse;
	std::vector<int>::reverse_iterator iterEnd = vectorInt.rend();

	for (iterReverse = vectorInt.rbegin(); iterReverse != iterEnd; iterReverse++)
	{
		std::cout << *iterEnd << std::endl;
	}

	std::vector<int>::const_iterator citer;
	citer = vectorInt.begin();

	iter = vectorInt.insert(iter, 1234);

	iterReverse = vectorInt.begin();
	iterReverse += 100;

	// insert() ����� �߰� �迭�� �߰��ϴ� ���̴�.
	citer = vectorInt.insert(iterReverse, 1020);

	// erase : ������ ��Ҹ� �����Ѵ�.
	// ���ڷ� �� iterator�� ��Ҹ� �����ϰ�,
	// �� ������Ҹ� ������ iterator�� ��ȯ.
	vectorInt.erase(iter);

	iter = vectorInt.erase(vectorInt.begin(), iter);

	std::cout << *iter << std::endl;
	
	iterEnd = vectorInt.end();

	for (iter = vectorInt.begin(); iter != iterEnd; iter++)
	{
		std::cout << *iter << std::endl;
	}

	return 0;
}