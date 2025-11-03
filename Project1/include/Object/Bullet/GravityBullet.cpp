#include "GravityBullet.h"
#include "../../Component/SceneComponent/StaticMeshComponent.h"
#include "../../Component/NonSceneComponent/MovementComponent.h"
#include "../../Component/NonSceneComponent/RotationComponent.h"

#include "../Monster/MonsterObject.h"
#include "../../Scene/Scene.h"

CGravityBullet::CGravityBullet()
{
}

CGravityBullet::CGravityBullet(const CGravityBullet& Obj)
{
}

CGravityBullet::CGravityBullet(CGravityBullet&& Obj)
{
}

CGravityBullet::~CGravityBullet()
{
}

bool CGravityBullet::Init()
{
	//if (!CSceneObject::Init())
	//{
	//	return false;
	//}

	mMesh = CreateComponent<CStaticMeshComponent>();
	mMovement = CreateComponent<CMovementComponent>();


	mMovement->SetUpdateComponent(mMesh);
	mMovement->SetMoveAxis(EAxis::Y);
	mMovement->SetMoveSpeed(500.f);

	mMesh->SetMesh("CenterRect");
	mMesh->SetShader("ColorMeshShader");
	mMesh->SetWorldScale(0.5f, 0.5f, 1.f);

	SetRootComponent(mMesh);

	return true;
}



void CGravityBullet::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);
	
	mDistance -= mMovement->GetMoveDistance();

	if (mDistance <= 0.f)
	{
		mDuration -= DeltaTime;

		if (mDuration <= 0)
		{
			Destroy();
		}

		// 총알 이동 스탑
		mMovement->SetEnable(false);

		list <CSharedPtr<CMonsterObject>>(MonsterList);

		mScene->FindObjectsFromType<CMonsterObject>(MonsterList);

		auto iter = MonsterList.begin();
		auto iterEnd = MonsterList.end();

		for (; iter != iterEnd; iter++)
		{
			FVector3D Pos = (*iter)->GetWorldPosition();

			float dist = Pos.Distnace(GetWorldPosition());

			if (dist <= mRange)
			{
				FVector3D MoveDir;

				switch (mGravityType)
				{
				case EGravityType::GravitionSurge:
					MoveDir = GetWorldPosition() - Pos;
					break;
				case EGravityType::ConcussiveBlast:
					MoveDir = Pos - GetWorldPosition();
					break;
				default:
					break;
				}

				MoveDir.Normalize();

				(*iter)->AddWorldPos(MoveDir * mGravitySpeed * DeltaTime);
			}
		}
	}
}