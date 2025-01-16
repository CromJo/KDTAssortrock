#pragma once
#include "../GameInfo.h"
#include "Shader.h"

class CGraphicShader : public CShader
{
	friend class CShaderManager;

protected:
	CGraphicShader();
	virtual ~CGraphicShader();

private:
	// �������� �̸�, ��ȣ ����
	ID3D11InputLayout* mInputLayout = nullptr;

	// �������� ������ ���� ����ü
	// INPUT_ELEMENT_DESC : ���̾ƿ� ����ϳ��� ǥ���ϴ� ��� 
	std::vector<D3D11_INPUT_ELEMENT_DESC> mVectorDesc;
	int mInputLayoutSize = 0;

	ID3D11VertexShader* mVertexShader = nullptr;
	// VertexShader �ڵ带 �������ϰ� ����Ʈ �ڵ带 �����ϱ� ���� ����
	ID3DBlob* mVertexShaderBlob = nullptr;

	ID3D11PixelShader* mPixelShader = nullptr;
	// VertexShader �ڵ带 �������ϰ� ����Ʈ �ڵ带 �����ϱ� ���� ����
	ID3DBlob* mPixelShaderBlob = nullptr;;

	ID3D11HullShader* mHullShader = nullptr;
	// VertexShader �ڵ带 �������ϰ� ����Ʈ �ڵ带 �����ϱ� ���� ����
	ID3DBlob* mHullShaderBlob = nullptr;;

	ID3D11DomainShader* mDomainShader = nullptr;
	// VertexShader �ڵ带 �������ϰ� ����Ʈ �ڵ带 �����ϱ� ���� ����
	ID3DBlob* mDomainShaderBlob = nullptr;;

	ID3D11GeometryShader* mGeometryShader = nullptr;
	// VertexShader �ڵ带 �������ϰ� ����Ʈ �ڵ带 �����ϱ� ���� ����
	ID3DBlob* mGeometryShaderBlob = nullptr;;


public:
	// ���������Լ� : ���������� �ڽĿ��� ������ ��û���
	virtual bool Init();
	// final �̰� ������ �����Ƕ�� ��
	virtual void SetShader() final;

public:
	void AddInputLayoutDesc(const char* Semantic, unsigned int SemanticIndex,
		DXGI_FORMAT Format, unsigned int InputSlot, unsigned int Size,
		D3D11_INPUT_CLASSIFICATION InputSlotClass,
		unsigned int InstanceDataStepRate);

	bool CreateInputLayout();
	bool LoadVertexShader(const char* EntryName, const TCHAR* FileName);
	bool LoadHullShader(const char* EntryName, const TCHAR* FileName);
	bool LoadPixelShader(const char* EntryName, const TCHAR* FileName);
	bool LoadDomainShader(const char* EntryName, const TCHAR* FileName);
	bool LoadGeometryShader(const char* EntryName, const TCHAR* FileName);
};

