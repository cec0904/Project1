#include "CameraManager.h"

#include "../../Component/SceneComponent/CameraComponent.h"

CCameraManager::CCameraManager()
{

}
CCameraManager::~CCameraManager()
{

}
void CCameraManager::SetViewTarget(CCameraComponent* ViewTarget)
{
	mViewTarget = ViewTarget;
}

const FMatrix& CCameraManager::GetViewMatrix() const
{
	return mViewTarget->GetWorldMatrix();
}

const FMatrix& CCameraManager::GetProjMatrix() const
{
	return mViewTarget->GetProjMatrix();
}

bool CCameraManager::Init()
{
	return true;
}
void CCameraManager::Update(float DeltaTime)
{
	if (mViewTarget)
	{
		if (!mViewTarget->IsActive())
		{
			mViewTarget == nullptr;
		}
	}
}