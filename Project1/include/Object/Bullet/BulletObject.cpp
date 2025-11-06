#include "BulletObject.h"
#include "../../Component/NonSceneComponent/MovementComponent.h"
#include "../../Component/SceneComponent/StaticMeshComponent.h"
#include "../../Component/Collider/ColliderAABB2D.h"
#include "../../Share/Log/Log.h"

void CBulletObject::SetBulletCollisionProfile(const string& Name)
{
	mBody->SetCollisionProfile(Name);
}

CBulletObject::CBulletObject()
	:CSceneObject()
{
}

CBulletObject::CBulletObject(const CBulletObject& Obj)
	:CSceneObject(Obj)
{
}

CBulletObject::CBulletObject(CBulletObject&& Obj)
	:CSceneObject(Obj)
{
}

CBulletObject::~CBulletObject()
{
}

bool CBulletObject::Init()
{
	CSceneObject::Init();

	mRoot = CreateComponent<CStaticMeshComponent>();
	mBody = CreateComponent<CColliderAABB2D>();
	mMovement = CreateComponent<CMovementComponent>();


	mRoot->SetMesh("CenterRect");
	mRoot->SetShader("ColorMeshShader");
	mRoot->SetWorldScale(0.5f, 0.5f, 1.f);

	SetRootComponent(mRoot);

	mRoot->AddChild(mBody);
	mBody->SetBoxSize(50.f, 50.f);

	mBody->SetCollisionProfile("PlayerAttack");
	mBody->SetCollisionBeginFunc<CBulletObject>(this, &CBulletObject::CollisionBullet);
	

	// Movement 세팅
	mMovement->SetUpdateComponent(mRoot);
	mMovement->SetMoveAxis(EAxis::Y);
	mMovement->SetMoveSpeed(500.f);


	return true;
}

void CBulletObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	//FVector3D Pos = mRoot->GetWorldPosition();
	//// 이동할 위치의 새로운 위치값 = 내 위치 + 내 Y축 * 속도 * DeltaTime
	//mRoot->SetWorldPos(Pos + mRootComponent->GetAxis(EAxis::Y) * mSpeed * DeltaTime);
}

void CBulletObject::CollisionBullet(const FVector3D& HitPoint, CColliderBase* Dest)
{
	CLog::PrintLog("Bullet Hit Collision", ELogPrintType::All);

	Dest->GetOwner()->Damage(1.f, this);

	Destroy();
}
