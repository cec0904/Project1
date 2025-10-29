#include "CameraComponent.h"
#include "../../Scene/Scene.h"
#include "../../Scene/CameraManager/CameraManager.h"

CCameraComponent::CCameraComponent()
{
}

CCameraComponent::CCameraComponent(const CCameraComponent& Com)
{
}

CCameraComponent::CCameraComponent(CCameraComponent&& Com)
{
}

CCameraComponent::~CCameraComponent()
{
}

void CCameraComponent::SetProjectionType(ECameraProjectionType Type)
{
	mProjType = Type;

	switch (mProjType)
	{
	case ECameraProjectionType::Perspective:	// 원근
		mmatProj = DirectX::XMMatrixPerspectiveLH(DirectX::XMConvertToRadians(mViewAngle), mWidth / mHeight, 0.5, mViewDistance);
		break;
	case ECameraProjectionType::Ortho:		// 직교
		mmatProj = DirectX::XMMatrixOrthographicOffCenterLH(mWidth / -2.f, mWidth/2.f, mHeight/ -2.f, mHeight/2.f,0, mViewDistance);
		break;
	default:
		break;
	}


}

bool CCameraComponent::Init()
{
	if (!CSceneComponent::Init())
	{
		return false;
	}

	SetProjectionType(ECameraProjectionType::Perspective);

	// 처음 생성된 카메라면 뷰타겟으로 지정한다.
	if (!mScene->GetCameraManager()->GetViewTarget())
	{
		mScene->GetCameraManager()->SetViewTarget(this);
	}

	return true;
}
bool CCameraComponent::Init(const char* FileName)
{
	if (!CSceneComponent::Init(FileName))
	{
		return false;
	}

	SetProjectionType(ECameraProjectionType::Perspective);

	if (!mScene->GetCameraManager()->GetViewTarget())
	{
		mScene->GetCameraManager()->SetViewTarget(this);
	}
	return true;
}
void CCameraComponent::PreUpdate(float DeltaTime)
{
	CSceneComponent::PreUpdate(DeltaTime);
}
void CCameraComponent::Update(float DeltaTime)
{
	CSceneComponent::Update(DeltaTime);
}
void CCameraComponent::PostUpdate(float DeltaTime)
{
	CSceneComponent::PostUpdate(DeltaTime);

	/*
		
	*/

	// 카메라 축으로 뷰 행렬을 구성한다.
	mmatView.Identity();	// 뷰행렬 초기화

	// 카메라 축을 뷰행렬에 복사
	for (int i = 0; i < EAxis::End; i++)
	{
		FVector3D Axis = mAxis[i];		// 카메라 축
		memcpy(&mmatView[i][0], &Axis, sizeof(FVector3D));	// 카메라 축을 행렬에 복사
	}




	mmatView.Transpose();

	// 카메라 위로 뷰행렬의 이동 행렬 구성
	for (int i = 0; i < EAxis::End; i++)
	{
		// -X.P, -Y.P, -Z.P
		mmatView[3][i] = -mAxis[i].Dot(mWorldPos);	// 카메라 위치와 카메라 축의 내적
	}

}
void CCameraComponent::Collision(float DeltaTime)
{
	CSceneComponent::Collision(DeltaTime);
}
void CCameraComponent::PreRender()
{
	CSceneComponent::PreRender();
}
void CCameraComponent::Render()
{
	CSceneComponent::Render();
}
void CCameraComponent::PostRender()
{
	CSceneComponent::PostRender();
}
CCameraComponent* CCameraComponent::Clone()
{
	return new CCameraComponent(*this);
}