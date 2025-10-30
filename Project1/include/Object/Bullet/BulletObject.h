#pragma once
#include "../SceneObject.h"

class CBulletObject :
	public CSceneObject
{
	friend class CScene;

private:
	float mSpeed = 200.f;

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
	CSharedPtr<class CStaticMeshComponent> mRoot;
	CSharedPtr<class CMovementComponent> mMovement;
	

protected:
	CBulletObject();
	CBulletObject(const CBulletObject& Obj);
	CBulletObject(CBulletObject&& Obj);
	virtual ~CBulletObject();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

};

