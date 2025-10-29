#include "PlayerObject.h"

#include "../../Component/SceneComponent/StaticMeshComponent.h"
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

	mRoot->SetMesh("CenterRect");
	mRoot->SetShader("ColorMeshShader");

	mRoot->SetWorldPos(0.f, 0.f, 5.5f);
	SetRootComponent(mRoot);

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
	mScene->GetInput()->AddBindKey("MoveUP", 'W');
	mScene->GetInput()->AddBindFunction("MoveUp", EInputType::Hold, this, &CPlayerObject::MoveUp);

	mScene->GetInput()->AddBindKey("MoveDown", 'S');
	mScene->GetInput()->AddBindFunction("MoveDown", EInputType::Hold, this, &CPlayerObject::MoveDown);


	// 회전
	mScene->GetInput()->AddBindKey("RotationZ", 'D');
	mScene->GetInput()->AddBindFunction("RotationZ", EInputType::Hold, this, &CPlayerObject::RotationZ);

	mScene->GetInput()->AddBindKey("RotationZ", 'D');
	mScene->GetInput()->AddBindFunction("RotationZ", EInputType::Hold, this, &CPlayerObject::RotationZ);


	// 총알 발사
	mScene->GetInput()->AddBindKey("Fire", VK_SPACE);
	mScene->GetInput()->AddBindFunction("Fire", EInputType::Hold, this, &CPlayerObject::Fire);

	// 스킬1
	mScene->GetInput()->AddBindKey("Skill1", '1');
	mScene->GetInput()->ChangeKeyCtrl("Skill1", true);

	mScene->GetInput()->AddBindFunction("Skill1", EInputType::Hold, this, &CPlayerObject::Skill1);
	mScene->GetInput()->AddBindFunction("Skill1", EInputType::Up, this, &CPlayerObject::Skill1Fire);

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
	FVector3D Pos = mRootComponent->GetWorldPosition();
	FVector3D Dir = mRootComponent->GetAxis(EAxis::Y);
}

void CPlayerObject::MoveDown(float DeltaTime)
{
}

void CPlayerObject::RotationZ(float DeltaTime)
{
}

void CPlayerObject::RotationZInv(float DeltaTime)
{
}

void CPlayerObject::Fire(float DeltaTime)
{
}

void CPlayerObject::Skill1(float DeltaTime)
{
}

void CPlayerObject::Skill1Fire(float DeltaTime)
{
}

void CPlayerObject::Skill2(float DeltaTime)
{
}

void CPlayerObject::Skill3(float DeltaTime)
{
}

void CPlayerObject::Skill3Update(float DeltaTime)
{
}

void CPlayerObject::Skill4(float DeltatTime)
{
}

void CPlayerObject::Skill4Update(float DeltaTime)
{
}

void CPlayerObject::Skill5(float DeltaTime)
{
}
