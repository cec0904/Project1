#include "GravitonSurge.h"
#include "../../Component/SceneComponent/StaticMeshComponent.h"
#include "../../Component/NonSceneComponent/MovementComponent.h"
#include "../../Component/NonSceneComponent/RotationComponent.h"

CGravitionSurge::CGravitionSurge()
{
}

CGravitionSurge::CGravitionSurge(const CGravitionSurge& Obj)
{
}

CGravitionSurge::CGravitionSurge(CGravitionSurge&& Obj)
{
}

CGravitionSurge::~CGravitionSurge()
{
}

bool CGravitionSurge::Init()
{
	if (!CSceneObject::Init())
	{
		return false;
	}

	mMesh = CreateComponent<CStaticMeshComponent>();
	mMovement = CreateComponent<CMovementComponent>();


	mMovement->SetUpdateComponent(mMesh);
	mMovement->SetMoveAxis(EAxis::Y);
	mMovement->SetMoveSpeed(500.f);

	mMesh->SetMesh("CenterRect");
	mMesh->SetShader("ColorMeshShader");
	mMesh->SetWorldScale(0.5f, 0.5f, 1.f);

	SetRootComponent(mMesh);

	return true;
}

void CGravitionSurge::PreUpdate(float DeltaTime)
{
	CSceneObject::PreUpdate(DeltaTime);
	FVector3D Pos = mMesh->GetWorldPosition();
	FVector3D Dir = mMesh->GetAxis(EAxis::Y);

	

}

void CGravitionSurge::Update(float DeltaTime)
{
	CSceneObject::Update(DeltaTime);
}