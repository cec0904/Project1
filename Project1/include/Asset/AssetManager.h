#pragma once

#include "../GameInfo.h"

class CAssetManager
{
	DECLARE_SINGLETONE(CAssetManager)
private:
	class CMeshManager* mMeshManager = nullptr;

public:
	class CMeshManager* GetMeshManager() const
	{
		return mMeshManager;
	}

public:
	bool Init();

};

