#include <iostream>
#include "Tree.h"

int main()
{
	CTree<std::string, int> Tree1;
	Tree1.insert("Node0", 10, "");			// 루트
	Tree1.insert("Node1", 10, "");			// 루트
	Tree1.insert("Node2", 10, "");			// 노드2 루트
	Tree1.insert("Node3", 10, "Node2");
	Tree1.insert("Node4", 10, "Node1");
	Tree1.insert("Node5", 10, "Node1");
	Tree1.insert("Node6", 10, "Node5");
	Tree1.insert("Node7", 10, "Node5");

	Tree1.TestOutput();

	return 0;
}