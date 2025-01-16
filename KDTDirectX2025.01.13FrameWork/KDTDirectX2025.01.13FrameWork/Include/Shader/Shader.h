#pragma once
#include "../Share/Object.h"


// 그래픽 처리를 위한 그래픽 쉐이더
// 컴퓨터 쉐이더
class CShader abstract : public CObject
{
	friend class CShaderManager;

protected:
	CShader();
	virtual ~CShader();

public:
	// 순수가상함수 : 무조건적인 자식에서 재정의 요청기능
	virtual bool Init() = 0;
	virtual void SetShader() = 0;
};

