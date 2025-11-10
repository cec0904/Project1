#include "ColliderOBB2D.h"
#include "../../GameManager/Collision/Collision.h"
#include "../../Asset/AssetManager.h"
#include "../../Asset/Mesh/Mesh.h"
#include "../../Asset/Mesh/MeshManager.h"

CColliderOBB2D::CColliderOBB2D()
{
	mColliderType = EColliderType::Collider2D;
	mColliderShape = EColliderShape::OBB2D;
	mBoxSize.x = 100.f;
	mBoxSize.y = 100.f;
}

CColliderOBB2D::CColliderOBB2D(const CColliderOBB2D& Com)
	: CColliderBase(Com)
{
	mColliderType = EColliderType::Collider2D;
	mColliderShape = EColliderShape::OBB2D;

	mBoxSize = Com.mBoxSize;
}

CColliderOBB2D::CColliderOBB2D(CColliderOBB2D&& Com)
	: CColliderBase(Com)
{
	mColliderType = EColliderType::Collider2D;
	mColliderShape = EColliderShape::OBB2D;

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

	// 정보 넣기
	mBoxInfo.Center.x = mWorldPos.x;
	mBoxInfo.Center.y = mWorldPos.y;

	mBoxInfo.Axis[0].x = mAxis[EAxis::X].x;
	mBoxInfo.Axis[0].y = mAxis[EAxis::X].y;

	mBoxInfo.Axis[1].x = mAxis[EAxis::X].x;
	mBoxInfo.Axis[1].y = mAxis[EAxis::X].y;

	mBoxInfo.HalfSizel = mBoxSize * 0.5;




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
		/*return CCollision::CollisionAABB2DToAABB2D(HitPoint, this, (CColliderOBB2D*)Dest);
		break;*/
	case EColliderShape::Sphere2D:
		/*return CCollision::CollisionAABB2DToSphere2D(HitPoint, this, (CColliderSphere2D*)Dest);
		break;*/
	}

	return false;
}
