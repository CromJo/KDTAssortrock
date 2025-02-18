#pragma once

#include "../GameInfo.h"

// MeshManager�� AssetManager�� ������ �ְ�,
// MeshLoad�� �ʿ��ϸ� ���⼭ Return���ִ� 
// Manager Container������ �����Ѵ�.
class CAssetManager
{
private:
	class CMeshManager* mMeshManager = nullptr;

public:
	class CMeshManager* GetMeshManager() const
	{
		return mMeshManager;
	}

public:
	bool Init();

	DECLARE_SINGLE(CAssetManager);
};

