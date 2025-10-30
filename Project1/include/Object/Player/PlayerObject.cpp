#include "PlayerObject.h"

#include "../../Component/SceneComponent/StaticMeshComponent.h"
#include "../../Component/NonSceneComponent/MovementComponent.h"
#include "../../Component/NonSceneComponent/RotationComponent.h"
#include "../../Component/SceneComponent/CameraComponent.h"


#include "../../Scene/Scene.h"
#include "../../Scene/Input/Input.h"

#include "../Bullet/BulletObject.h"
#include "../Bullet/TornadoBullet.h"
#include "../Bullet/TalonR.h"




CPlayerObject::CPlayerObject()
	: CSceneObject()
{
}

CPlayerObject::CPlayerObject(const CPlayerObject& Obj)
	: CSceneObject(Obj)
{
}

CPlayerObject::CPlayerObject(CPlayerObject&& Obj)
	: CSceneObject(Obj)
{
}

CPlayerObject::~CPlayerObject()
{
}
bool CPlayerObject::Init()
{
	// 게임 매니저 -> 씬매니저를 통해 -> 현재 씬을 실행시키고
	// 씬에서는 씬에 포함된 오브젝트들을 전부 순회하면서 시점 함수들을 호출해준다.
	// 오브젝트들은 본인의 루트 컴포넌트를 호출해주면
	// 루트 컴포넌트는 자식 컴포넌트들을 호출해준다.

	// 컴포넌트 하나 등록해줄것이다.

	mRoot = CreateComponent<CStaticMeshComponent>();
	mMovement = CreateComponent<CMovementComponent>();
	mCamera = CreateComponent<CCameraComponent>();
	mRotation = CreateComponent<CRotationComponent>();

	mRoot->SetMesh("CenterRect");
	mRoot->SetShader("ColorMeshShader");

	mRoot->SetWorldPos(0.f, 0.f, 0.f);
	mRoot->SetWorldScale(100.f, 100.f, 0.f);
	SetRootComponent(mRoot);

	mMovement->SetUpdateComponent(mRoot);
	mMovement->SetMoveSpeed(500.f);

	mRotation->SetUpdateComponent(mRoot);

	// 카메라 세팅
	mCamera->SetProjectionType(ECameraProjectionType::Ortho);
	mRoot->AddChild(mCamera);
	

	// 위성 만들기
	mRotationPivot = CreateComponent<CSceneComponent>();
	mSub = CreateComponent<CStaticMeshComponent>();
	mSub1 = CreateComponent<CStaticMeshComponent>();

	mRoot->AddChild(mRotationPivot);
	mRotationPivot->AddChild(mSub);
	mRotationPivot->AddChild(mSub1);

	// 위성1
	mSub->SetMesh("CenterRect");
	mSub->SetShader("ColorMeshShader");
	mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);
	mSub->SetRelativeScale(0.5f, 0.5f, 1.f);

	// 위성2
	mSub1->SetMesh("CenterRect");
	mSub1->SetShader("ColorMeshShader");
	mSub1->SetRelativePos(-mSkill4Range, 0.f, 0.f);
	mSub1->SetRelativeScale(0.5f, 0.5f, 1.f);

	// 입력
	mScene->GetInput()->AddBindKey("MoveUp", 'W');
	mScene->GetInput()->AddBindFunction("MoveUp", EInputType::Hold, this, &CPlayerObject::MoveUp);

	mScene->GetInput()->AddBindKey("MoveDown", 'S');
	mScene->GetInput()->AddBindFunction("MoveDown", EInputType::Hold, this, &CPlayerObject::MoveDown);


	// 회전
	mScene->GetInput()->AddBindKey("RotationZ", 'A');
	mScene->GetInput()->AddBindFunction("RotationZ", EInputType::Hold, this, &CPlayerObject::RotationZ);

	mScene->GetInput()->AddBindKey("RotationZInv", 'D');
	mScene->GetInput()->AddBindFunction("RotationZInv", EInputType::Hold, this, &CPlayerObject::RotationZInv);


	// 총알 발사
	mScene->GetInput()->AddBindKey("Fire", VK_SPACE);
	mScene->GetInput()->AddBindFunction("Fire", EInputType::Down, this, &CPlayerObject::Fire);

	// 스킬1
	mScene->GetInput()->AddBindKey("Skill1", '1');
	mScene->GetInput()->ChangeKeyCtrl("Skill1", true);

	mScene->GetInput()->AddBindFunction("Skill1", EInputType::Hold, this, &CPlayerObject::Skill1);
	mScene->GetInput()->AddBindFunction("Skill1", EInputType::Up, this, &CPlayerObject::Skill1Fire);


	// 스킬2
	// 토네이도샷
	mScene->GetInput()->AddBindKey("Skill2", '2');
	mScene->GetInput()->AddBindFunction("Skill2", EInputType::Down, this, &CPlayerObject::Skill2);

	// 스킬 3
	// 위성 발사
	mScene->GetInput()->AddBindKey("Skill3", '3');
	mScene->GetInput()->AddBindFunction("Skill3", EInputType::Down, this, &CPlayerObject::Skill3);

	// 스킬 4
	// 롤 아우솔 w 스킬
	// 돌아가는 위성의 범위를 늘렸다가 몇 초 후 다시 되돌아 오기
	// 가능하면 위송의 속도도 늘렸다가 줄이기
	mScene->GetInput()->AddBindKey("Skill4", '4');
	mScene->GetInput()->AddBindFunction("Skill4", EInputType::Down, this, &CPlayerObject::Skill4);

	// 스킬5
	// 롤 탈론 궁극기
	// 플레이어 기준으로 8방향으로 총알을 발사하고
	// 해당총알이 몇 초 돌다가
	// 플레이어에게 다시 되돌아오는 부메랑 기능
	mScene->GetInput()->AddBindKey("Skill5", '5');
	mScene->GetInput()->AddBindFunction("Skill5", EInputType::Down, this, &CPlayerObject::Skill5);




	return true;
}

void CPlayerObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	// 위성을 돌려주면 될 것 같다.
	FVector3D Rot = mRotationPivot->GetRelativeRotation();
	Rot.z += DeltaTime * mPivotRotationSpeed;
	mRotationPivot->SetRelativeRotationZ(Rot.z);

	if (mSkill3Enable)
	{
		Skill3Update(DeltaTime);
	}

	if (mSkill4Enable)
	{
		Skill4Update(DeltaTime);
	}
}

void CPlayerObject::MoveUp(float DeltaTime)
{
	/*FVector3D Pos = mRootComponent->GetWorldPosition();
	FVector3D Dir = mRootComponent->GetAxis(EAxis::Y);

	mRootComponent->SetWorldPos(Pos + Dir * DeltaTime * 3.f);*/


	mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y));
}

void CPlayerObject::MoveDown(float DeltaTime)
{

	mMovement->AddMove(mRootComponent->GetAxis(EAxis::Y) * -1);
}

void CPlayerObject::RotationZ(float DeltaTime)
{
	/*FVector3D Rot = mRootComponent->GetWorldRotation();
	mRootComponent->SetWorldRotationZ(Rot.z + 90.f * DeltaTime);*/

	mRotation->AddMoveZ(90.f);
}

void CPlayerObject::RotationZInv(float DeltaTime)
{
	/*FVector3D Rot = mRootComponent->GetWorldRotation();
	mRootComponent->SetWorldRotationZ(Rot.z - 90.f * DeltaTime);*/

	mRotation->AddMoveZ(-90.f);
}

void CPlayerObject::Fire(float DeltaTime)
{
	// 총알을 만들 것이고
	CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

	CSceneComponent* Root = Bullet->GetRootComponent();
	// 총알의 시작 위치 == 내 월드 위치
	Root->SetWorldPos(mRootComponent->GetWorldPosition());
	Root->SetWorldRotation(mRootComponent->GetWorldRotation());
	Root->SetWorldScale(50.f, 50.f, 1.f);
	Bullet->SetLifeTime(2.f);


}

void CPlayerObject::Skill1(float DeltaTime)
{

	// 스킬을 누르는 동안
	if (!mSkill1Object)
	{
		// 발사할 총알을 만든다.
		mSkill1Object = mScene->CreateObj<CBulletObject>("Skill1Bullet");
		mSkill1Object->SetBulletSpeed(0.f);
	}

	CSceneComponent* Root = mSkill1Object->GetRootComponent();
	Root->SetWorldPos(mRootComponent->GetWorldPosition() + mRootComponent->GetAxis(EAxis::Y));
	Root->SetWorldRotation(mRootComponent->GetWorldRotation());

	FVector3D Scale = Root->GetWorldScale();

	Scale.x += 2.f * DeltaTime;
	Scale.y += 2.f * DeltaTime;

	if (Scale.x >= 4.f)
	{
		Scale.x = 4.f;
	}

	if (Scale.y >= 4.f)
	{
		Scale.y = 4.f;
	}

	mSkill1Object->GetRootComponent()->SetWorldScale(Scale);


}

void CPlayerObject::Skill1Fire(float DeltaTime)
{
	mSkill1Object->SetBulletSpeed(2.f);
	mSkill1Object = nullptr;

}

void CPlayerObject::Skill2(float DeltaTime)
{
	// 총알을 만들고
	CTornadoBullet* Bullet = mScene->CreateObj<CTornadoBullet>("TornadoBullet");

	CSceneComponent* Root = Bullet->GetRootComponent();

	// 총알의 시작 위치 == 내 월드 위치
	Root->SetWorldPos(mRootComponent->GetWorldPosition());
	Root->SetWorldRotation(mRootComponent->GetWorldRotation());
	Bullet->SetBulletSpeed(5.f);
	Bullet->SetLifeTime(1.f);
}

