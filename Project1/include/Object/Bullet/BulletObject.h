#pragma once
#include "../SceneObject.h"
#include "../../Component/SceneComponent/StaticMeshComponent.h"
#include "../../Component/Collider/ColliderAABB2D.h"
#include "../../Component/NonSceneComponent/MovementComponent.h"

enum class EBulletClass
{
	Player,
	Monster
};

class CBulletObject :
	public CSceneObject
{
	friend class CScene;

private:
	float mSpeed = 200.f;


	EBulletClass mBulletClass = EBulletClass::Player;
	CSceneObject* mOwner = nullptr;

public:
	float GetBulletSpeed() const
	{
		return mSpeed;
	}

	void SetBulletSpeed(const float& Speed)
	{
		mSpeed = Speed;
	}

	void SetBulletClass(EBulletClass BulletType)
	{
		mBulletClass = BulletType;
		if (mBody)
		{
			mBody->SetCollisionProfile(BulletType == EBulletClass::Player ? "PlayerAttack" : "MonsterAttack");
		}
	}

	void SetOwner(CSceneObject* Owner)
	{
		mOwner = Owner;
	}



protected:

	CSharedPtr<class CStaticMeshComponent> mRoot;
	CSharedPtr<class CColliderAABB2D> mBody;
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

