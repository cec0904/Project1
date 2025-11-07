#include "Collision.h"

#include "../../Component/Collider/ColliderAABB2D.h"
#include "../../Component/Collider/ColliderSphere2D.h"

CCollision::CCollision()
{
}

CCollision::~CCollision()
{
}

bool CCollision::CollisionAABB2DToAABB2D(FVector3D& HitPoint, CColliderAABB2D* Src, CColliderAABB2D* Dest)
{
	if (CollisionAABB2DToAABB2D(HitPoint, 
		Src->GetBox(), 
		Dest->GetBox()))
	{
		return true;
	}

	return false;
}

bool CCollision::CollisionSphere2DToSphere2D(FVector3D& HitPoint, CColliderSphere2D* Src, CColliderSphere2D* Dest)
{
	if (CollisionSphere2DToSphere2D(HitPoint, 
		Src->GetWorldPosition(), Src->GetRadius(), 
		Dest->GetWorldPosition(), Dest->GetRadius()))
	{
		return true;
	}

	return false;
}

bool CCollision::CollisionAABB2DToSphere2D(FVector3D& HitPoint, CColliderAABB2D* Src, CColliderSphere2D* Dest)
{
	if (CollisionAABB2DToSphere2D(HitPoint,
		Src->GetBox(),
		Dest->GetWorldPosition(), Dest->GetRadius()))
	{
		return true;
	}

	return false;
}

bool CCollision::CollisionAABB2DToAABB2D(FVector3D& HitPoint, const FAABB2D& Src, const FAABB2D& Dest)
{
	// AABB 충돌
	// 좌표
	if (Src.Min.x > Dest.Max.x)
	{
		// 충돌체 왼쪽이 노드의 오른쪽 보다 크다
		return false;
	}
	else if (Dest.Min.x > Src.Max.x)
	{
		// 충돌체 오른쪽이 노드의 왼쪽보다 작다
		return false;
	}
	else if (Src.Min.y > Dest.Max.y)
	{
		// 충돌체의 아래가 노드의 위보다 크다
		return false;
	}
	else if (Dest.Min.y > Src.Max.y)
	{
		// 충돌체의 아래가 노드의 위보다 작다
		return false;
	}

	// 충돌했다면
	// 충돌 좌표
	FVector3D Min, Max;

	// 비교 ? 참 : 거짓
	// 겹친부분의 최소 좌표
	Min.x = Src.Min.x > Dest.Min.x ? Src.Min.x : Dest.Min.x;
	Min.y = Src.Min.y > Dest.Min.y ? Src.Min.y : Dest.Min.y;

	// 겹친 부분의 최대 좌표
	Max.x = Src.Max.x < Dest.Max.x ? Src.Max.x : Dest.Max.x;
	Max.y = Src.Max.y < Dest.Max.y ? Src.Max.y : Dest.Max.y;

	HitPoint.x = (Min.x + Max.x) * 0.5f;
	HitPoint.y = (Min.y + Max.y) * 0.5f;

	return true;
}

bool CCollision::CollisionSphere2DToSphere2D(FVector3D& HitPoint, const FVector3D& SrcCenter, float SrcRadius, const FVector3D& DestCenter, float DestRadius)
{
	// Src 와 Dest의 원 충돌이 일어날 것이다.
	// 두 원의 중심간의 거리를 구한다.
	float Dist = SrcCenter.Distance(DestCenter);

	// 원 충돌했니 ?
	// 두 원점의 거리가 두 원의 반지름의 합보다 작니 ?
	if (Dist <= SrcRadius + DestRadius)
	{
		// 충돌

		// 충돌 지점의 길이의 절반을 구한다.
		float Gap = SrcRadius + DestRadius - Dist;
		Gap *= 0.5;

		// 두 중심을 잇는 방향 벡터를 구한다.
		FVector3D Dir = DestCenter - SrcCenter;
		Dir.Normalize();	// Src 에서 Dest 가는 방향을 구했다.

		HitPoint = SrcCenter + Dir * (SrcRadius - Gap);
				// 충돌 사이 좌표

		return true;
	}

	return false;
}

bool CCollision::CollisionAABB2DToSphere2D(FVector3D& HitPoint, const FAABB2D& Src, const FVector3D& DestCenter, float DestRadius)
{
	// 1. 원의 중심이 사각형의 안에 있는지 검사해야한다.



	
	// 2. 대각선이 아닌 상 하 좌 우 범위에 들어갔는지 검사한다.
	// 사각형의 크기에서 반지름 만큼 더한 사각형 안에 있는지 검사한다.


	// 대각선은 두번 나눠 계산한다.


	// 3. 대각선 영역을 검사한다.
	// 가장 가까운 꼭짓점을 구하고
	// 해당 꼭짓점이랑 원의 중심이랑 거리가 반지름보다 작은지 확인해야한다.

	// hitPoint는 
	// 사격형과 원의 MinMax 사각형의 중간지점으로 한다.


	return false;
}
