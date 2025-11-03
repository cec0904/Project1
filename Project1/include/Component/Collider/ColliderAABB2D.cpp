#include "ColliderAABB2D.h"

CColliderAABB2D::CColliderAABB2D()
{
	mColliderType = EColliderType::Collider2D;
	mColliderShape = EColliderShape::AABB2D;
	mBoxSize.x = 100.f;
	mBoxSize.y = 100.f;
}

CColliderAABB2D::CColliderAABB2D(const CColliderAABB2D& Com)
	: CColliderBase(Com)
{
	mColliderType = EColliderType::Collider2D;
	mColliderShape = EColliderShape::AABB2D;

	mBoxSize = Com.mBoxSize;
}

CColliderAABB2D::CColliderAABB2D(CColliderAABB2D&& Com)
	: CColliderBase(Com)
{
	mColliderType = EColliderType::Collider2D;
	mColliderShape = EColliderShape::AABB2D;

	mBoxSize = Com.mBoxSize;
}

CColliderAABB2D::~CColliderAABB2D()
{
}

bool CColliderAABB2D::Init()
{
	if (!CColliderBase::Init())
	{
		return false;
	}

	return true;
}

bool CColliderAABB2D::Init(const char* FileName)
{
	if (!CColliderBase::Init(FileName))
	{
		return false;
	}

	return true;
}
void CColliderAABB2D::PreUpdate(float DeltaTime)
{
	CColliderBase::PreUpdate(DeltaTime);
}

void CColliderAABB2D::Update(float DeltaTime)
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
}

void CColliderAABB2D::PostUpdate(float DeltaTime)
{
	CColliderBase::PostUpdate(DeltaTime);
}

void CColliderAABB2D::Collision(float DeltaTime)
{
	CColliderBase::Collision(DeltaTime);
}
void CColliderAABB2D::PreRender()
{
	CColliderBase::PreRender();
}
void CColliderAABB2D::Render()
{
	CColliderBase::Render();
}
void CColliderAABB2D::PostRender()
{
	CColliderBase::PostRender();
}

CColliderAABB2D* CColliderAABB2D::Clone()
{
	return new CColliderAABB2D(*this);
}


