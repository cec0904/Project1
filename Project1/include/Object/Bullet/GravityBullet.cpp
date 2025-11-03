#include "GravityBullet.h"
#include "../../Component/SceneComponent/StaticMeshComponent.h"
#include "../../Component/NonSceneComponent/MovementComponent.h"


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

	mRoot = CreateComponent<CStaticMeshComponent>();
	mMovement = CreateComponent<CMovementComponent>();

	mRoot->SetMesh("CenterRect");
	mRoot->SetShader("ColorMeshShader");
	mRoot->SetWorldScale(50.f, 50.f);
	SetRootComponent(mRoot);

	mMovement->SetUpdateComponent(mRoot);
	mMovement->SetMoveAxis(EAxis::Y);
	mMovement->SetMoveSpeed(500.f);

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

		list<CSharedPtr<CMonsterObject>>MonsterList;

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
				//default:
				//	break;
				}

				MoveDir.Normalize();

				(*iter)->AddWorldPos(MoveDir * mGravitySpeed * DeltaTime);
			}
		}
	}
}