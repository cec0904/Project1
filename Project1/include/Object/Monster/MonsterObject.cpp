#include "MonsterObject.h"
#include "../../Component/SceneComponent/StaticMeshComponent.h"
#include "../../Object/Bullet/BulletObject.h"
#include "../../Scene/Scene.h"
#include "../../Component/Collider/ColliderAABB2D.h"
#include "../../Component/Collider/ColliderSphere2D.h"
#include "../../Component/Collider/ColliderOBB2D.h"
#include "../../Share/Log/Log.h"
#include "../Monster/ObjectSpawnPoint.h"




#include <sstream>


CMonsterObject::CMonsterObject()
{
}

CMonsterObject::CMonsterObject(const CMonsterObject& Obj)
	: CSceneObject(Obj)
{
}

CMonsterObject::CMonsterObject(CMonsterObject&& Obj)
	: CSceneObject(Obj)
{
	
}

CMonsterObject::~CMonsterObject()
{
}



void CMonsterObject::CollisionMonster(const FVector3D& HitPoint, CColliderBase* Dest)
{
	CLog::PrintLog("Collision Monster");

	// Dest->GetProfile()->Channel == ECollisionChannel::PlayerAttack();

	// 공용된 데미지 함수를 만들어서 호출하는게 더 좋다.
}

float CMonsterObject::Damage(float Attack, CSceneObject* Obj)
{
	float Dmg = CSceneObject::Damage(Attack, Obj);

 	mHP -= (int)Dmg;

	if (mHP <= 0)
	{
		if (mSpawnPoint != nullptr)
		{
			mSpawnPoint->ClearObject();
		}

		Destroy();
		CLog::PrintLog("Monster is dead");
		//CMonsterSpawn::MonsterRespawn();
		
	}

	return Dmg;
}



bool CMonsterObject::Init()
{
	if (!CSceneObject::Init())
	{
		return false;
	}

	mRoot = CreateComponent<CStaticMeshComponent>();
	mBody = CreateComponent<CColliderOBB2D>();
	//mBody = CreateComponent<CColliderSphere2D>();

	mRoot->SetMesh("CenterRect");
	mRoot->SetShader("ColorMeshShader");
	mRoot->SetWorldScale(100.f, 100.f);

	SetRootComponent(mRoot);

	mRoot->AddChild(mBody);
	mBody->SetBoxSize(100.f, 100.f);
	// mBody->SetRadius(50.f);
	mBody->SetCollisionProfile("Monster");
	mBody->SetCollisionBeginFunc<CMonsterObject>(this, &CMonsterObject::CollisionMonster);

	return true;

}
void CMonsterObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	if (!mTarget->IsActive())
	{
		mTarget = nullptr;
	}

	else if (mTarget->IsEnable())
	{
	}

}
