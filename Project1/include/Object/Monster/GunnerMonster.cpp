#include "GunnerMonster.h"
#include "../Bullet/BulletObject.h"
#include "../../Scene/Scene.h"
#include "../Player/PlayerObject.h"
#include "../../Component/SceneComponent/StaticMeshComponent.h"


CGunnerMonster::CGunnerMonster()
	:CMonsterObject()
{
}

CGunnerMonster::CGunnerMonster(const CGunnerMonster& Obj)
	:CMonsterObject(Obj)
{
}

CGunnerMonster::CGunnerMonster(CGunnerMonster&& Obj)
	:CMonsterObject(Obj)
{
}

CGunnerMonster::~CGunnerMonster()
{
}

bool CGunnerMonster::Init()
{
	if (!CMonsterObject::Init())
	{
		return false;
	}

	mRoot->SetMesh("CenterTexRect");
	mRoot->SetMaterial(0, "Monster1");
	mRoot->SetShader("StaticMeshShader");
	mRoot->SetOpacity(0, 1.f);

	SetTarget(mScene->FindObjectFromType<CPlayerObject>());

	return true;
}

void CGunnerMonster::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	if (!mTarget->IsActive())
	{
		mTarget = nullptr;
	}

	else if (mTarget->IsEnable())
	{
		

		float Angle = GetWorldPosition().GetViewTargetAngle(mTarget->GetWorldPosition());

		

		SetWorldRotationZ(Angle);
	}

	// 발사하기 샘플
	mFireTime -= DeltaTime;
	if (mFireTime <= 0)
	{
		mFireTime = 1.f;

		mFireCount++;

		CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");
		Bullet->SetWorldScale(50.f, 50.f);
		Bullet->SetWorldRotation(GetWorldRotation());
		Bullet->SetWorldPos(GetWorldPosition());
		
		// collision
		Bullet->SetBulletCollisionProfile("MonsterAttack");

		// collision
		// Bullet->SetBulletClass(EBulletClass::Monster);

		Bullet->SetLifeTime(2.f);

		// 지금 총알이 4번째 총알임 ?
		// 4번째 탄을 쐈을 때
		if (mFireCount ==4)
		{
			// 4번째 총알이면 다시 0으로 가게 해주자
			mFireCount = 0;


			// 위로 하나
			Bullet = mScene->CreateObj<CBulletObject>("Bullet");
			Bullet->SetWorldScale(50.f, 50.f);
			Bullet->SetWorldRotation(GetWorldRotation());

			Bullet->AddWorldRotationZ(45.f);

			Bullet->SetWorldPos(GetWorldPosition());

			// collision
			Bullet->SetBulletCollisionProfile("MonsterAttack");
			// collision
			// Bullet->SetBulletClass(EBulletClass::Monster);

			Bullet->SetLifeTime(2.f);


			// 아래로 하나
			Bullet = mScene->CreateObj<CBulletObject>("Bullet");
			Bullet->SetWorldScale(50.f, 50.f);
			Bullet->SetWorldRotation(GetWorldRotation());

			Bullet->AddWorldRotationZ(-45.f);

			Bullet->SetWorldPos(GetWorldPosition());

			// collision
			Bullet->SetBulletCollisionProfile("MonsterAttack");
			// collision
			// Bullet->SetBulletClass(EBulletClass::Monster);

			Bullet->SetLifeTime(2.f);
		}

	}
}