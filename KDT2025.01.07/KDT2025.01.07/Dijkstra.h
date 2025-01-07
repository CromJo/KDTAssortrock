#pragma once
#include "Array.h"
#include "Stack.h"
#include "Heap.h"

// 무방향 베이스로 만들어볼 예정.
/*
	게임쪽에서 자주쓰이는 알고리즘은 아님 (속도가 그리 빠른 알고리즘은 아님)
	현실앱 (버스 노선도등)에서 광범위하게 쓰이는 알고리즘


	다익스트라 알고리즘 : 너비우선탐색을 베이스로 하는 알고리즘 (속도 ↓, 정확성 ↑)
		간선(Edge)마다 거리(비용 Cost)를 넣어서 길찾기를 만드는 알고리즘
		모든 도착거리를 계산하기에 결과값을 도출하기위한 속도가 느리고, 정확성이 빠른이유이다.

		로직 :
			1. Queue베이스의 Heap (정렬 Queue)기능을 사용한다.
			2. 정렬의 기준은 Edge의 비용이다.
			3. 각 노드들의 이전 노드를 부모로 상속받고 거리를 계산해둔다.
			4. 더 빠른 거리를 계산이 나온다면 기존 부모를 상속받던 
*/

template <typename T>
class CDijkstraEdge
{
	template <typename T>
	friend class CDijkstra;

	template <typename T>
	friend class CDijkstraNode;

private:
	CDijkstraEdge() {}
	~CDijkstraEdge()
	{

	}

private:
	CDijkstraNode<T>* mNode = nullptr;
	unsigned int mWeight = 0;		// 노드와 노드 사이의 이동비용

};


template <typename T>
class CDijkstraNode
{
	template <typename T>
	friend class CDijkstra;

private:
	CDijkstraNode() {}
	~CDijkstraNode()
	{
		int Size = mEdgeArray.size();
	}

private:
	T mData;
	bool mVisit = false;
	CArray<CDijkstraEdge<T>*> mEdgeArray;
	CDijkstraNode<T>* mPrevious = nullptr;
	// 0xffffffff로 초기화를 하는 이유, 16진수 최대값보다는 비용이 낮을 것이기 때문이다.
	// 0으로 초기화하면 가장 빠른 숫자가 될 수 있는 이슈가 있을 수 있다.
	unsigned int mWeight = 0xffffffff;			// 각 노드들의 이동의 최종비용 저장 변수

};


enum class EDijkstraType
{
	Dir,		// 방향
	NonDir		// 무방향
};


template <typename T>
class CDijkstra
{
public:
	CDijkstra() {}
	~CDijkstra()
	{
		int Size = mNodeArray.size();

		// 생성한 노드를 전부 제거
		for (int i = 0; i < Size; i++)
		{
			delete mNodeArray[i];
		}
	}

private:
	CArray<CDijkstraNode<T>*> mNodeArray;
	EDijkstraType mType = EDijkstraType::NonDir;

public:
	void SetGraphType(EDijkstraType Type)
	{
		mType = Type;
	}

public:
	void AddData(const T& Data)
	{
		CDijkstraNode<T>* Node = new CDijkstraNode<T>;

		Node->mData = Data;
		mNodeArray.push_back(Node);
	}

	void AddEdge(const T& Source, const T& Dest, unsigned int Weight)
	{
		CDijkstraNode<T>* SourceNode = nullptr;
		CDijkstraNode<T>* DestNode = nullptr;

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

		CDijkstraEdge<T>* Edge = new CDijkstraEdge<T>;

		Edge->mNode = DestNode;
		Edge->mWeight = Weight;
		SourceNode->mEdgeArray.push_back(Edge);

		if (EDijkstraType::NonDir == mType)
		{
			CDijkstraEdge<T>* Edge = new CDijkstraEdge<T>;

			Edge->mNode = SourceNode;
			DestNode->mEdgeArray.push_back(Edge);
		}
	}

	/// <summary>
	/// 찾기
	/// result : 최종 경로를 받기위한 배열
	/// Start : 시작 위치
	/// End : 도착 지점
	/// </summary>
	void Find(CArray<T>& result, const T& Start, const T& End)
	{
		CDijkstraNode<T>* StartNode = nullptr;
		CDijkstraNode<T>* EndNode = nullptr;

		int Size = mNodeArray.size();

		for (int i = 0; i < Size; i++)
		{
			// 만약 데이터가 스타트와 일치하면
			if (mNodeArray[i]->mData == Start)
			{
				StartNode = mNodeArray[i];
			}
			else if (mNodeArray[i]->mData == End)
			{
				EndNode = mNodeArray[i];
			}

			mNodeArray[i]->mVisit = false;
			mNodeArray[i]->mPrevious = nullptr;
			mNodeArray[i]->mWeight = 0xffffffff;
		}

		// 노드 못찾으면 종료
		if (!StartNode)
			return;

		CHeap<CDijkstraNode<T>*> Queue;
		Queue.SetSortFunction(CDijkstra<T>::SortFunc());
		Queue.push(StartNode);
		StartNode->mWeight = 0;

		// 큐가 비었으면 종료되도록
		while (!Queue.empty())
		{
			CDijkstraNode<T>* Node = Queue.front();
			int EdgeSize = Node->mEdgeArray.size();

			for (int i = 0; i < EdgeSize; i++)
			{
				// Edge에 붙어있는 노드로 이동하기 위한 비용을 구한다.
				// 현재 노드비용 + 이동하기위한 간선비용
				unsigned int Weight = Node->mWeight + Node->mEdgeArray[i]->mWeight;

				// 위에서 구한 이동비용이 Edge에 붙어있는 노드의 비용보다 낮으면 교체.
				if (Node->mEdgeArray[i]->mNode->mWeight > Weight)
				{
					if (!Node->mEdgeArray[i]->mNode->mVisit)
					{
						Queue.push(Node->mEdgeArray[i]->mNode);
					}

					Node->mEdgeArray[i]->mNode->mVisit = true;
					// Edge에 붙어있는 노드의 비용을 Weight비용으로 교체한다.
					Node->mEdgeArray[i]->mNode->mWeight = Weight;
					//Edge에 붙어있는 노드의 이전 노드로 지정한다.
					Node->mEdgeArray[i]->mNode->mPrevious = Node;
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
		CDijkstraNode<T>* StartNode = nullptr;
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

		CStackList<CDijkstraNode<T>*> Stack;
		Stack.push(StartNode);
		StartNode->mVisit = true;

		// 큐가 비었으면 종료되도록
		while (!Stack.empty())
		{
			CDijkstraNode<T>* Node = Stack.pop();
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

		Result.clear();

		CStackList<T> Stack;
		CDijkstraNode<T>* Current = EndNode;

		// 시작의 이전노드는 무조건 nullptr이므로,
		// 거기에 도달하면 while문이 종료되도록 설정.
		while (Current)
		{
			Stack.push(Current->mData);
			Current = Current->mPrevious;
		}

		while (!Stack.empty())
		{
			T Data = Stack.pop();

			Result.push_back(Data);
		}
	}

private:
	static bool SortFunc(const CDijkstraNode<T>* const& Source, const CDijkstraNode<T>* const& Dest)
	{
		return Source->mWeight > Dest->mWeight;
	}
};

