#include "ColliderAABB2D.h"
#include "../../GameManager/Collision/Collision.h"
#include "../../Asset/AssetManager.h"
#include "../../Asset/Mesh/Mesh.h"
#include "../../Asset/Mesh/MeshManager.h"
#include "ColliderSphere2D.h"

CColliderOBB2D::CColliderOBB2D()
{
	mColliderType = EColliderType::Collider2D;
	mColliderShape = EColliderShape::AABB2D;
	mBoxSize.x = 100.f;
	mBoxSize.y = 100.f;
}

CColliderOBB2D::CColliderOBB2D(const CColliderOBB2D& Com)
	: CColliderBase(Com)
{
	mColliderType = EColliderType::Collider2D;
	mColliderShape = EColliderShape::AABB2D;

	mBoxSize = Com.mBoxSize;
}

CColliderOBB2D::CColliderOBB2D(CColliderOBB2D&& Com)
	: CColliderBase(Com)
{
	mColliderType = EColliderType::Collider2D;
	mColliderShape = EColliderShape::AABB2D;

	mBoxSize = Com.mBoxSize;
}

CColliderOBB2D::~CColliderOBB2D()
{
}

bool CColliderOBB2D::Init()
{
	if (!CColliderBase::Init())
	{
		return false;
	}
#ifdef _DEBUG
	mMesh = CAssetManager::GetInst()->GetMeshManager()->FindMesh("FrameCenterRect");
#endif // _DEBUG


	return true;
}

bool CColliderOBB2D::Init(const char* FileName)
{
	if (!CColliderBase::Init(FileName))
	{
		return false;
	}


	return true;
}
void CColliderOBB2D::PreUpdate(float DeltaTime)
{
	CColliderBase::PreUpdate(DeltaTime);
}

void CColliderOBB2D::Update(float DeltaTime)
{
	CColliderBase::Update(DeltaTime);

	//충돌체의 좌표값 구하기!

	mAABB.Min.x = mWorldPos.x - mBoxSize.x * 0.5;
	mAABB.Min.y = mWorldPos.y - mBoxSize.y * 0.5;

	mAABB.Max.x = mWorldPos.x + mBoxSize.x * 0.5;
	mAABB.Max.y = mWorldPos.y + mBoxSize.y * 0.5;

	mMin.x = mAABB.Min.x;
	mMin.y = mAABB.Min.y;
	mMax.x = mAABB.Max.x;
	mMax.y = mAABB.Max.y;

	// 박스 사이즈가 곧 ColliderBase의 크기이다.
	SetWorldScale(mBoxSize);
}

void CColliderOBB2D::PostUpdate(float DeltaTime)
{
	CColliderBase::PostUpdate(DeltaTime);
}

void CColliderOBB2D::Collision(float DeltaTime)
{
	CColliderBase::Collision(DeltaTime);
}
void CColliderOBB2D::PreRender()
{
	CColliderBase::PreRender();
}
void CColliderOBB2D::Render()
{
	CColliderBase::Render();
}
void CColliderOBB2D::PostRender()
{
	CColliderBase::PostRender();
}

CColliderOBB2D* CColliderOBB2D::Clone()
{
	return new CColliderOBB2D(*this);
}

bool CColliderOBB2D::Collision(FVector3D& HitPoint, CColliderBase* Dest)
{
	if (Dest->GetColliderType() == EColliderType::Collider3D)
	{
		return false;
	}

	switch (Dest->GetColliderShape())
	{
	case EColliderShape::AABB2D:
		return CCollision::CollisionAABB2DToAABB2D(HitPoint, this, (CColliderOBB2D*)Dest);
		break;
	case EColliderShape::Sphere2D:
		return CCollision::CollisionAABB2DToSphere2D(HitPoint, this, (CColliderSphere2D*)Dest);
		break;
	}

	return false;
}

