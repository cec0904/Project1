#include "SpriteComponent.h"
#include "../../Shader/ShaderClass/Shader.h"
#include "../../Shader/ShaderManager.h"
#include "../../Asset/AssetManager.h"
#include "../../Asset/Mesh/Mesh.h"
#include "../../Asset/Mesh/MeshManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/Asset/SceneAssetManager.h"
#include "../../Asset/Texture/TextureManager.h"
#include "../../Asset/Texture/Texture.h"
#include "../../Shader/ConstantBuffer/SpriteCBuffer.h"
#include "../../Shader/ConstantBuffer/Transform/TransformCBuffer.h"
#include "../../Component/SceneComponent/CameraComponent.h"

CSpriteComponent::CSpriteComponent()
{
}

CSpriteComponent::CSpriteComponent(const CSpriteComponent& Com)
{
}

CSpriteComponent::CSpriteComponent(CSpriteComponent&& Com)
{
}

CSpriteComponent::~CSpriteComponent()
{
	SAFE_DELETE(mSpriteCBuffer);
}

void CSpriteComponent::SetShader(const string& Name)
{
	mShader = CShaderManager::GetInst()->FindShader(Name);
}

void CSpriteComponent::SetShader(class CShader* Shader)
{
	mShader = Shader;
}

void CSpriteComponent::SetTexture(const string& Name, int TextureIndex)
{
	if (mScene)
	{
		//Scene->SceneAssetManager 통해서
		mTexture = mScene->GetAssetManager()->FindTexture(Name);
	}
	else
	{
		//AssetManager 에서 TextureManager통해서 가져올수도 있다.
		mTexture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);
	}

	mTextureIndex = TextureIndex;
}

void CSpriteComponent::SetTexture(const string& Name, const TCHAR* FileName, int TextureIndex)
{
	if (mScene)
	{
		//Scene->SceneAssetManager 통해서
		if (!mScene->GetAssetManager()->LoadTexture(Name, FileName))
		{
			return;
		}
		mTexture = mScene->GetAssetManager()->FindTexture(Name);
	}
	else
	{
		if (!CAssetManager::GetInst()->GetTextureManager()->LoadTexture(Name, FileName))
		{
			return;
		}

		mTexture = CAssetManager::GetInst()->GetTextureManager()->FindTexture(Name);
	}

	mTextureIndex = TextureIndex;
}

void CSpriteComponent::SetTexture(class CTexture* Texture, int TextureIndex)
{
	mTexture = Texture;
	mTextureIndex = TextureIndex;
}

void CSpriteComponent::SetTint(float r, float g, float b)
{
	mTint.x = r;
	mTint.y = g;
	mTint.z = b;
}

void CSpriteComponent::SetOpacity(float Opacity)
{
	mTint.w = Opacity;
}

bool CSpriteComponent::Init()
{
	CSceneComponent::Init();

	mSpriteCBuffer = new CSpriteCBuffer;
	mSpriteCBuffer->Init();

	SetShader("SpriteShader");

	// SpriteRect
	// Sprite이미지는 Mesh 고정해서 사용할것이다. 
	if (mScene)
	{
		mMesh = mScene->GetAssetManager()->FindMesh("SpriteRect");
	}
	else
	{
		mMesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh("SpriteRect");
	}


	return true;
}

bool CSpriteComponent::Init(const char* FileName)
{
	CSceneComponent::Init(FileName);

	mSpriteCBuffer = new CSpriteCBuffer;
	mSpriteCBuffer->Init();

	SetShader("SpriteShader");

	//SpriteRect
	// Sprite이미지는 Mesh 고정해서 사용할것이다. 
	if (mScene)
	{
		mMesh = mScene->GetAssetManager()->FindMesh("SpriteRect");
	}
	else
	{
		mMesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh("SpriteRect");
	}

	return true;
}

void CSpriteComponent::PreUpdate(float DeltaTime)
{
	CSceneComponent::PreUpdate(DeltaTime);
}

void CSpriteComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CSpriteComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CSpriteComponent::Collision(float DeltaTime)
{
	CSceneComponent::Collision(DeltaTime);
}

void CSpriteComponent::PreRender()
{
	CSceneComponent::PreRender();
}

void CSpriteComponent::Render()
{
	CSceneComponent::Render();

	//스프라이트 상수버퍼 셋팅 해주기
	mSpriteCBuffer->SetTint(mTint);
	mSpriteCBuffer->UpdateBuffer();
	//
	mShader->SetShader();

	if (mTexture)
	{
		mTexture->SetShader(0, EShaderBufferType::Pixel, mTextureIndex);
	}

	mMesh->Render();
}

void CSpriteComponent::PostRender()
{
	CSceneComponent::PostRender();
}

CSpriteComponent* CSpriteComponent::Clone()
{
	return new CSpriteComponent(*this);
}