#pragma once
#include "Array.h"
#include "Stack.h"
#include "Heap.h"

// ������ ���̽��� ���� ����.
/*
	�����ʿ��� ���־��̴� �˰����� �ƴ� (�ӵ��� �׸� ���� �˰����� �ƴ�)
	���Ǿ� (���� �뼱����)���� �������ϰ� ���̴� �˰���


	���ͽ�Ʈ�� �˰��� : �ʺ�켱Ž���� ���̽��� �ϴ� �˰��� (�ӵ� ��, ��Ȯ�� ��)
		����(Edge)���� �Ÿ�(��� Cost)�� �־ ��ã�⸦ ����� �˰���
		��� �����Ÿ��� ����ϱ⿡ ������� �����ϱ����� �ӵ��� ������, ��Ȯ���� ���������̴�.

		���� :
			1. Queue���̽��� Heap (���� Queue)����� ����Ѵ�.
			2. ������ ������ Edge�� ����̴�.
			3. �� ������ ���� ��带 �θ�� ��ӹް� �Ÿ��� ����صд�.
			4. �� ���� �Ÿ��� ����� ���´ٸ� ���� �θ� ��ӹ޴� 
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
	unsigned int mWeight = 0;		// ���� ��� ������ �̵����

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
	// 0xffffffff�� �ʱ�ȭ�� �ϴ� ����, 16���� �ִ밪���ٴ� ����� ���� ���̱� �����̴�.
	// 0���� �ʱ�ȭ�ϸ� ���� ���� ���ڰ� �� �� �ִ� �̽��� ���� �� �ִ�.
	unsigned int mWeight = 0xffffffff;			// �� ������ �̵��� ������� ���� ����

};


enum class EDijkstraType
{
	Dir,		// ����
	NonDir		// ������
};


template <typename T>
class CDijkstra
{
public:
	CDijkstra() {}
	~CDijkstra()
	{
		int Size = mNodeArray.size();

		// ������ ��带 ���� ����
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
	/// ã��
	/// result : ���� ��θ� �ޱ����� �迭
	/// Start : ���� ��ġ
	/// End : ���� ����
	/// </summary>
	void Find(CArray<T>& result, const T& Start, const T& End)
	{
		CDijkstraNode<T>* StartNode = nullptr;
		CDijkstraNode<T>* EndNode = nullptr;

		int Size = mNodeArray.size();

		for (int i = 0; i < Size; i++)
		{
			// ���� �����Ͱ� ��ŸƮ�� ��ġ�ϸ�
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

		// ��� ��ã���� ����
		if (!StartNode)
			return;

		CHeap<CDijkstraNode<T>*> Queue;
		Queue.SetSortFunction(CDijkstra<T>::SortFunc());
		Queue.push(StartNode);
		StartNode->mWeight = 0;

		// ť�� ������� ����ǵ���
		while (!Queue.empty())
		{
			CDijkstraNode<T>* Node = Queue.front();
			int EdgeSize = Node->mEdgeArray.size();

			for (int i = 0; i < EdgeSize; i++)
			{
				// Edge�� �پ��ִ� ���� �̵��ϱ� ���� ����� ���Ѵ�.
				// ���� ����� + �̵��ϱ����� �������
				unsigned int Weight = Node->mWeight + Node->mEdgeArray[i]->mWeight;

				// ������ ���� �̵������ Edge�� �پ��ִ� ����� ��뺸�� ������ ��ü.
				if (Node->mEdgeArray[i]->mNode->mWeight > Weight)
				{
					if (!Node->mEdgeArray[i]->mNode->mVisit)
					{
						Queue.push(Node->mEdgeArray[i]->mNode);
					}

					Node->mEdgeArray[i]->mNode->mVisit = true;
					// Edge�� �پ��ִ� ����� ����� Weight������� ��ü�Ѵ�.
					Node->mEdgeArray[i]->mNode->mWeight = Weight;
					//Edge�� �پ��ִ� ����� ���� ���� �����Ѵ�.
					Node->mEdgeArray[i]->mNode->mPrevious = Node;
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
		CDijkstraNode<T>* StartNode = nullptr;
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

		CStackList<CDijkstraNode<T>*> Stack;
		Stack.push(StartNode);
		StartNode->mVisit = true;

		// ť�� ������� ����ǵ���
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

		// ������ �������� ������ nullptr�̹Ƿ�,
		// �ű⿡ �����ϸ� while���� ����ǵ��� ����.
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

