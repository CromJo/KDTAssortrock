#pragma once

#include "ConstantBuffer.h"
 
class CConstantBufferData abstract
{
public:
	CConstantBufferData();
	CConstantBufferData(const CConstantBufferData& Data);
	CConstantBufferData(CConstantBufferData&& Data);
	virtual ~CConstantBufferData();

protected:
	// 상수버퍼 한개를 반드시 들고있어야한다.
	// ConstantBuffer는 Object를 상속받았기 때문에,
	// 레퍼런스 카운터 관리가 필요하다.
	// 버퍼 자체는 여러개만들 필요가없고,
	// 데이터만 따로 들고있으면 된다.
	CSharedPointer<CConstantBuffer> mBuffer;

protected:
	void SetConstantBuffer(const std::string& Name);

public:
	virtual bool Init() = 0;
	virtual void UpdateBuffer() = 0;
	virtual CConstantBufferData* Clone() = 0;
};

