#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include "BlockEditor.h"
#include "Block.h"

// 블록이라는 주체 1개로만 하면 필요없지만,
// 블록의 상세 크기 설정이면 총 7개가 필요함
enum class EObjectType
{
	None,
	Block		// 블록 밖에 없긴하네 enum이 필요할까	
};

enum class EBlockType
{
	None,
	SBlock,
	ZBlock,
	JBlock,
	LBlock,
	IBlock,
	TBlock,
	OBlock,
};

enum class ECollisionType
{
	None,
	Block,
};