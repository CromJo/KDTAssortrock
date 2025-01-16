#pragma once
#include "../GameInfo.h"
#include "GraphicShader.h"

class CShaderManager
{
private:
	std::unordered_map<std::string, CSharedPointer> mShaderMap;

public:
	bool Init();

	class CGraphicShader* FindShader(const std::string& Name);

	template<typename T>
	bool CreateShader(const std::string& Name)
	{
		CGraphicShader* Shader = FindShader(Name);

		if (Shader)
			return true;

		Shader = new T;

		if (!Shader->Init())
		{
			SAFE_DELETE(Shader);

			return false;
		}

		mShaderMap.insert(std::make_pair(Name, Shader));

		return true;
	}

	DECLARE_SINGLE(CShaderManager)
};

