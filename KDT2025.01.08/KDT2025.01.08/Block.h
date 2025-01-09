#pragma once
#include "GameInfo.h"
using Block = std::vector<std::vector<int>>;	// �߰��ϱ� ������ ���ͷ� ����.

class CBlock
{
public:
	CBlock() {}
	~CBlock() {}

private:
	std::vector<Block> mBlockList;

public:
	std::vector<Block>& GetBlockList()
	{
		return mBlockList;
	}

public:
	// �⺻ ��� �߰� �Լ�
	void DefualtBlockAdd()
	{
		mBlockList.push_back(
			{ 
				{ 1, 1, 1, 1 } 
			});

		mBlockList.push_back
		(
			{
				{ 1, 0 },
				{ 1, 0 },
				{ 1, 1 }
			}
		);

		mBlockList.push_back
		(
			{
				{ 0, 1 },
				{ 0, 1 },
				{ 1, 1 }
			}
		);


		mBlockList.push_back
		(
			{
				{ 0, 1, 0 },
				{ 1, 1, 1 }
			}
		);

		mBlockList.push_back
		(
			{
				{1, 1},
				{1, 1}
			}
		);

		mBlockList.push_back
		(
			{
				{ 0, 1, 1 },
				{ 1, 1, 0 }
			}
		);

		mBlockList.push_back
		(
			{
				{ 1, 1, 0 },
				{ 0, 1, 1 }
			}
		);
	}

	// ���߿� �߰����� �ҳ���Ƴ�
	void CustomBlockAdd()
	{

	}
};


