#include "SceneAssetManager.h"
#include "../Asset/Mesh/Mesh.h"
#include "../Asset/Texture/Texture.h"
#include "../Asset/Texture/TextureManager.h"
#include "../Asset/AssetManager.h"
#include "../Asset/Mesh/MeshManager.h"
#include "../Asset/Material/Material.h"
#include "../Asset/Material/MaterialManager.h"
#include "../Asset/Animation/Animation2DData.h"
#include "../Asset/Animation/Animation2DManager.h"
#include "../Asset/Sound/Sound.h"
#include "../Asset/Sound/SoundManager.h"
#include "../Asset/Font/Font.h"
#include "../Asset/Font/FontCollection.h"
#include "../Asset/Font/FontManager.h"

CSceneAssetManager::CSceneAssetManager()
{
}

/// <summary>
/// 메모리 해제
/// </summary>
CSceneAssetManager::~CSceneAssetManager()
{
	auto	iter = mAssetMap.begin();

	for (; iter != mAssetMap.end();)
	{
		CAsset* Asset = iter->second;

		iter = mAssetMap.erase(iter);

		// Asset에서 빌려온 데이터들 SceneAsset에서 해제
		CAssetManager::GetInst()->ReleaseAsset(Asset);
	}
}

bool CSceneAssetManager::Init()
{
	return true;
}

/// <summary>
/// 메쉬를 생성하는 기능
/// 1. 에셋 보물상자에 메쉬를 찾아서 추가한다.
/// </summary>
/// <param name="Name"></param>
/// <param name="VertexData"></param>
/// <param name="Size"></param>
/// <param name="Count"></param>
/// <param name="VertexUsage"></param>
/// <param name="Primitive"></param>
/// <param name="IndexData"></param>
/// <param name="IndexSize"></param>
/// <param name="IndexCount"></param>
/// <param name="Fmt"></param>
/// <param name="IndexUsage"></param>
/// <returns></returns>
bool CSceneAssetManager::CreateMesh(
	const std::string& Name, void* VertexData, 
	int Size, int Count, D3D11_USAGE VertexUsage,
	D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IndexData,
	int IndexSize, int IndexCount, DXGI_FORMAT Fmt,
	D3D11_USAGE IndexUsage)
{
	// 에셋매니저에서 메쉬를 만들지 못하면 종료합니다.
	if (!CAssetManager::GetInst()->GetMeshManager()->CreateMesh(
		Name, VertexData, Size, Count, VertexUsage,
		Primitive, IndexData, IndexSize, IndexCount,
		Fmt, IndexUsage))
		return false;

	// 메쉬를 만들었다면 이름으로 찾습니다.
	auto	iter = mAssetMap.find(Name);

	// 존재하는 이름이면
	if (iter != mAssetMap.end())
	{
		// 그 이름으로 에셋을 추가하고 찾습니다.
		mAssetMap.insert(std::make_pair(Name, 
			CAssetManager::GetInst()->GetMeshManager()->FindMesh(Name)));
	}

	return true;
}

/// <summary>
/// 에셋매니저에서 메쉬 찾아보는 기능
/// 1. 있으면 Asset모음집에 추가해준다.
/// 2. 없으면 형변환 시켜서 오브젝트 넣어준다.
/// </summary>
/// <param name="Name"></param>
/// <returns></returns>
CMesh* CSceneAssetManager::FindMesh(const std::string& Name)
{
	// Asset에서 key값이 있는지 찾아본다.
	auto	iter = mAssetMap.find(Name);

	// 있다면,
	if (iter == mAssetMap.end())
	{
		// Asset에서 메쉬를 찾아봅니다.
		CMesh* Mesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh(Name);

		// 없으면 종료하셔
		if (!Mesh)
			return nullptr;

		// 있다면
		// 추가...해줘야겠지..? 
		mAssetMap.insert(std::make_pair(Name, Mesh));
		
		return Mesh;
	}

	// 없다면
	// iter를 메쉬로 형변환 시켜서 오브젝트를 가지고옴
	return dynamic_cast<CMesh*>(iter->second.Get());
}

