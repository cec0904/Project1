#include "NearingMonster.h"
#include "../Player/PlayerObject.h"
#include "../../Scene/Scene.h"
#include "../../Component/Collider/ColliderLine2D.h"
#include "../../Component/Collider/ColliderSphere2D.h"

CNearingMonster::CNearingMonster()
{
}

CNearingMonster::CNearingMonster(const CNearingMonster& Obj)
	:CMonsterObject(Obj)
{
}

CNearingMonster::CNearingMonster(CNearingMonster&& Obj)
	:CMonsterObject(Obj)
{
}

CNearingMonster::~CNearingMonster()
{
}

bool CNearingMonster::Init()
{

	if (!CMonsterObject::Init())
	{
		return false;
	}

	mLine = CreateComponent<CColliderLine2D>();
	mBody->AddChild(mLine);
	mLine->SetLineDistance(200.f);
	mLine->SetCollisionProfile("Monster");
	mLine->SetLineAxis(EAxis::X);

	CPlayerObject* pPlayer = mScene->FindObjectFromName<CPlayerObject>("Player");
	if (pPlayer)
	{
		SetTarget(pPlayer);
	}

	mDetectDistance = 400.f;
	

	return true;


}

void CNearingMonster::Update(float DeltaTime)
{
	CMonsterObject::Update(DeltaTime);


	// 타겟있음 ?
	if (mTarget)
	{
		// 나와 타겟의 거리를 측정한다.
		float Distance = GetWorldPosition().Distance(mTarget->GetWorldPosition());

		// 측정한 거리가 내 사정거리 안이냐
		if (Distance <= mDetectDistance)	// 탐지 됐다
		{
			// 타겟쪽으로 회전시켜
			float RotAngle = GetWorldPosition().GetViewTargetAngle(mTarget->GetWorldPosition());

			SetWorldRotationZ(RotAngle);


			// 타겟과의 각도를 계산한다.
			// 타겟을 바라보는 방향벡터를 구한다.
			// 상대방에서 내위치 빼면 상대방이 바라보는 방향벡터다
			FVector3D View = mTarget->GetWorldPosition() - GetWorldPosition();
			View.Normalize();

			// 내가 타겟을 바라보는 각도 < 내가 공격 각도 안이냐
			float Angle = GetAxis(EAxis::Y).GetAngle(View);

			if (Angle < mDetectAngle)
			{
				// 공격
				// Attack Time 주기마다
				mAttackTime -= DeltaTime;

				if (mAttackTime <= 0.f)
				{
					// 공격을 할 것이다.
					mAttackTime += 1.f;

					CPlayerObject* Player = dynamic_cast<CPlayerObject*>(mTarget.Get());
					if (Player)
					{
						Player->Damage(1);
					}
				}
			}
			
			else
			{
				mAttackTime = 1.f;
			}
		}
		else
		{
			mAttackTime = 1.f;
		}

	}
}
