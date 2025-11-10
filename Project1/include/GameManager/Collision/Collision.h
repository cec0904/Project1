#pragma once

#include "../../GameInfo.h"

class CCollision
{
public:
	CCollision();
	~CCollision();

	// 호출
	static bool CollisionAABB2DToAABB2D(
		FVector3D& HitPoint,
		class CColliderAABB2D* Src,
		class CColliderAABB2D* Dest);

	static bool CollisionSphere2DToSphere2D(FVector3D& HitPoint,
		class CColliderSphere2D* Src,
		class CColliderSphere2D* Dest);

	// AABB2D to Sphere2D
	static bool CollisionAABB2DToSphere2D(FVector3D& HitPoint,
		class CColliderAABB2D* Src,
		class CColliderSphere2D* Dest);

	// OBB2D to OBB2D
	static bool CollisionOBB2DToOBB2D(FVector3D& HitPoint,
		class CColliderOBB2D* Src,
		class CColliderOBB2D* Dest);

	// 연산
	static bool CollisionAABB2DToAABB2D(FVector3D& HitPoint,
		const FAABB2D& Src, const FAABB2D& Dest);

	static bool CollisionSphere2DToSphere2D(FVector3D& HitPoint,
		const FVector3D& SrcCenter, float SrcRadius,
		const FVector3D& DestCenter, float DestRadius);

	static bool CollisionAABB2DToSphere2D(FVector3D& HitPoint,
		const FAABB2D& Src,
		const FVector3D& DestCenter, float DestRadius);

	static bool CollisionOBB2DToOBB2D(FVector3D& HitPoint, const FOBB2D& Src, const FOBB2D& Dest);

	

private:
	// 1. 두 중심의 축
	// 2. 분리축
	// 3. Src 크기의 반
	// 4. Dest축
	// 5. Dest의 크기
	static bool ComputeAxisProjection(
		const FVector2D& CenterLine,
		const FVector2D& SeparationAxis,
		float AxisHalfSize, 
		const FVector2D* DestAxis,
		const FVector2D& DestHalfSize);
	
	// OBB 정보를 가지고 충돌용 AABB 사각형을 만들어주는 함수
	static FAABB2D CreateAABB2D(const FOBB2D& Info);



};

