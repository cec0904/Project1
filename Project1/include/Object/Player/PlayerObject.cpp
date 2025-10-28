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

	return true;
}

void CPlayerObject::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);
}

void CPlayerObject::MoveUp(float DeltaTime)
{
}

void CPlayerObject::MoveDown(float DeltaTime)
{
}

void CPlayerObject::RoationZ(float DeltaTime)
{
}

void CPlayerObject::RoationZInv(float DeltaTime)
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