void CPlayerObject::Skill3(float DeltaTime)
{

	// 스킬 발동중임 ?
	if (!mSkill3Enable)
	{
		mSkill3Enable = true;
		mSkill3Time = 3.f;
		mSkill3TimeAcc = 0.f;
		mSkill3Interval = 0.2f;
	}
}

void CPlayerObject::Skill3Update(float DeltaTime)
{
	mSkill3TimeAcc += DeltaTime;

	if (mSkill3TimeAcc >= mSkill3Interval)
	{
		mSkill3TimeAcc -= mSkill3Interval;

		// 총알 발사
		CBulletObject* Bullet = mScene->CreateObj<CBulletObject>("Bullet");

		CSceneComponent* Root = Bullet->GetRootComponent();
		// 총알의 시작 위치 == 내 월드 위치
		Root->SetWorldPos(mSub->GetWorldPosition());
		Root->SetWorldRotation(mRootComponent->GetWorldRotation());
		Bullet->SetLifeTime(2.f);
		Bullet->SetBulletSpeed(1.5f);

		Bullet = mScene->CreateObj<CBulletObject>("Bullet");
		Root = Bullet->GetRootComponent();
		// 총알의 시작 위치 == 내 월드 위치
		Root->SetWorldPos(mSub1->GetWorldPosition());
		Root->SetWorldRotation(mRootComponent->GetWorldRotation());
		Bullet->SetLifeTime(2.f);
		Bullet->SetBulletSpeed(1.5f);
	}

	mSkill3Time -= DeltaTime;

	if (mSkill3Time <= 0.f)
	{
		mSkill3Enable = false;
	}
}

void CPlayerObject::Skill4(float DeltatTime)
{
	if (!mSkill4Enable)
	{
		mSkill4Enable = true;
		mSkill4Time = 5.f;
		mSkill4TimeAcc = 0.f;
		mSkill4ReadyTime = 2.l;

		mPivotRotationSpeed = 360.f;
		mSkill4State = ESkill4State::Expansion;
		
	}
}

void CPlayerObject::Skill4Update(float DeltaTime)
{
	// 스킬 4 구현
	mSkill4TimeAcc += DeltaTime;

	switch (mSkill4State)
	{



	case ESkill4State::Expansion:
		// DeltaTime / mSkill4ReadyTime 을 하게 되면 확장하는 시간 2초라는 시간에 대해서
		// 현재 DeltaTime 이 몇 퍼센트의 시간이 흘렀는지를 구해낼 수 있다.

		mSkill4Range += DeltaTime / mSkill4ReadyTime * mSkill4RangeLength;

		if (mSkill4TimeAcc >= mSkill4ReadyTime)
			// 예를 들어 시작하고 나서 2초가 지나면
		{
			mSkill4TimeAcc -= mSkill4ReadyTime;
			mSkill4Range = mSkill4MaxRange;
			mSkill4State = ESkill4State::Maintain;
		}

		mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);
		mSub1->SetRelativePos(mSkill4Range, 0.f, 0.f);


		break;



	case ESkill4State::Maintain:
		if (mSkill4TimeAcc >= mSkill4Time)
		{
			mSkill4TimeAcc = 0.f;
			mSkill4State = ESkill4State::Reducion;
		}
		break;


	case ESkill4State::Reducion:
		mSkill4Range -= DeltaTime / mSkill4ReadyTime * mSkill4RangeLength;

		if (mSkill4TimeAcc >= mSkill4ReadyTime)
		{
			mSkill4Enable = false;
			mSkill4TimeAcc = 0;
			mSkill4Range = 200.f;
			mSkill4State = ESkill4State::Expansion;
			mPivotRotationSpeed = 180.f;
		}
		mSub->SetRelativePos(-mSkill4Range, 0.f, 0.f);
		mSub1->SetRelativePos(mSkill4Range, 0.f, 0.f);
		break;

	//default:
	//	break;
	}

}

void CPlayerObject::Skill5(float DeltaTime)
{
	// 8방향으로 총알 발사
	FVector3D Dir = mRoot->GetAxis(EAxis::Y);
	FVector3D Rot = mRoot->GetWorldRotation();

	FMatrix matRot;
	matRot.RotationZ(45.f);

	for (int i = 0; i < 8; i++)
	{
		CTalonR* Bullet = mScene->CreateObj<CTalonR>("TalonBullet");

		CSceneComponent* Root = Bullet->GetRootComponent();
		FVector3D Pos = mRoot->GetWorldPosition();
		Root->SetWorldPos(Pos + Dir);
		Root->SetWorldRotation(Rot);
		Root->SetWorldScale(50.f, 50.f, 1.f);

		Rot.z += 45;

		Dir = Dir.TransformNormal(matRot);
		Dir.Normalize();
		Bullet->SetTarget(this);
	}


}
