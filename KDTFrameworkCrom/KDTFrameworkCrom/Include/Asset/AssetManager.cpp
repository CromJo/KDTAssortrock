#include "AssetManager.h"
#include "Mesh/MeshManager.h"

DEFINITION_SINGLE(CAssetManager)

CAssetManager::CAssetManager()
{
	
}

CAssetManager::~CAssetManager()
{
	SAFE_DELETE(mMeshManager)
}

bool CAssetManager::Init()
{
	mMeshManager = new CMeshManager;

	// MeshManager가 존재하지않으면
	// AssetManager 초기화 실패
	if (!mMeshManager->Init())
		return false;

	return true;
}
