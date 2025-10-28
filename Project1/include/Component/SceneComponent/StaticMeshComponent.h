#pragma once
#include "MeshComponent.h"

class CStaticMeshComponent :
	public CMeshComponent
{
	//씬이랑 오브젝트 모두 사용할거같다.
	friend class CScene;
	friend class CSceneObject;

protected:
	CStaticMeshComponent();
	CStaticMeshComponent(const CStaticMeshComponent& Com);
	CStaticMeshComponent(CStaticMeshComponent&& Com);
	virtual ~CStaticMeshComponent();

protected:
	CSharedPtr<class CShader> mShader;
	CSharedPtr<class CStaticMesh> mMesh;

public:
	void SetShader(const std::string& Name);
	void SetShader(class CShader* Shader);
	void SetMesh(const std::string& Name);
	void SetMesh(class CMesh* Mesh);


	//시점 함수 
public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual CStaticMeshComponent* Clone();
};

