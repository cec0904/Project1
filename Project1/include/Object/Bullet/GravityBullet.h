#pragma once
#include "../SceneObject.h"

enum class EGravityType
{
	GravitionSurge,
	ConcussiveBlast
};

class CGravityBullet : public CSceneObject
{
	friend class CScene;

protected:

private:
	float mSpeed = 200.f;
	float mDistance = 150.f;
	float mDuration = 1.f;
	float mRange = 500.f;
	float mGravitySpeed = 400.f;
	

public:
	float GetBulletSpeed() const
	{
		return mSpeed;
	}
	void SetBulletSpeed(const float& Speed)
	{
		mSpeed = Speed;
	}

	EGravityType GetGravityType()
	{
		return mGravityType;
	}

	void SetGravityType(EGravityType Type)
	{
		mGravityType = Type;
	}
	
protected:
	CSharedPtr<class CStaticMeshComponent> mMesh;
	CSharedPtr<class CMovementComponent> mMovement;
	EGravityType mGravityType = EGravityType::GravitionSurge;

protected:
	CGravityBullet();
	CGravityBullet(const CGravityBullet& Obj);
	CGravityBullet(CGravityBullet&& Obj);
	virtual ~CGravityBullet();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);


};

