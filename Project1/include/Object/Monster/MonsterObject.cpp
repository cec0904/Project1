#include "MonsterObject.h"
#include "../../Component/SceneComponent/StaticMeshComponent.h"
#include "../../Object/Bullet/BulletObject.h"
#include "../../Scene/Scene.h"
#include "../../Component/Collider/ColliderAABB2D.h"

#include <sstream>


CMonsterObject::CMonsterObject()
{
}

CMonsterObject::CMonsterObject(const CMonsterObject& Obj)
	: CSceneObject(Obj)
{
}

CMonsterObject::CMonsterObject(CMonsterObject&& Obj)
	: CSceneObject(Obj)
{
}

CMonsterObject::~CMonsterObject()
{
}

bool CMonsterObject::Init()
{
	if (!CSceneObject::Init())
	{
		return false;
	}

	mRoot = CreateComponent<CStaticMeshComponent>();
	mBody = CreateComponent<CColliderAABB2D>();

	mRoot->SetMesh("CenterRect");
	mRoot->SetShader("ColorMeshShader");
	mRoot->SetWorldScale(100.f, 100.f);

	SetRootComponent(mRoot);

	mRoot->AddChild(mBody);
	mBody->SetBoxSize(100.f, 100.f);
	mBody->SetCollisionProfile("Monster");

	return true;

}
void CMonsterObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);

	if (!mTarget->IsActive())
	{
		mTarget = nullptr;
	}

	else if (mTarget->IsEnable())
	{
	}

}
