#pragma once
#include "../Share/Object.h"


// �׷��� ó���� ���� �׷��� ���̴�
// ��ǻ�� ���̴�
class CShader abstract : public CObject
{
	friend class CShaderManager;

protected:
	CShader();
	virtual ~CShader();

public:
	// ���������Լ� : ���������� �ڽĿ��� ������ ��û���
	virtual bool Init() = 0;
	virtual void SetShader() = 0;
};

