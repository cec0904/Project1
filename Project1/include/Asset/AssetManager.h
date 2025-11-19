#pragma once

#include "../GameInfo.h"

class CAssetManager
{
	DECLARE_SINGLETONE(CAssetManager)
private:
	class CMeshManager* mMeshManager = nullptr;
	class CTextureManager* mTextureManager = nullptr;

public:
	class CMeshManager* GetMeshManager() const
	{
		return mMeshManager;
	}

public:
	bool Init();
	void ReleaseAsset(class CAsset* Asset);

};

