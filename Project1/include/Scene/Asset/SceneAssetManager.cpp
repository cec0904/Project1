#include "SceneAssetManager.h"

#include "../../Asset/Asset.h"
#include "../../Asset/AssetManager.h"
#include "../../Asset/Mesh/Mesh.h"
#include "../../Asset/Mesh/MeshManager.h"
#include "../../Asset/Texture/TextureManager.h"
#include "../../Asset/Texture/Texture.h"
#include "../../Asset/Material/Material.h"
#include "../../Asset/Material/MaterialManager.h"

CSceneAssetManager::CSceneAssetManager()
{
}

CSceneAssetManager::~CSceneAssetManager()
{
	auto iter = mAssetMap.begin();

	for (; iter != mAssetMap.end();)
	{
		CAsset* Asset = iter->second;
		iter = mAssetMap.erase(iter);

		//릴리즈 따로 해줘야할거같다. 
		CAssetManager::GetInst()->ReleaseAsset(Asset);
	}
}

bool CSceneAssetManager::Init()
{

	return true;
}

bool CSceneAssetManager::CreateMesh(const string& Name, void* VertexData, int Size, int Count,
	D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitiv, void* IndexData, int IndexSize, int IndexCount,
	DXGI_FORMAT Fmt, D3D11_USAGE IndexUsage)
{
	if (!CAssetManager::GetInst()->GetMeshManager()->CreateMesh(Name, VertexData, Size, Count, VertexUsage, Primitiv, IndexData, IndexSize, IndexCount, Fmt, IndexUsage))
	{
		return false;
	}

	auto iter = mAssetMap.find(Name);

	if (iter != mAssetMap.end())
	{
		
		mAssetMap.insert(make_pair(Name, iter->second));
	}

	return true;
}

bool CSceneAssetManager::LoadTexture(const string& Name, const TCHAR* FileName)
{
	if (!CAssetManager::GetInst()->GetTextureManager()->LoadTexture(Name, FileName))
	{
		return false;
	}

	auto iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		
		mAssetMap.insert(make_pair(Name, iter->second));
	}

	return true;
}

bool CSceneAssetManager::LoadTextureFullPath(const string& Name, const TCHAR* FullPath)
{
	if (!CAssetManager::GetInst()->GetTextureManager()->LoadTextureFullPath(Name, FullPath))
	{
		return false;
	}

	auto iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		
		mAssetMap.insert(make_pair(Name, iter->second));
	}

	return true;
}

bool CSceneAssetManager::CreateMaterial(const string& Name)
{
	if (!CAssetManager::GetInst()->GetMaterialManager()->CreateMaterial(Name))
	{
		return false;
	}

	auto iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		//일부러 터짐
		//assert(0);
		mAssetMap.insert(make_pair(Name, iter->second));
	}

	return true;
}

class CMaterial* CSceneAssetManager::FindMaterial(const string& Name)
{
	auto iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		CMaterial* Material = CAssetManager::GetInst()->GetMaterialManager()->FindMaterial(Name);

		if (!Material)
		{
			return nullptr;
		}

		mAssetMap.insert(make_pair(Name, Material));

		return Material;
	}

	return dynamic_cast<CMaterial*>(iter->second.Get());
}

class CTexture* CSceneAssetManager::FindTexture(const string& Name)
{
	auto iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		CTexture* Texture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);

		if (!Texture)
		{
			return nullptr;
		}

		mAssetMap.insert(make_pair(Name, Texture));
		return Texture;
	}

	return dynamic_cast<CTexture*>(iter->second.Get());
}

class CMesh* CSceneAssetManager::FindMesh(const string& Name)
{
	auto iter = mAssetMap.find(Name);

	if (iter == mAssetMap.end())
	{
		CMesh* Mesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh(Name);

		if (!Mesh)
		{
			return nullptr;
		}

		mAssetMap.insert(make_pair(Name, Mesh));
		return Mesh;
	}

	return dynamic_cast<CMesh*>(iter->second.Get());
}
