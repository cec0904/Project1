#include "StaticMeshComponent.h"

#include "../../Asset/Mesh/StaticMesh.h"
#include "../../Shader/ShaderClass/Shader.h"
#include "../../Shader/ShaderManager.h"
#include "../../Asset/AssetManager.h"
#include "../../Asset/Mesh/MeshManager.h"
#include "../../Scene/Scene.h"
#include "../../Scene/Asset/SceneAssetManager.h"

CStaticMeshComponent::CStaticMeshComponent()
	: CMeshComponent()
{
}

CStaticMeshComponent::CStaticMeshComponent(const CStaticMeshComponent& Com)
	: CMeshComponent(Com)
{
}

CStaticMeshComponent::CStaticMeshComponent(CStaticMeshComponent&& Com)
	: CMeshComponent(Com)
{
}

CStaticMeshComponent::~CStaticMeshComponent()
{
}

void CStaticMeshComponent::SetShader(const std::string& Name)
{
	mShader = CShaderManager::GetInst()->FindShader(Name);
}

void CStaticMeshComponent::SetShader(CShader* Shader)
{
	mShader = Shader;
}

void CStaticMeshComponent::SetMesh(const std::string& Name)
{
	//mMesh = (CStaticMesh*)CAssetManager::GetInst()->GetMeshManager()->FindMesh(Name);

	mMesh = (CStaticMesh*)mScene->GetAssetManager()->FindMesh(Name);
}

void CStaticMeshComponent::SetMesh(CMesh* Mesh)
{
	mMesh = (CStaticMesh*)Mesh;
}

bool CStaticMeshComponent::Init()
{
	CMeshComponent::Init();

	return true;
}
bool CStaticMeshComponent::Init(const char* FileName)
{
	CMeshComponent::Init(FileName);
	return true;
}
void CStaticMeshComponent::PreUpdate(float DeltaTime)
{
	CMeshComponent::PreUpdate(DeltaTime);
}
void CStaticMeshComponent::Update(float DeltaTime)
{
	CMeshComponent::Update(DeltaTime);
}
void CStaticMeshComponent::PostUpdate(float DeltaTime)
{
	CMeshComponent::PostUpdate(DeltaTime);
}
void CStaticMeshComponent::Collision(float DeltaTime)
{
	CMeshComponent::Collision(DeltaTime);
}
void CStaticMeshComponent::PreRender()
{
	CMeshComponent::PreRender();
}
void CStaticMeshComponent::Render()
{
	CMeshComponent::Render();

	mShader->SetShader();
	mMesh->Render();

}
void CStaticMeshComponent::PostRender()
{
	CMeshComponent::PostRender();
}
CStaticMeshComponent* CStaticMeshComponent::Clone()
{
	return new CStaticMeshComponent(*this);
}