#pragma region 텍스쳐 불러오는 기능 모음
/// <summary>
/// 씬의 필요한 텍스쳐 불러오는 기능
/// 파일명으로 찾음
/// </summary>
/// <param name="Name"></param>
/// <param name="FileName"></param>
/// <returns></returns>
bool CSceneAssetManager::LoadTexture(
	const std::string& Name, const TCHAR* FileName)
{
	// 에셋 다라이에서 텍스쳐를 불러온다.
	// 못불러오면 "그럼 죽어"
	if (!CAssetManager::GetInst()->GetTextureManager()->LoadTexture(
		Name, FileName))
		return false;

	// Asset 다라이에서 Name으로 찾아본다이
	auto	iter = mAssetMap.find(Name);

	// 있으면 에셋 다라이에 텍스쳐 넣을게~
	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name, 
			CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name)));
	}

	return true;
}

/// <summary>
/// 씬에 필요한 텍스쳐 경로를 불러오는 기능
/// 경로로 불러옴
/// </summary>
/// <param name="Name"></param>
/// <param name="FullPath"></param>
/// <returns></returns>
bool CSceneAssetManager::LoadTextureFullPath(
	const std::string& Name, const TCHAR* FullPath)
{
	// 에셋 매니저에서 텍스쳐 경로로 불러오는것을 실패했다면 종료
	if (!CAssetManager::GetInst()->GetTextureManager()->LoadTextureFullPath(
		Name, FullPath))
		return false;

	// 불러왔다면 에셋 꾸러미에서 찾아
	auto	iter = mAssetMap.find(Name);

	// 다 똑같으니 그냥 이제 캔슬함
	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name, 
			CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name)));
	}

	return true;
}

/// <summary>
/// 텍스쳐 불러오는 기능
/// 파일명으로 불러옴
/// </summary>
/// <param name="Name"></param>
/// <param name="FileName"></param>
/// <returns></returns>
bool CSceneAssetManager::LoadTexture(
	const std::string& Name, 
	const std::vector<const TCHAR*>& FileName)
{
	if (!CAssetManager::GetInst()->GetTextureManager()->LoadTexture(
		Name, FileName))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name,
			CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name)));
	}

	return true;
}

/// <summary>
/// 텍스쳐 주소로 불러오는 기능
/// </summary>
/// <param name="Name"></param>
/// <param name="FullPath"></param>
/// <returns></returns>
bool CSceneAssetManager::LoadTextureFullPath(
	const std::string& Name, 
	const std::vector<const TCHAR*>& FullPath)
{
	if (!CAssetManager::GetInst()->GetTextureManager()->LoadTextureFullPath(
		Name, FullPath))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name,
			CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name)));
	}

	return true;
}

bool CSceneAssetManager::LoadTexture(
	const std::string& Name, const TCHAR* FileName, 
	const TCHAR* Ext, int Count)
{
	if (!CAssetManager::GetInst()->GetTextureManager()->LoadTexture(
		Name, FileName, Ext, Count))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name,
			CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name)));
	}

	return true;
}

#pragma endregion

/// <summary>
/// 텍스쳐 찾는 기능
/// </summary>
/// <param name="Name"></param>
/// <returns></returns>
CTexture* CSceneAssetManager::FindTexture(
	const std::string& Name)
{
	// 찾아서
	auto	iter = mAssetMap.find(Name);

	// 나온다면
	if (iter == mAssetMap.end())
	{
		// 텍스쳐를 찾고
		CTexture* Texture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);

		// 못 찾았으면 종료
		if (!Texture)
			return nullptr;

		// 찾았다면 키와 값을 꾸러미에 넣는다.
		mAssetMap.insert(std::make_pair(Name, Texture));

		// 텍스쳐 반환
		return Texture;
	}

	// 못찾았다면 iter의 오브젝트를 반환
	return dynamic_cast<CTexture*>(iter->second.Get());
}

