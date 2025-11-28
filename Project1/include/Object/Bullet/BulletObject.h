#pragma once
#include "../SceneObject.h"



class CBulletObject :
	public CSceneObject
{
	friend class CScene;
private:
	float mSpeed = 200.f;


	

	// 숙제
	/*EBulletClass mBulletClass = EBulletClass::Player;
	CSceneObject* mOwner = nullptr;*/

protected:
	float mFireTime = 1.f;
	int mFireCount = 0;

public:
	float GetBulletSpeed() const
	{
		return mSpeed;
	}

	void SetBulletSpeed(const float& Speed)
	{
		mSpeed = Speed;
	}

	// 숙제
	/*void SetBulletClass(EBulletClass BulletType)
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
	}*/

	// 강사님
	void SetBulletCollisionProfile(const string& Name);

protected:

	//CSharedPtr<class CStaticMeshComponent> mRoot;
	CSharedPtr<class CSpriteComponent> mRoot;
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

private:
	void CollisionBullet(const FVector3D& HitPoint, class CColliderBase* Dest);
	

};

