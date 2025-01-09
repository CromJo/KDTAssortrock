#pragma once
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
	CBlockEditor();
	CBlockEditor(class CBlock* mBlock) : mBlockEditorList(mBlock) {}
	~CBlockEditor() {}

private:
	CBlock* mBlockEditorList;

public:
	void CustomBlockAdd();

};