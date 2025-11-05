#include "Collision.h"

#include "../../Component/Collider/ColliderAABB2D.h"


bool CCollision::CollisionAABB2DToAABB2D(FVector3D& HitPoint, CColliderAABB2D* Src, CColliderAABB2D* Dest)
{
	if (CollisionAABB2DToAABB2D(HitPoint, Src->GetBox(), Dest->GetBox()))
	{
		return true;
	}

	return false;
}

bool CCollision::CollisionAABB2DToAABB2D(FVector3D& HitPoint, const FAABB2D& Src, const FAABB2D& Dest)
{
	//AABB 충돌 
	//좌표
	if (Src.Min.x > Dest.Max.x)
	{
		// 충돌체 왼쪽이 노드의 오른쪽 보다 크다.
		return false;
	}
	else if (Dest.Min.x > Src.Max.x)
	{
		// 충돌체 오른쪽이 노드의 왼쪽보다 작다 
		return false;
	}
	else if (Src.Min.y > Dest.Max.y)
	{
		// 충돌체의 아래가 노드의 위보다 크다.
		return false;
	}
	else if (Dest.Min.y > Src.Max.y)
	{
		// 충돌체의 위가 노드의 아래보다 작다.
		return false;
	}

	//충돌했다!
	//충돌 좌표 
	FVector3D Min, Max;
	// 비교 ?	참 : 거짓
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