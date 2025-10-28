#include "BulletObject.h"
#include "../../Component/SceneComponent/StaticMeshComponent.h"

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
	mRoot->SetMesh("CenterRect");
	mRoot->SetShader("ColorMeshShader");
	mRoot->SetWorldScale(0.5f, 0.5f, 1.f);

	SetRootComponent(mRoot);

	return true;
}

void CBulletObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	FVector3D Pos = mRoot->GetWorldPosition();
	// 이동할 위치의 새로운 위치값 = 내 위치 + 내 Y축 * 속도 * DeltaTime
	mRoot->SetWorldPos(Pos + mRootComponent->GetAxis(EAxis::Y) * mSpeed * DeltaTime);
}
