#pragma once
#include <vector>
#include "BlockEditor.h"
#include "GameInfo.h"
using Block = std::vector<std::vector<int>>;	// 추가하기 쉽도록 벡터로 구현.

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
	// 기본 블록 추가 함수
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

	// 나중에 추가하자 죠낸어렵네
	void CustomBlockAdd()
	{

	}
};