/// <summary>
/// 머테리얼 생성하는 기능
/// </summary>
/// <param name="Name"></param>
/// <returns></returns>
bool CSceneAssetManager::CreateMaterial(
	const std::string& Name)
{
	// 마테리얼 생성이 안되면 종료
	if (!CAssetManager::GetInst()->GetMaterialManager()->CreateMaterial(
		Name))
		return false;

	// 생성되면 찾고
	auto	iter = mAssetMap.find(Name);

	// 존재하면
	if (iter == mAssetMap.end())
	{
		// 넣을게~
		mAssetMap.insert(std::make_pair(Name, 
			CAssetManager::GetInst()->GetMaterialManager()->FindMaterial(Name)));
	}

	return true;
}

/// <summary>
/// 마테리얼 찾는 기능
/// </summary>
/// <param name="Name"></param>
/// <returns></returns>
CMaterial* CSceneAssetManager::FindMaterial(const std::string& Name)
{
	// 찾고
	auto	iter = mAssetMap.find(Name);

	// 나오면
	if (iter == mAssetMap.end())
	{
		// 머테리얼을 찾는다.
		CMaterial* Material = CAssetManager::GetInst()->GetMaterialManager()->FindMaterial(Name);

		// 안나오면 종료
		if (!Material)
			return nullptr;

		// 나오면 삽입
		mAssetMap.insert(std::make_pair(Name, Material));

		// 그리고 반환
		return Material;
	}

	// 안나왔으면 오브젝트 반환
	return dynamic_cast<CMaterial*>(iter->second.Get());
}

/// <summary>
/// 도저히 못해먹겠다 Create, Find, Load는 다 거기서 거기임
/// </summary>
/// <param name="Name"></param>
/// <returns></returns>
bool CSceneAssetManager::CreateAnimation(
	const std::string& Name)
{
	if (!CAssetManager::GetInst()->GetAnimationManager()->CreateAnimation(
		Name))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name,
			CAssetManager::GetInst()->GetAnimationManager()->FindAnimation(Name)));
	}

	return true;
}

#pragma region 애니메이션 텍스쳐 세팅 기능 모음
bool CSceneAssetManager::SetAnimationTextureType(
	const std::string& Name, EAnimationTextureType Type)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->SetAnimationTextureType(Type);

	return true;
}

bool CSceneAssetManager::SetAnimationTexture(const std::string& Name,
	CTexture* Texture)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->SetTexture(Texture);

	return true;
}

bool CSceneAssetManager::SetAnimationTexture(const std::string& Name,
	const std::string& TextureName, const TCHAR* FileName)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->SetTexture(TextureName, FileName);

	return true;
}

bool CSceneAssetManager::SetAnimationTexture(
	const std::string& Name, 
	const std::string& TextureName, 
	std::vector<const TCHAR*> FileName)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->SetTexture(TextureName, FileName);

	return true;
}

bool CSceneAssetManager::SetAnimationTexture(
	const std::string& Name, 
	const std::string& TextureName, 
	const TCHAR* FileName, const TCHAR* Ext, int Count)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->SetTexture(TextureName, FileName, Ext,
		Count);

	return true;
}

bool CSceneAssetManager::SetAnimationTextureFullPath(
	const std::string& Name, 
	const std::string& TextureName,
	const TCHAR* FullPath)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->SetTextureFullPath(TextureName, FullPath);

	return true;
}

bool CSceneAssetManager::SetAnimationTextureFullPath(
	const std::string& Name,
	const std::string& TextureName, 
	std::vector<const TCHAR*> FullPath)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->SetTextureFullPath(TextureName, FullPath);

	return true;
}
#pragma endregion

#pragma region 애니메이션 프레임 관련 기능 모음
/// <summary>
/// 애니메이션 프레임 추가하는 기능
/// 1. 시작지점
/// 2. 이미지의 X, Y 좌표
/// </summary>
/// <param name="Name"></param>
/// <param name="Start"></param>
/// <param name="Size"></param>
/// <returns></returns>
bool CSceneAssetManager::AddAnimationFrame(
	const std::string& Name, const FVector2D& Start, 
	const FVector2D& Size)
{
	// 애니메이션 찾고
	CAnimation2DData* Animation = FindAnimation(Name);

	// 없으면 종료
	if (!Animation)
		return false;

	// 존재하면 애니메이션 한부분 추가
	Animation->AddFrame(Start, Size);

	return true;
}

