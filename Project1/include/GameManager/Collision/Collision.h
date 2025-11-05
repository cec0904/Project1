#pragma once

#include "../../Gameinfo.h"

class CCollision
{
public:
	static bool CollisionAABB2DToAABB2D(FVector3D& HitPoint, class CColliderAABB2D* Src, class CColliderAABB2D* Dest);

	static bool CollisionAABB2DToAABB2D(FVector3D& HitPoint, const FAABB2D& Src, const FAABB2D& Dest);
};

