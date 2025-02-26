#pragma once

#include "../GameInfo.h"
#include "Shader.h"

class CShaderManager
{
private:
	std::unordered_map<std::string, CSharedPointer<CShader>> mShaderMap;
	std::unordered_map<std::string, CSharedPointer<class CConstantBuffer>> mCBufferMap;

public:
	bool Init();
	CShader* FindShader(const std::string& Name);
	void ReleaseShader(const std::string& Name);

	template<typename T>
	bool CreateShader(const std::string& Name)
	{
		CShader* Shader = FindShader(Name);

		if (Shader)
			return true;

		Shader = new T;

		// 생설 실패 시
		if (!Shader->Init())
		{
			// 동적할당 제거
			SAFE_DELETE(Shader)

				return false;
		}

		// 생성 성공 시
		mShaderMap.insert(std::make_pair(Name, Shader));

		return true;
	}

public:

	bool CreateConstantBuffer(const std::string& Name,
		int Size, int Register,
		int ShadowBufferType = EShaderBufferType::Graphic);
	CConstantBuffer* FindCBuffer(const std::string& Name);
	void ReleaseCBuffer(const std::string& Name);

	DECLARE_SINGLE(CShaderManager)
};
