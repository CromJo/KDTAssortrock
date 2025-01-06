#include <iostream>
#include "Graph.h"

void OutputNode(const int& Data)
{
	std::cout << Data << " -> ";
}

int main()
{
	CGraph<int> IntGraph;

	IntGraph.AddData(1);
	IntGraph.AddData(2);
	IntGraph.AddData(3);
	IntGraph.AddData(4);
	IntGraph.AddData(5);
	IntGraph.AddData(6);

	IntGraph.AddEdge(1, 2);
	IntGraph.AddEdge(1, 3);

	IntGraph.AddEdge(2, 3);
	IntGraph.AddEdge(2, 4);
	IntGraph.AddEdge(2, 5);

	IntGraph.AddEdge(3, 5);
	
	IntGraph.AddEdge(4, 5);
	IntGraph.AddEdge(4, 6);


	std::cout << "--------------------³Êºñ ¿ì¼± Å½»ö-----------------------" << std::endl;

	IntGraph.BFS(2, OutputNode);

	std::cout << std::endl;

	std::cout << "--------------------±íÀÌ ¿ì¼± Å½»ö-----------------------" << std::endl;

	IntGraph.DFS(2, OutputNode);

	return 0;
}