#include "TalonR.h"
#include "../../Component/SceneComponent/StaticMeshComponent.h"

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
	mMesh->SetMesh("CenterRect");
	mMesh->SetShader("ColorMeshShader");

	mMesh->SetWorldScale(0.5f, 0.5f, 1.f);

	SetRootComponent(mMesh);
	return true;
}

void CTalonR::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	FVector3D Pos = mMesh->GetWorldPosition();
	FVector3D Dir = mMesh->GetAxis(EAxis::Y);

	mTimeAcc += DeltaTime;
	float Angle = 0.f;

	switch (mState)
	{
	case ETalonRState::Expansion:
		mRange = DeltaTime / mReadyTime * mMaxRange;

		mMesh->SetWorldPos(Pos + Dir * mRange);

		if (mTimeAcc >= mReadyTime)
		{
			mTimeAcc -= mReadyTime;
			mState = ETalonRState::Maintain;
		}

		break;


	case ETalonRState::Maintain:

		Angle = mMesh->GetWorldRotation().z;
		Angle += mPivotRotationSpeed * DeltaTime;
		mMesh->SetWorldRotationZ(Angle);

		if (mTimeAcc >= mTime)
		{
			mTimeAcc = 0;
			mState = ETalonRState::Reducion;
			SetLifeTime(5.f);
		}


		break;



	case ETalonRState::Reducion:

		// 총알 -> 타겟 으로 가는 방향 벡터가 나온다.
		Dir = mTarget->GetRootComponent()->GetWorldPosition() - mMesh->GetWorldPosition();

		Dir.Normalize();

		mMesh->SetWorldPos(Pos + Dir * mSpeed * DeltaTime);

		break;
	//default:
	//	break;
	}
}