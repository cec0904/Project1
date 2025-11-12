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
	//CSharedPtr<class CColliderAABB2D> mBody;
	CSharedPtr<class CColliderSphere2D> mBody;

	
	float mSpeed = 200.f;
	// 총알거리
	float mDistance = 200.f;
	// 지속시간
	float mDuration = 5.f;
	// 범위
	float mRange = 200.f;
	
	// 데미지 시간
	float mPoisonTime = 1.f;


public:
	float GetBulletSpeed() const
	{
		return mSpeed;
	}
	void SetBulletSpeed(const float& Speed)
	{
		mSpeed = Speed;
	}
	void SetBulletCollisionProfile(const string& Name);

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);


private:
	void PoisonBullet(const FVector3D& HitPoint, class CColliderBase* Dest);
};

