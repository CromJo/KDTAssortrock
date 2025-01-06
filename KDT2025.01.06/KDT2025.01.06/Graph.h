#pragma once
#include "Array.h"
#include "Queue.h"
#include "Stack.h"

/*
	Ʈ�� : �θ�� N���� ���ϵ尡 �ִ� ������ ����̴�.

	�׷��� : ���鳢�� ����(����)�� �����
	���⼺ �׷��� : �̵� ������ ���� �׷���.
				���� ��� ���̿� �̵��� �� �ִ� ������ �����Ͽ�,
				�ش� ������ �������� �̵��� �� �ִ� �׷���.
				(�Ϲ�����)
	������ �׷��� : ��������� �̵��� �� �ִ� �׷���.
				(�ֹ�����)
				�� ��ã�� �˰��򿡼� ���� ���δ�.

	�׷����� ��ȸ���
	�ʺ�켱Ž��(BFS) : ������ ���������� Ž�� ���
					1. ���� ��忡�� �� �� �ִ� ��� ���� �湮�Ѵ�. (QUEUE�� ���� ������ ��带 �־�д�.)
					2. �湮�ѵ� ���� ��带 ���Լ��⿡ ���� ���������� ����(�̵�) �Ѵ�.
					3. �湮�� ����� �� �� �ִ� ��� ���� �湮�Ѵ�. (QUEUE�� ���Ӱ� �߰��� �� �ִ� ��带 �ִ´�.)
					4.
	���̿켱Ž��(DFS) : ���� �������� Ž���Ͽ�, �� �̻� �̵� �Ұ��� ���, ���ư��� �ٸ� ��� �ٽ� Ž���ϴ� ���.
					1. ���� ��忡�� �� �� �ִ� ��� ���� �湮�Ѵ�. (Stack���� �����Ͽ� ���� ������ ��带 �־�д�.)
					2.

	�������
		������� : 2���� �迭�� Ȱ���ϴ� ���.
				���	  1 2 3 4 5 6		( 0 : ���� X | 1 : ���� O)
					1 0 1 1 0 0 0
					2 1 0 1 1 1 0 
					3 1 1 0 0 1 0
					4 0 1 0 0 1 1
					5 0 1 1 1 0 0
					6 0 0 0 1 0 0
					��������Ʈ : ��ũ�帮��Ʈ ������� ����� ������ �ּҸ� ������ �ְ��Ͽ� �����ϴ� ���.
								�� ǥ�� ���ؼ� �̵��� �� �ִ� ��� ǥ��
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

		// ������ ��带 ���� ����
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
	Dir,		// ����
	NonDir		// ������
};



template <typename T> 
class CGraph
{
public:
	CGraph() {}
	~CGraph() 
	{
		int Size = mNodeArray.size();

		// ������ ��带 ���� ����
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
			// ���� �����Ͱ� �ҽ��� ��ġ�ϸ�
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
		// Source�� Dest�� �Ѱ��� ��ã������ ����
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
	/// �ʺ� �켱 Ž��
	/// Start : ���� ��ġ
	/// �Լ� ������ ������� : ����� ����
	/// </summary>
	void BFS(const T& Start, void (*Func)(const T&))
	{
		CGraphNode<T>* StartNode = nullptr;
		int Size = mNodeArray.size();
		
		for (int i = 0; i < Size; i++)
		{
			// ���� �����Ͱ� ��ŸƮ�� ��ġ�ϸ�
			if (mNodeArray[i]->mData == Start)
			{
				StartNode = mNodeArray[i];
			}

			mNodeArray[i]->mVisit = false;
		}

		// ��� ��ã���� ����
		if (!StartNode)
			return;

		CQueue<CGraphNode<T>*> Queue;
		Queue.push(StartNode);
		StartNode->mVisit = true;

		// ť�� ������� ����ǵ���
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
	/// ���� �켱 Ž��
	/// Start : ���� ��ġ
	/// �Լ� ������ ������� : ����� ����
	/// </summary>
	void DFS(const T& Start, void (*Func)(const T&))
	{
		CGraphNode<T>* StartNode = nullptr;
		int Size = mNodeArray.size();

		for (int i = 0; i < Size; i++)
		{
			// ���� �����Ͱ� ��ŸƮ�� ��ġ�ϸ�
			if (mNodeArray[i]->mData == Start)
			{
				StartNode = mNodeArray[i];
			}

			mNodeArray[i]->mVisit = false;
		}

		// ��� ��ã���� ����
		if (!StartNode)
			return;

		CStackList<CGraphNode<T>*> Stack;
		Stack.push(StartNode);
		StartNode->mVisit = true;

		// ť�� ������� ����ǵ���
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

