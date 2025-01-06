#pragma once
#include "Array.h"
#include "Queue.h"
#include "Stack.h"

/*
	트리 : 부모와 N개의 차일드가 있는 형태의 방식이다.

	그래프 : 노드들끼리 간선(엣지)를 연결시
	방향성 그래프 : 이동 방향을 가진 그래프.
				노드와 노드 사이에 이동할 수 있는 간선을 연결하여,
				해당 간선의 방향으로 이동할 수 있는 그래프.
				(일방통행)
	무방향 그래프 : 양방향으로 이동할 수 있는 그래프.
				(쌍방통행)
				※ 길찾기 알고리즘에서 자주 쓰인다.

	그래프의 순회방법
	너비우선탐색(BFS) : 범위를 넓혀나가는 탐색 방법
					1. 현재 노드에서 갈 수 있는 모든 곳을 방문한다. (QUEUE로 접근 가능한 노드를 넣어둔다.)
					2. 방문한뒤 넣은 노드를 선입선출에 의해 순차적으로 접근(이동) 한다.
					3. 방문한 노드의 갈 수 있는 모든 곳을 방문한다. (QUEUE에 새롭게 추가할 수 있는 노드를 넣는다.)
					4.
	깊이우선탐색(DFS) : 한쪽 방향으로 탐색하여, 더 이상 이동 불가일 경우, 돌아가서 다른 길로 다시 탐색하는 방법.
					1. 현재 노드에서 갈 수 있는 모든 곳을 방문한다. (Stack으로 구현하여 접근 가능한 노드를 넣어둔다.)
					2.

	구현방법
		인접행렬 : 2차원 배열을 활용하는 방식.
				노드	  1 2 3 4 5 6		( 0 : 연결 X | 1 : 연결 O)
					1 0 1 1 0 0 0
					2 1 0 1 1 1 0 
					3 1 1 0 0 1 0
					4 0 1 0 0 1 1
					5 0 1 1 1 0 0
					6 0 0 0 1 0 0
					인접리스트 : 링크드리스트 방식으로 연결된 노드들의 주소를 가지고 있게하여 연결하는 방식.
								윗 표에 의해서 이동할 수 있는 노드 표시
								1 -> 2 -> 3
								2 -> 1 -> 3 -> 4 -> 5
								3 -> 1 -> 2 -> 5
								4 -> 2 -> 5 -> 6
								5 -> 2 -> 3 -> 4
								6 -> 4
				
*/

template <typename T>
class CGraphEdge
{
	template <typename T>
	friend class CGraph;

	template <typename T>
	friend class CGraphNode;


private:
	CGraphEdge() {}
	~CGraphEdge() {}

private:
	CGraphNode<T>* mNode = nullptr;
};

template <typename T>
class CGraphNode
{
	template <typename T>
	friend class CGraph;

private:
	CGraphNode() {}
	~CGraphNode()
	{
		int Size = mEdgeArray.size();

		// 생성한 노드를 전부 제거
		for (int i = 0; i < Size; i++)
		{
			delete mEdgeArray[i];
		}
	}

private:
	T mData;
	bool mVisit = false;
	CArray<CGraphEdge<T>*> mEdgeArray;
};

enum class EGraphType
{
	Dir,		// 방향
	NonDir		// 무방향
};



template <typename T> 
class CGraph
{
public:
	CGraph() {}
	~CGraph() 
	{
		int Size = mNodeArray.size();

		// 생성한 노드를 전부 제거
		for (int i = 0; i < Size; i++)
		{
			delete mNodeArray[i];
		}
	}

private:
	CArray<CGraphNode<T>*> mNodeArray;
	EGraphType mType = EGraphType::NonDir;

public:
	void SetGraphType(EGraphType Type)
	{
		mType = Type;
	}

public:
	void AddData(const T& Data)
	{
		CGraphNode<T>* Node = new CGraphNode<T>;

		Node->mData = Data;
		mNodeArray.push_back(Node);
	}

