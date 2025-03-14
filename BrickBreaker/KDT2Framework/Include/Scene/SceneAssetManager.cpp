#include "SceneAssetManager.h"
#include "../Asset/Mesh/Mesh.h"
#include "../Asset/Texture/Texture.h"
#include "../Asset/Texture/TextureManager.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Mesh/MeshManager.h"
#include "../Asset/Material/Material.h"
#include "../Asset/Material/MaterialManager.h"

CSceneAssetManager::CSceneAssetManager()
{
}

CSceneAssetManager::~CSceneAssetManager()
{
	auto	iter = mAssetMap.begin();

	for (; iter != mAssetMap.end();)
	{
		CAsset* Asset = iter->second;

		iter = mAssetMap.erase(iter);

		CAssetManager::GetInst()->ReleaseAsset(Asset);
	}
}

bool CSceneAssetManager::Init()
{
	return true;
}

bool CSceneAssetManager::CreateMesh(
	const std::string& Name, void* VertexData, 
	int Size, int Count, D3D11_USAGE VertexUsage,
	D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IndexData,
	int IndexSize, int IndexCount, DXGI_FORMAT Fmt,
	D3D11_USAGE IndexUsage)
{
	if (!CAssetManager::GetInst()->GetMeshManager()->CreateMesh(
		Name, VertexData, Size, Count, VertexUsage,
		Primitive, IndexData, IndexSize, IndexCount,
		Fmt, IndexUsage))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter != mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name, iter->second));
	}

	return true;
}

CMesh* CSceneAssetManager::FindMesh(const std::string& Name)
{
	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		CMesh* Mesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh(Name);

		if (!Mesh)
			return nullptr;

		mAssetMap.insert(std::make_pair(Name, Mesh));
		
		return Mesh;
	}

	return dynamic_cast<CMesh*>(iter->second.Get());
}

bool CSceneAssetManager::LoadTexture(
	const std::string& Name, const TCHAR* FileName)
{
	if (!CAssetManager::GetInst()->GetTextureManager()->LoadTexture(
		Name, FileName))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name, iter->second));
	}

	return true;
}

bool CSceneAssetManager::LoadTextureFullPath(
	const std::string& Name, const TCHAR* FullPath)
{
	if (!CAssetManager::GetInst()->GetTextureManager()->LoadTextureFullPath(
		Name, FullPath))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name, iter->second));
	}

	return true;
}

CTexture* CSceneAssetManager::FindTexture(
	const std::string& Name)
{
	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		CTexture* Texture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);

		if (!Texture)
			return nullptr;

		mAssetMap.insert(std::make_pair(Name, Texture));

		return Texture;
	}

	return dynamic_cast<CTexture*>(iter->second.Get());
}

bool CSceneAssetManager::CreateMaterial(
	const std::string& Name)
{
	if (!CAssetManager::GetInst()->GetMaterialManager()->CreateMaterial(
		Name))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name, iter->second));
	}

	return true;
}

CMaterial* CSceneAssetManager::FindMaterial(const std::string& Name)
{
	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		CMaterial* Material = CAssetManager::GetInst()->GetMaterialManager()->FindMaterial(Name);

		if (!Material)
			return nullptr;

		mAssetMap.insert(std::make_pair(Name, Material));

		return Material;
	}

	return dynamic_cast<CMaterial*>(iter->second.Get());
}
