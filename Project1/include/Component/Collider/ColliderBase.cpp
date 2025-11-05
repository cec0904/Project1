#include "ColliderBase.h"


#include "../../Scene/Scene.h"
#include "../../Scene/Collision/SceneCollision.h"

CColliderBase::CColliderBase()
{
}
CColliderBase::CColliderBase(const CColliderBase& Com)
	: CSceneComponent(Com)
{
}
CColliderBase::CColliderBase(CColliderBase&& Com)
	: CSceneComponent(Com)
{
}
CColliderBase::~CColliderBase()
{
}

bool CColliderBase::Init()
{
	if (!CSceneComponent::Init())
	{
		return false;
	}

	mScene->GetCollision()->AddCollider(this);

	return true;
}
bool CColliderBase::Init(const char* FileName)
{
	if (!CSceneComponent::Init(FileName))
	{
		return false;
	}
	mScene->GetCollision()->AddCollider(this);

	return true;
}
void CColliderBase::PreUpdate(float DeltaTime)
{
	CSceneComponent::PreUpdate(DeltaTime);
}
void CColliderBase::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}

void CColliderBase::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);
}

void CColliderBase::Collision(float DeltaTime)
{
	CSceneComponent::Collision(DeltaTime);
}
void CColliderBase::PreRender()
{
	CSceneComponent::PreRender();
}
void CColliderBase::Render()
{
	CSceneComponent::Render();
}
void CColliderBase::PostRender()
{
	CSceneComponent::PostRender();
}

CColliderBase* CColliderBase::Clone()
{
	return new CColliderBase(*this);
}