	void AddEdge(const T& Source, const T& Dest)
	{
		CGraphNode<T>* SourceNode = nullptr;
		CGraphNode<T>* DestNode = nullptr;

		int Size = mNodeArray.size();

		for (int i = 0; i < Size; i++)
		{
			// 만약 데이터가 소스와 일치하면
			if (mNodeArray[i]->mData == Source)
			{
				SourceNode = mNodeArray[i];
			}
			else if (mNodeArray[i]->mData == Dest)
			{
				DestNode = mNodeArray[i];
			}

			if (SourceNode && DestNode)
				break;
		}
		// Source와 Dest를 한개라도 못찾았으면 종료
		if (!SourceNode || !DestNode)
			return;

		CGraphEdge<T>* Edge = new CGraphEdge<T>;

		Edge->mNode = DestNode;
		SourceNode->mEdgeArray.push_back(Edge);

		if (EGraphType::NonDir == mType)
		{
			CGraphEdge<T>* Edge = new CGraphEdge<T>;

			Edge->mNode = SourceNode;
			DestNode->mEdgeArray.push_back(Edge);
		}
	}

	/// <summary>
	/// 너비 우선 탐색
	/// Start : 시작 위치
	/// 함수 포인터 사용이유 : 출력을 위해
	/// </summary>
	void BFS(const T& Start, void (*Func)(const T&))
	{
		CGraphNode<T>* StartNode = nullptr;
		int Size = mNodeArray.size();
		
		for (int i = 0; i < Size; i++)
		{
			// 만약 데이터가 스타트와 일치하면
			if (mNodeArray[i]->mData == Start)
			{
				StartNode = mNodeArray[i];
			}

			mNodeArray[i]->mVisit = false;
		}

		// 노드 못찾으면 종료
		if (!StartNode)
			return;

		CQueue<CGraphNode<T>*> Queue;
		Queue.push(StartNode);
		StartNode->mVisit = true;

		// 큐가 비었으면 종료되도록
		while (!Queue.empty())
		{
			CGraphNode<T>* Node = Queue.pop();
			int EdgeSize = Node->mEdgeArray.size();

			for (int i = 0; i < EdgeSize; i++)
			{
				if (!Node->mEdgeArray[i]->mNode->mVisit)
				{
					Queue.push(Node->mEdgeArray[i]->mNode);
					Node->mEdgeArray[i]->mNode->mVisit = true;
				}
			}

			Func(Node->mData);
		}
	}

	/// <summary>
	/// 깊이 우선 탐색
	/// Start : 시작 위치
	/// 함수 포인터 사용이유 : 출력을 위해
	/// </summary>
	void DFS(const T& Start, void (*Func)(const T&))
	{
		CGraphNode<T>* StartNode = nullptr;
		int Size = mNodeArray.size();

		for (int i = 0; i < Size; i++)
		{
			// 만약 데이터가 스타트와 일치하면
			if (mNodeArray[i]->mData == Start)
			{
				StartNode = mNodeArray[i];
			}

			mNodeArray[i]->mVisit = false;
		}

		// 노드 못찾으면 종료
		if (!StartNode)
			return;

		CStackList<CGraphNode<T>*> Stack;
		Stack.push(StartNode);
		StartNode->mVisit = true;

		// 큐가 비었으면 종료되도록
		while (!Stack.empty())
		{
			CGraphNode<T>* Node = Stack.pop();
			int EdgeSize = Node->mEdgeArray.size();

			for (int i = 0; i < EdgeSize; i++)
			{
				if (!Node->mEdgeArray[i]->mNode->mVisit)
				{
					Stack.push(Node->mEdgeArray[i]->mNode);
					Node->mEdgeArray[i]->mNode->mVisit = true;
				}
			}

			Func(Node->mData);
		}
	}
};

