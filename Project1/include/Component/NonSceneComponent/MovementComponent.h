#pragma once
#include "../Component.h"

class CMovementComponent : public CComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CMovementComponent();
	CMovementComponent(const CMovementComponent& Com);
	CMovementComponent(CMovementComponent&& Com);
	virtual ~CMovementComponent();

protected:
	// 업데이트 할 컴포넌트
	CSharedPtr<class CSceneComponent> mUpdateComponent;

protected:
	// 이동 방향 벡터
	FVector3D mVelocity;
	// 한 프레임 당 이동 할 거리 벡터


};

