#include <iostream>
#include "BinarySearchTree.h"

/*
	���� ���.

	1. ���� �� ��ȣ�� �����Ѵ�.
	2. ����Ǿ��ִ� ���� �����Ѵ�.

	���� ���� ���.
	1. ���� �� ��ȣ�� ���� ����� ���� ū �� A�� ã�´�.
	2. A�� ���� ����ڸ��� �ű��.
	3. ������ �ִ� �ڸ� A�� �����Ѵ�.


*/

int main()
{
	CBinarySearchTree<int, int>	IntTree;

	IntTree.insert(10, 10);
	IntTree.insert(4, 4);
	IntTree.insert(2, 2);
	IntTree.insert(1, 1);
	IntTree.insert(3, 3);
	IntTree.insert(8, 8);
	IntTree.insert(7, 7);

	IntTree.insert(30, 30);
	IntTree.insert(20, 20);
	IntTree.insert(15, 15);
	IntTree.insert(25, 25);

	IntTree.insert(50, 50);
	IntTree.insert(40, 40);
	IntTree.insert(80, 80);
	IntTree.insert(45, 45);

	CBinarySearchTree<int, int>::iterator	iter;
	CBinarySearchTree<int, int>::iterator	iterEnd =
		IntTree.end();

	/*iter = IntTree.erase(4);
	std::cout << "erase Next Key : " << iter->mKey <<
		", Value : " << iter->mData << std::endl;*/

	for (iter = IntTree.begin(); iter != iterEnd; ++iter)
	{
		std::cout << "Key : " << iter->mKey <<
			", Value : " << iter->mData << std::endl;
	}

	std::cout << "======== PreOrder ========" <<
		std::endl;
	IntTree.PreOrder();

	std::cout << "======== InOrder ========" <<
		std::endl;
	IntTree.InOrder();

	std::cout << "======== PostOrder ========" <<
		std::endl;
	IntTree.PostOrder();

	return 0;
}
