#include <iostream>
#include "BinarySearchTree.h"

int main()
{
	CBinarySearchTree<std::string, int>	IntMap;

	IntMap.insert("R", 100);
	IntMap.insert("F", 200);
	IntMap.insert("V", 300);
	IntMap.insert("D", 400);
	IntMap.insert("T", 500);

	CBinarySearchTree<std::string, int>::iterator	iter;
	CBinarySearchTree<std::string, int>::iterator	iterEnd = IntMap.end();

	for (iter = IntMap.begin(); iter != iterEnd; ++iter)
	{
		std::cout << "Key : " << iter->mKey << " Value : " <<
			iter->mData << std::endl;
	}

	iter = IntMap.find("Y");

	if (iter != IntMap.end())
	{
		std::cout << "Find Key : " << iter->mKey << " Value : " <<
			iter->mData << std::endl;
	}

	else
		std::cout << "키가 없습니다." << std::endl;

	return 0;
}