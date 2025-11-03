#pragma once
#include "../SceneObject.h"


class CGravitionSurge : public CSceneObject
{
	friend class CScene;

protected:

private:
	float mSpeed = 200.f;

	float mMeshRange = 400.f;
	float mPullRange = 200.f;
	

public:
	float GetBulletSpeed() const
	{
		return mSpeed;
	}
	void SetBulletSpeed(const float& Speed)
	{
		mSpeed = Speed;
	}
	
protected:
	CSharedPtr<class CStaticMeshComponent> mMesh;
	CSharedPtr<class CMovementComponent> mMovement;

protected:
	CGravitionSurge();
	CGravitionSurge(const CGravitionSurge& Obj);
	CGravitionSurge(CGravitionSurge&& Obj);
	virtual ~CGravitionSurge();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PreUpdate(float DeltaTime);

};

