#include "TextureManager.h"
#include "Texture.h"

CTextureManager::CTextureManager()
{
}

CTextureManager::~CTextureManager()
{
}

bool CTextureManager::Init()
{

	return true;
}

class CTexture* CTextureManager::FindTexture(const std::string& Name)
{
	auto iter = mTextureMap.find(Name);

	if (iter == mTextureMap.end())
	{
		return nullptr;
	}
	return iter->second;
}

void CTextureManager::ReleaseTexture(class CAsset* Texture)
{
	auto iter = mTextureMap.find(Texture->GetName());

	if (iter != mTextureMap.end())
	{
		// 다른데서 사용하고 있을때 해당 에셋을 지우면 안되니까!
		if (iter->second->GetRefCount() == 1)
		{
			mTextureMap.erase(iter);
		}
	}
}
