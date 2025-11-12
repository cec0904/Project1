#include "PoisonBullet.h"
#include "../../Component/SceneComponent/StaticMeshComponent.h"
#include "../../Component/NonSceneComponent/MovementComponent.h"

#include "../Monster/MonsterObject.h"
#include "../../Scene/Scene.h"

#include "BulletObject.h"
#include "../../Component/Collider/ColliderAABB2D.h"
#include "../../Share/Log/Log.h"
#include "../../Component/Collider/ColliderOBB2D.h"
#include "../../Component/Collider/ColliderSphere2D.h"



CPoisonBullet::CPoisonBullet()
{
}

CPoisonBullet::CPoisonBullet(const CPoisonBullet& Obj)
{
}

CPoisonBullet::CPoisonBullet(CPoisonBullet&& Obj)
{
}

CPoisonBullet::~CPoisonBullet()
{
}
void CPoisonBullet::SetBulletCollisionProfile(const string& name)
{
	mBody->SetCollisionProfile(name);
}

bool CPoisonBullet::Init()
{
	mRoot = CreateComponent<CStaticMeshComponent>();
	mMovement = CreateComponent<CMovementComponent>();
	mBody = CreateComponent<CColliderSphere2D>();

	mRoot->SetMesh("CenterRect");
	mRoot->SetShader("ColorMeshShader");
	mRoot->SetWorldScale(50.f, 50.f);
	SetRootComponent(mRoot);
	mRoot->AddChild(mBody);

	mMovement->SetUpdateComponent(mRoot);
	mMovement->SetMoveAxis(EAxis::Y);
	mMovement->SetMoveSpeed(250.f);

	mBody->SetRadius(mRange);
	mBody->SetCollisionProfile("PlayerPoisonAttack");
	//mBody->SetCollisionBeginFunc<CPoisonBullet>(this, &CPoisonBullet::PoisonBullet);

	return true;
}
void CPoisonBullet::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	mDistance -= mMovement->GetMoveDistance();

	if (mDistance <= 0.f)
	{
		//
		mDuration -= DeltaTime;

		if (mDuration <= 0)
		{
			Destroy();
		}
		

		mMovement->SetEnable(false);
		
		list<CSharedPtr<CMonsterObject>> MonsterList;

		mScene->FindObjectsFromType<CMonsterObject>(MonsterList);

		// 순회 반복자
		auto iter = MonsterList.begin();
		auto iterEnd = MonsterList.end();

		for (; iter != iterEnd; iter++)
		{
			FVector3D Pos = (*iter)->GetWorldPosition();


			float dist = Pos.Distance(GetWorldPosition());

			if (dist <= mRange)
			{
				mPoisonTime += DeltaTime;
				if (mPoisonTime >= 1)
				{
					mPoisonTime = 0.f;

					float dmg = (*iter)->Damage(1.f, this);
					CLog::PrintLog("Bullet is Poisoning Collision", ELogPrintType::All);
				}
			}
		}

	}

	
}

void CPoisonBullet::PoisonBullet(const FVector3D& HitPoint, CColliderBase* Dest)
{
	CLog::PrintLog("Bullet is Poisoning Collision", ELogPrintType::All);
		Dest->GetOwner()->Damage(1.f, this);
}