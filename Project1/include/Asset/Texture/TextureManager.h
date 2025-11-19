#pragma once
#include "../../GameInfo.h"

class CTextureManager
{
	friend class CAssetManager;

private:
	CTextureManager();
	~CTextureManager();

private:
	unordered_map<string, CSharedPtr<class CTexture>> mTextureMap;

public:
	bool Init();

	class CTexture* FindTexture(const string& Name);
	void ReleaseTexture(class CAsset* Texture);


};

