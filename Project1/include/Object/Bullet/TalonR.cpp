﻿#include "TalonR.h"
#include "../../Component/SceneComponent/StaticMeshComponent.h"

#include "../../Component/NonSceneComponent/MovementComponent.h"
#include "../../Component/NonSceneComponent/RotationComponent.h"

CTalonR::CTalonR()
{
}

CTalonR::CTalonR(const CTalonR& Obj)
	:CSceneObject(Obj)
{
}

CTalonR::CTalonR(CTalonR&& Obj)
	:CSceneObject(Obj)
{
}

CTalonR::~CTalonR()
{
}

bool CTalonR::Init()
{
	if (!CSceneObject::Init())
	{
		return false;
	}

	mMesh = CreateComponent<CStaticMeshComponent>();
	mMovement = CreateComponent<CMovementComponent>();
	mRotation = CreateComponent<CRotationComponent>();

	mMovement->SetUpdateComponent(mMesh);
	mMovement->SetMoveAxis(EAxis::Y);
	// 이동거리 => 최대거리 / 총 걸리는 시간
	// 총 400 을 이동해야하는데 그걸 2초에 걸쳐서 갈거다.
	// 그럼 초당 200을 움직이면 최종 2초동안 400을 움직이게 될 것이다.
	mMovement->SetMoveSpeed(mMaxRange / mReadyTime);

	mRotation->SetUpdateComponent(mMesh);
	mRotation->SetEnable(false);
	mRotation->SetVelocityInit(false);
	mRotation->SetMoveZ(1080.f);


	mMesh->SetMesh("CenterRect");
	mMesh->SetShader("ColorMeshShader");

	mMesh->SetWorldScale(0.5f, 0.5f, 1.f);

	SetRootComponent(mMesh);
	return true;
}



void CTalonR::PreUpdate(float DeltaTime)
{
	CSceneObject::PreUpdate(DeltaTime);

	FVector3D Pos = mMesh->GetWorldPosition();
	FVector3D Dir = mMesh->GetAxis(EAxis::Y);

	mTimeAcc += DeltaTime;
	float Angle = 0.f;

	switch (mState)
	{
	case ETalonRState::Expansion:
		mRange = DeltaTime / mReadyTime * mMaxRange;

		// mMesh->SetWorldPos(Pos + Dir * mRange);

		if (mTimeAcc >= mReadyTime)
		{
			mTimeAcc -= mReadyTime;

			// 다음 상태값의 component의 상태값을 변경 해 줄것이다.
			mRotation->SetEnable(true);
			mMovement->SetEnable(true);

			mState = ETalonRState::Maintain;
			SetLifeTime(5.f);
		}

		break;


	case ETalonRState::Maintain:

		/*Angle = mMesh->GetWorldRotation().z;
		Angle += mPivotRotationSpeed * DeltaTime;
		mMesh->SetWorldRotationZ(Angle);*/

		if (mTimeAcc >= mTime)
		{
			mTimeAcc = 0;

			mRotation->SetEnable(true);
			mMovement->SetEnable(true);
			mMovement->SetMoveAxis(EAxis::None);

			mState = ETalonRState::Reducion;
			SetLifeTime(5.f);
		}


		break;



	case ETalonRState::Reducion:

		// 총알 -> 타겟 으로 가는 방향 벡터가 나온다.
		Dir = mTarget->GetRootComponent()->GetWorldPosition() - mMesh->GetWorldPosition();

		Dir.Normalize();

		// mMesh->SetWorldPos(Pos + Dir * mSpeed * DeltaTime);
		mMovement->SetMove(Dir);

		break;
	//default:
	//	break;
	}
}

void CTalonR::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);
}