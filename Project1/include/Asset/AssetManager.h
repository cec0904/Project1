#pragma once

#include "../GameInfo.h"

class CAssetManager
{
	DECLARE_SINGLETONE(CAssetManager)
private:
	class CMeshManager* mMeshManager = nullptr;
	class CTextureManager* mTextureManager = nullptr;
	class CMaterialManager* mMaterialManager = nullptr;
public:
	class CMeshManager* GetMeshManager() const
	{
		return mMeshManager;
	}

	class CTextureManager* GetTextureManager() const
	{
		return mTextureManager;
	}

	class CMaterialManager* GetMaterialManager() const
	{
		return mMaterialManager;
	}

public:
	bool Init();
	void ReleaseAsset(class CAsset* Asset);

};