/// <summary>
/// 애니메이션 프레임 추가 기능
/// 1 & 2. 그림을 그려줄 시작 X, Y좌표
/// 3 & 4. 그림을 범위를 끝내줄 X, Y좌표
/// </summary>
/// <param name="Name"></param>
/// <param name="StartX"></param>
/// <param name="StartY"></param>
/// <param name="SizeX"></param>
/// <param name="SizeY"></param>
/// <returns></returns>
bool CSceneAssetManager::AddAnimationFrame(
	const std::string& Name, float StartX, float StartY,
	float SizeX, float SizeY)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->AddFrame(StartX, StartY, SizeX, SizeY);

	return true;
}

/// <summary>
/// 애니메이션 프레임 장면 추가
/// 1. 이름으로 찾고
/// 2. 몇장인지 알려주고
/// 3. 어디서부터
/// 4. 어디까지 그려줄건지 범위 지정
/// </summary>
/// <param name="Name"></param>
/// <param name="Count"></param>
/// <param name="Start"></param>
/// <param name="Size"></param>
/// <returns></returns>
bool CSceneAssetManager::AddAnimationFrameCount(
	const std::string& Name, int Count, 
	const FVector2D& Start, const FVector2D& Size)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->AddFrameCount(Count, Start, Size);

	return true;
}

/// <summary>
/// 애니메이션 프레임 장면추가 이하생략
/// </summary>
/// <param name="Name"></param>
/// <param name="Count"></param>
/// <param name="StartX"></param>
/// <param name="StartY"></param>
/// <param name="SizeX"></param>
/// <param name="SizeY"></param>
/// <returns></returns>
bool CSceneAssetManager::AddAnimationFrameCount(
	const std::string& Name, int Count, float StartX,
	float StartY, float SizeX, float SizeY)
{
	CAnimation2DData* Animation = FindAnimation(Name);

	if (!Animation)
		return false;

	Animation->AddFrameCount(Count, StartX, StartY,
		SizeX, SizeY);

	return true;
}
#pragma endregion

/// <summary>
/// 애니메이션 찾는 함수
/// </summary>
/// <param name="Name"></param>
/// <returns></returns>
CAnimation2DData* CSceneAssetManager::FindAnimation(
	const std::string& Name)
{
	// 이름으로 찾고
	auto	iter = mAssetMap.find(Name);

	// 존재하면
	if (iter == mAssetMap.end())
	{
		// Name으로 찾아서 넣어주는데
		CAnimation2DData* Animation = 
			CAssetManager::GetInst()->GetAnimationManager()->FindAnimation(Name);

		// 없으면 종료하고
		if (!Animation)
			return nullptr;

		// 있으면 넣어주고
		mAssetMap.insert(std::make_pair(Name, Animation));

		// 반환도 해줌
		return Animation;
	}

	// 형변환 해서 바꿔서 반환해줌
	return dynamic_cast<CAnimation2DData*>(iter->second.Get());
}

#pragma region 사운드 파일명 / 파일경로 / 그냥찾기 모음
/// <summary>
/// 사운드 불러오는 기능
/// 불러오기 성공/실패를 반환
/// </summary>
/// <param name="Name"></param>
/// <param name="GroupName"></param>
/// <param name="Loop"></param>
/// <param name="FileName"></param>
/// <returns></returns>
bool CSceneAssetManager::LoadSound(const std::string& Name, 
	const std::string& GroupName, bool Loop, const char* FileName)
{
	if (!CAssetManager::GetInst()->GetSoundManager()->LoadSound(
		Name, GroupName, Loop, FileName))
		return false;

	// 찾아보고
	auto	iter = mAssetMap.find(Name);

	// 있으면
	if (iter == mAssetMap.end())
	{
		// 삽입 
		mAssetMap.insert(std::make_pair(Name,
			CAssetManager::GetInst()->GetSoundManager()->FindSound(Name)));
	}

	// 로드 성공
	return true;
}

