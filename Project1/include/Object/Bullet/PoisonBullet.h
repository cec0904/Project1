#pragma once
#include "../SceneObject.h"


class CPoisonBullet : public CSceneObject
{
	friend class CScene;

protected:
	CPoisonBullet();
	CPoisonBullet(const CPoisonBullet& Obj);
	CPoisonBullet(CPoisonBullet&& Obj);
	virtual ~CPoisonBullet();

protected:
	CSharedPtr<class CStaticMeshComponent> mRoot;
	CSharedPtr<class CMovementComponent> mMovement;


	float mSpeed = 200.f;
	float mDistance = 150.f;
	float mDuration = 1.f;
	float mRange = 500.f;
	


public:
	float GetBulletSpeed() const
	{
		return mSpeed;
	}
	void SetBulletSpeed(const float& Speed)
	{
		mSpeed = Speed;
	}

public:
	virtual bool Init();
	virtual void Update(float DeltaTime, const FVector3D& HitPoint, class CColliderBase* Dest);


};

