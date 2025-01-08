#pragma once
#include "Block.h"
#include <vector>
#include "GameInfo.h"

enum class EBlockMenu
{
	None,			// ȣ��(�ƹ��͵� �ƴ� ��)
	BlockAdd,		// ��� �����
	BlockDelete,	// ���� ��� ����
	BlockModify,	// ������� ��� ����
	BlockOutput,	// ��� ������� ��¿�
	BlockSave,		// ���� ���� ��� ����
	BlockLoad,		// ���� ���� ��� �ҷ�����
	Exit,			// �ڷΰ���
};

class CBlockEditor
{
public:
	CBlockEditor() : mBlockEditorList(nullptr) {}
	CBlockEditor(CBlock* mBlock) : mBlockEditorList(mBlock) {}
	~CBlockEditor() {}

private:
	CBlock* mBlockEditorList;

public:
	void CustomBlockAdd();

};