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

		// 몬스터 리스트 만들기
		list<CSharedPtr<CMonsterObject>>MonsterList;


		mScene->FindObjectsFromType<CMonsterObject>(MonsterList);

		// 순회 반복자 준비
		auto iter = MonsterList.begin();
		auto iterEnd = MonsterList.end();

		// 모든 몬스터에 대해서
		for (; iter != iterEnd; iter++)
		{
			// 몬스터 현재 위치
			FVector3D Pos = (*iter)->GetWorldPosition();

			// 총알의 중심(= 본인 위치) 와의 거리 계산
			// Vector3D.h, Vector3D.cpp
			// 몬스터 위치와(Pos) 총알 중심(GetWorldPosition()) 사이의 직선 거리를 구하는 수식
			float dist = Pos.Distance(GetWorldPosition());


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