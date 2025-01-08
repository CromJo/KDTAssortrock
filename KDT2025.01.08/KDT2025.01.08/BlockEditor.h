#pragma once
#include "Block.h"
#include <vector>
#include "GameInfo.h"

enum class EBlockMenu
{
	None,			// 호드(아무것도 아님 ㅎ)
	BlockAdd,		// 블록 만들기
	BlockDelete,	// 만든 블록 삭제
	BlockModify,	// 만들었던 블록 수정
	BlockOutput,	// 어떻게 생겼는지 출력용
	BlockSave,		// 내가 만든 블록 저장
	BlockLoad,		// 내가 만든 블록 불러오기
	Exit,			// 뒤로가기
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