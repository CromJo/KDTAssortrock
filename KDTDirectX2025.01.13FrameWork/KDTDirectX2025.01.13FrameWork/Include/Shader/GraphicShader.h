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
	// 레지스터 이름, 번호 등의
	ID3D11InputLayout* mInputLayout = nullptr;

	// 레지스터 지정을 위한 구조체
	// INPUT_ELEMENT_DESC : 레이아웃 요소하나를 표시하는 기능 
	std::vector<D3D11_INPUT_ELEMENT_DESC> mVectorDesc;
	int mInputLayoutSize = 0;

	ID3D11VertexShader* mVertexShader = nullptr;
	// VertexShader 코드를 컴파일하고 바이트 코드를 저장하기 위한 버퍼
	ID3DBlob* mVertexShaderBlob = nullptr;

	ID3D11PixelShader* mPixelShader = nullptr;
	// VertexShader 코드를 컴파일하고 바이트 코드를 저장하기 위한 버퍼
	ID3DBlob* mPixelShaderBlob = nullptr;;

	ID3D11HullShader* mHullShader = nullptr;
	// VertexShader 코드를 컴파일하고 바이트 코드를 저장하기 위한 버퍼
	ID3DBlob* mHullShaderBlob = nullptr;;

	ID3D11DomainShader* mDomainShader = nullptr;
	// VertexShader 코드를 컴파일하고 바이트 코드를 저장하기 위한 버퍼
	ID3DBlob* mDomainShaderBlob = nullptr;;

	ID3D11GeometryShader* mGeometryShader = nullptr;
	// VertexShader 코드를 컴파일하고 바이트 코드를 저장하기 위한 버퍼
	ID3DBlob* mGeometryShaderBlob = nullptr;;


public:
	// 순수가상함수 : 무조건적인 자식에서 재정의 요청기능
	virtual bool Init();
	// final 이게 마지막 재정의라는 뜻
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

