#include "Material.h"

#include "../../Scene/Scene.h"
#include "../Texture/Texture.h"
#include "../../Shader/ShaderManager.h"
#include "../AssetManager.h"
#include "../../Scene/Asset/SceneAssetManager.h"
#include "../Texture/TextureManager.h"

CMaterial::CMaterial()
{
}

CMaterial::~CMaterial()
{
	size_t Size = mTextureList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		SAFE_DELETE(mTextureList[i]);
	}
}

//텍스쳐 
void CMaterial::AddTexture(class CTexture* Texture, int Register, int ShaderBufferType, int TextureIndex)
{
	FMaterialTextureInfo* TexInfo = new FMaterialTextureInfo;

	TexInfo->Texture = Texture;
	TexInfo->Name = Texture->GetName();
	TexInfo->Register = Register;
	TexInfo->ShaderBufferType = ShaderBufferType;
	TexInfo->TextureIndex = TextureIndex;

	//텍스쳐가 사용하는 상수버퍼가 있으면 여기에 작업해준다. 


	mTextureList.emplace_back(TexInfo);
}

void CMaterial::AddTexture(const std::string& Name, int Register, int ShaderBufferType, int TextureIndex)
{
	FMaterialTextureInfo* TexInfo = new FMaterialTextureInfo;

	//Texture 정보를 찾아온다.
	//머티리얼 꼭 Scene이 있을때 생성된다고 보장이 없다.
	if (mScene)
	{
		//Scene->SceneAssetManager 통해서
		TexInfo->Texture = mScene->GetAssetManager()->FindTexture(Name);
	}
	else
	{
		//AssetManager 에서 TextureManager통해서 가져올수도 있다.
		TexInfo->Texture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);
	}

	TexInfo->Name = TexInfo->Texture->GetName();
	TexInfo->Register = Register;
	TexInfo->ShaderBufferType = ShaderBufferType;
	TexInfo->TextureIndex = TextureIndex;

	//텍스쳐가 사용하는 상수버퍼가 있으면 여기에 작업해준다. 


	mTextureList.emplace_back(TexInfo);

}

void CMaterial::AddTexture(const std::string& Name, const TCHAR* FileName, int Register, int ShaderBufferType,
	int TextureIndex)
{
	FMaterialTextureInfo* TexInfo = new FMaterialTextureInfo;

	//Texture 정보를 찾아온다.
	//머티리얼 꼭 Scene이 있을때 생성된다고 보장이 없다.
	if (mScene)
	{
		//Scene->SceneAssetManager 통해서
		if (!mScene->GetAssetManager()->LoadTexture(Name, FileName))
		{
			SAFE_DELETE(TexInfo);
			return;
		}

		TexInfo->Texture = mScene->GetAssetManager()->FindTexture(Name);
	}
	else
	{
		if (!CAssetManager::GetInst()->GetTextureManager()->LoadTexture(Name, FileName))
		{
			SAFE_DELETE(TexInfo);
			return;
		}
		//AssetManager 에서 TextureManager통해서 가져올수도 있다.
		TexInfo->Texture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);
	}


	TexInfo->Name = TexInfo->Texture->GetName();
	TexInfo->Register = Register;
	TexInfo->ShaderBufferType = ShaderBufferType;
	TexInfo->TextureIndex = TextureIndex;

	//텍스쳐가 사용하는 상수버퍼가 있으면 여기에 작업해준다. 


	mTextureList.emplace_back(TexInfo);
}

//픽셀 쉐이더 
void CMaterial::SetPixelShader(const std::string& Name)
{
	const FMaterialPixelShader* mps = CShaderManager::GetInst()->FindPixelShader(Name);

	if (!mps)
	{
		return;
	}

	mPS = mps->PS;
}

void CMaterial::SetPixelShader(const std::string& Name, const char* EntryName, const TCHAR* FileName)
{

	if (!CShaderManager::GetInst()->LoadPixelShader(Name, EntryName, FileName))
	{
		return;
	}

	const FMaterialPixelShader* mps = CShaderManager::GetInst()->FindPixelShader(Name);

	if (!mps)
	{
		return;
	}

	mPS = mps->PS;
}
