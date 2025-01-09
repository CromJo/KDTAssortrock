#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include "BlockEditor.h"
#include "Block.h"

// ����̶�� ��ü 1���θ� �ϸ� �ʿ������,
// ����� �� ũ�� �����̸� �� 7���� �ʿ���
enum class EObjectType
{
	None,
	Block		// ��� �ۿ� �����ϳ� enum�� �ʿ��ұ�	
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