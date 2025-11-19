#include "AssetManager.h"

#include "../Asset/Asset.h"
#include "Mesh/MeshManager.h"
#include "Texture/TextureManager.h"

CAssetManager::CAssetManager()
{

}
CAssetManager::~CAssetManager()
{
	SAFE_DELETE(mMeshManager);
}

bool CAssetManager::Init()
{
	// 메쉬를 관리
	mMeshManager = new CMeshManager;

	if (!mMeshManager->Init())
	{
		return false;
	}

	// 이미지 텍스쳐
	// 사운드, 이펙트 등 다양한 리소스들을 관리 할 수도 있다.

	return true;

}

void CAssetManager::ReleaseAsset(CAsset* Asset)
{
	switch (Asset->GetAssetType())
	{
	case EAssetType::Mesh:
		mMeshManager->ReleaseMesh(Asset);
		break;
	case EAssetType::Texture:
		mTextureManager->ReleaseTexture(Asset);
		break;
	}
}
