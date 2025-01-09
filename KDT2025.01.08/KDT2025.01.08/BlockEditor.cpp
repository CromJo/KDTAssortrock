#include "BlockEditor.h"

CBlockEditor::CBlockEditor()
{
}

void CBlockEditor::CustomBlockAdd()
{
	// null이면 종료
	if (!mBlockEditorList)
		return;

	Block newBlock;
	int result[4] = {};
	bool BlockCreate[16] = {};

	std::cout << "생성할 블록을 표현해주세요. \n(0:빈공간 | 1:블록생성 | 최대 4x4 16칸) \n";
	
	for (int i = 0; i < 4; i++)
	{
		std::cout << i << ". 4자리 입력해주세요. : ";
		std::cin >> result[i];
		std::cout << std::endl;
	}
	
	for (int i = 0; i < 16; i++)
	{
		BlockCreate[i] = result[i] > 0;
	}

	mBlockEditorList->GetBlockList().push_back(newBlock);

	
}
