#include <iostream>
#include "BinarySearchTree.h"

/*
	제거 기능.

	1. 제거 할 번호를 제거한다.
	2. 연결되어있는 선을 제거한다.

	상위 제거 기능.
	1. 제거 할 번호의 하위 노드중 제일 큰 값 A를 찾는다.
	2. A를 제거 노드자리에 옮긴다.
	3. 기존에 있던 자리 A를 제거한다.


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
