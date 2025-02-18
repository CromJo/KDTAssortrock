#pragma once

#include "../GameInfo.h"

// MeshManager는 AssetManager가 가지고 있고,
// MeshLoad가 필요하면 여기서 Return해주는 
// Manager Container역할을 수행한다.
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

