#include "BlockEditor.h"

CBlockEditor::CBlockEditor()
{
}

void CBlockEditor::CustomBlockAdd()
{
	// null�̸� ����
	if (!mBlockEditorList)
		return;

	Block newBlock;
	int result[4] = {};
	bool BlockCreate[16] = {};

	std::cout << "������ ����� ǥ�����ּ���. \n(0:����� | 1:��ϻ��� | �ִ� 4x4 16ĭ) \n";
	
	for (int i = 0; i < 4; i++)
	{
		std::cout << i << ". 4�ڸ� �Է����ּ���. : ";
		std::cin >> result[i];
		std::cout << std::endl;
	}
	
	for (int i = 0; i < 16; i++)
	{
		BlockCreate[i] = result[i] > 0;
	}

	mBlockEditorList->GetBlockList().push_back(newBlock);

	
}
