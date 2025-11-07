#pragma once

#include "../../GameInfo.h"

class CCollision
{
public:
	CCollision();
	~CCollision();

	// 호출
	static bool CollisionAABB2DToAABB2D(FVector3D& HitPoint,
		class CColliderAABB2D* Src,
		class CColliderAABB2D* Dest);

	static bool CollisionSphere2DToSphere2D(FVector3D& HitPoint,
		class CColliderSphere2D* Src,
		class CColliderSphere2D* Dest);

	// AABB2D to Sphere2D
	static bool CollisionAABB2DToSphere2D(FVector3D& HitPoint,
		class CColliderAABB2D* Src,
		class CColliderSphere2D* Dest);

	// 연산
	static bool CollisionAABB2DToAABB2D(FVector3D& HitPoint,
		const FAABB2D& Src, const FAABB2D& Dest);

	static bool CollisionSphere2DToSphere2D(FVector3D& HitPoint,
		const FVector3D& SrcCenter, float SrcRadius,
		const FVector3D& DestCenter, float DestRadius);

	static bool CollisionAABB2DToSphere2D(FVector3D& HitPoint,
		const FAABB2D& Src,
		const FVector3D& DestCenter, float DestRadius);
private:

};