/// <summary>
/// 경로로 사운드 불러오기 이하생략
/// </summary>
/// <param name="Name"></param>
/// <param name="GroupName"></param>
/// <param name="Loop"></param>
/// <param name="FullPath"></param>
/// <returns></returns>
bool CSceneAssetManager::LoadSoundFullPath(const std::string& Name,
	const std::string& GroupName, bool Loop, const char* FullPath)
{
	if (!CAssetManager::GetInst()->GetSoundManager()->LoadSoundFullPath(
		Name, GroupName, Loop, FullPath))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name,
			CAssetManager::GetInst()->GetSoundManager()->FindSound(Name)));
	}

	return true;
}

CSound* CSceneAssetManager::FindSound(const std::string& Name)
{
	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		CSound* Sound =
			CAssetManager::GetInst()->GetSoundManager()->FindSound(Name);

		if (!Sound)
			return nullptr;

		mAssetMap.insert(std::make_pair(Name, Sound));

		return Sound;
	}

	return dynamic_cast<CSound*>(iter->second.Get());
}
#pragma endregion

#pragma region 폰트 불러오기
bool CSceneAssetManager::LoadFont(const std::string& Name, 
	const TCHAR* FontName, int Weight, float FontSize, 
	const TCHAR* LocalName, int Stretch)
{
	if (!CAssetManager::GetInst()->GetFontManager()->LoadFont(
		Name, FontName, Weight, FontSize, LocalName, Stretch))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name,
			CAssetManager::GetInst()->GetFontManager()->FindFont(Name)));
	}

	return true;
}

bool CSceneAssetManager::LoadFontCollection(const std::string& Name, 
	const TCHAR* FileName)
{
	if (!CAssetManager::GetInst()->GetFontManager()->LoadFontCollection(
		Name, FileName))
		return false;

	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		mAssetMap.insert(std::make_pair(Name,
			CAssetManager::GetInst()->GetFontManager()->FindFontCollection(Name)));
	}

	return true;
}
#pragma endregion

const TCHAR* CSceneAssetManager::GetFontFaceName(const std::string& CollectionName)
{
	return CAssetManager::GetInst()->GetFontManager()->GetFontFaceName(CollectionName);
}

#pragma region 폰트 색상 (알파값 포함)
bool CSceneAssetManager::CreateFontColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return CAssetManager::GetInst()->GetFontManager()->CreateFontColor(r, g, b, a);
}

bool CSceneAssetManager::CreateFontColor(const FVector4D& Color)
{
	return CAssetManager::GetInst()->GetFontManager()->CreateFontColor(Color);
}
#pragma endregion

#pragma region 폰트 관련 찾는 기능 모음
CFont* CSceneAssetManager::FindFont(const std::string& Name)
{
	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		CFont* Font = CAssetManager::GetInst()->GetFontManager()->FindFont(Name);

		if (!Font)
			return nullptr;

		mAssetMap.insert(std::make_pair(Name, Font));

		return Font;
	}

	return dynamic_cast<CFont*>(iter->second.Get());
}

CFontCollection* CSceneAssetManager::FindFontCollection(
	const std::string& Name)
{
	auto	iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		CFontCollection* Font = CAssetManager::GetInst()->GetFontManager()->FindFontCollection(Name);

		if (!Font)
			return nullptr;

		mAssetMap.insert(std::make_pair(Name, Font));

		return Font;
	}

	return dynamic_cast<CFontCollection*>(iter->second.Get());
}

ID2D1SolidColorBrush* CSceneAssetManager::FindFontColor(
	unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	return CAssetManager::GetInst()->GetFontManager()->FindFontColor(r, g, b, a);
}

/// <summary>
/// 폰트 불러오는 기능
/// </summary>
/// <param name="Color"></param>
/// <returns></returns>
ID2D1SolidColorBrush* CSceneAssetManager::FindFontColor(
	const FVector4D& Color)
{
	return CAssetManager::GetInst()->GetFontManager()->FindFontColor(Color);
}
#pragma endregion