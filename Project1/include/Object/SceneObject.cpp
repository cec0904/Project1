#include "SceneObject.h"

#include "../Component/SceneComponent/SceneComponent.h"

CSceneObject::CSceneObject()
{
}

CSceneObject::CSceneObject(const CSceneObject& Obj)
{
}

CSceneObject::CSceneObject(CSceneObject&& Obj)
{
}

CSceneObject::~CSceneObject()
{
}

void CSceneObject::SetRootComponent(CSceneComponent* Root)
{
	mRootComponent = Root;
}

bool CSceneObject::Init()
{
	return true;
}

bool CSceneObject::Init(const char* FileName)
{
	return true;
}

void CSceneObject::PreUpdate(float DeltaTime)
{
	// NonSceneComponent 호출하기
	auto iter = mNonSceneComponent.begin();
	auto iterEnd = mNonSceneComponent.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mNonSceneComponent.erase(iter);
			iterEnd = mNonSceneComponent.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;
			continue;
		}
		(*iter)->PreUpdate(DeltaTime);
		iter++;
	}



	mRootComponent->PreUpdate(DeltaTime);
}

void CSceneObject::Update(float DeltaTime)
{
	//NonSceneComponent 호출하기 
	auto iter = mNonSceneComponent.begin();
	auto iterEnd = mNonSceneComponent.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mNonSceneComponent.erase(iter);
			iterEnd = mNonSceneComponent.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Update(DeltaTime);
		++iter;
	}



	mRootComponent->Update(DeltaTime);

	// LifeTime 검사
	if (mLifeTime > 0)
	{
		mLifeTime -= DeltaTime;
		if (mLifeTime <=0)
		{
			Destroy();
		}
	}
}

void CSceneObject::PostUpdate(float DeltaTime)
{
	//NonSceneComponent 호출하기 
	auto iter = mNonSceneComponent.begin();
	auto iterEnd = mNonSceneComponent.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mNonSceneComponent.erase(iter);
			iterEnd = mNonSceneComponent.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);
		++iter;
	}


	mRootComponent->PostUpdate(DeltaTime);
}

void CSceneObject::Collision(float DeltaTime)
{
	//NonSceneComponent 호출하기 
	auto iter = mNonSceneComponent.begin();
	auto iterEnd = mNonSceneComponent.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mNonSceneComponent.erase(iter);
			iterEnd = mNonSceneComponent.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Collision(DeltaTime);
		++iter;
	}


	mRootComponent->Collision(DeltaTime);
}

void CSceneObject::PreRender()
{
	//NonSceneComponent 호출하기 
	auto iter = mNonSceneComponent.begin();
	auto iterEnd = mNonSceneComponent.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mNonSceneComponent.erase(iter);
			iterEnd = mNonSceneComponent.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PreRender();
		++iter;
	}

	mRootComponent->PreRender();
}

void CSceneObject::Render()
{
	//NonSceneComponent 호출하기 
	auto iter = mNonSceneComponent.begin();
	auto iterEnd = mNonSceneComponent.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mNonSceneComponent.erase(iter);
			iterEnd = mNonSceneComponent.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->Render();
		++iter;
	}

	mRootComponent->Render();
}

void CSceneObject::PostRender()
{
	//NonSceneComponent 호출하기 
	auto iter = mNonSceneComponent.begin();
	auto iterEnd = mNonSceneComponent.end();

	for (; iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mNonSceneComponent.erase(iter);
			iterEnd = mNonSceneComponent.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			++iter;
			continue;
		}

		(*iter)->PostRender();
		++iter;
	}


	mRootComponent->PostRender();
}

CSceneObject* CSceneObject::Clone()
{
	return nullptr;
}

#pragma region Trasnfrom
// Transform 함수들 

const FMatrix& CSceneObject::GetScaleMatrix() const
{
	return mRootComponent->GetScaleMatrix();
}

const FMatrix& CSceneObject::GetRotationMatrix() const
{
	return mRootComponent->GetRotationMatrix();
}

const FMatrix& CSceneObject::GetTranslateMatrix() const
{
	return mRootComponent->GetTranslateMatrix();
}

const FMatrix& CSceneObject::GetWorldMatrix() const
{
	return mRootComponent->GetWorldMatrix();
}

const FVector3D& CSceneObject::GetAxis(EAxis::Type Axis) const
{
	return mRootComponent->GetAxis(Axis);
}

const FVector3D& CSceneObject::GetRelativeScale() const
{
	return mRootComponent->GetRelativeScale();
}

const FVector3D& CSceneObject::GetRelativeRotation() const
{
	return mRootComponent->GetRelativeRotation();
}

const FVector3D& CSceneObject::GetRelativePosition() const
{
	return mRootComponent->GetRelativePosition();
}

const FVector3D& CSceneObject::GetWorldScale() const
{
	return mRootComponent->GetWorldScale();
}

const FVector3D& CSceneObject::GetWorldRotation() const
{
	return mRootComponent->GetWorldRotation();
}

const FVector3D& CSceneObject::GetWorldPosition() const
{
	return mRootComponent->GetWorldPosition();
}

void CSceneObject::SetRelativeScale(const FVector3D& Scale)
{
	mRootComponent->SetRelativeScale(Scale);
}

void CSceneObject::SetRelativeScale(float x, float y, float z)
{
	mRootComponent->SetRelativeScale(x, y, z);
}

void CSceneObject::SetRelativeScale(const FVector2D& Scale)
{
	mRootComponent->SetRelativeScale(Scale);
}

void CSceneObject::SetRelativeScale(float x, float y)
{
	mRootComponent->SetRelativeScale(x, y);
}

void CSceneObject::SetRelativeRotation(const FVector3D& Rot)
{
	mRootComponent->SetRelativeRotation(Rot);
}

void CSceneObject::SetRelativeRotation(float x, float y, float z)
{
	mRootComponent->SetRelativeRotation(x, y, z);
}

void CSceneObject::SetRelativeRotation(const FVector2D& Rot)
{
	mRootComponent->SetRelativeRotation(Rot);
}

void CSceneObject::SetRelativeRotation(float x, float y)
{
	mRootComponent->SetRelativeRotation(x, y);
}

void CSceneObject::SetRelativeRotationX(float x)
{
	mRootComponent->SetRelativeRotationX(x);
}

void CSceneObject::SetRelativeRotationY(float y)
{
	mRootComponent->SetRelativeRotationY(y);
}

void CSceneObject::SetRelativeRotationZ(float z)
{
	mRootComponent->SetRelativeRotationZ(z);
}

void CSceneObject::SetRelativeRotationAxis(float Angle,
	const FVector3D& Axis)
{
	mRootComponent->SetRelativeRotationAxis(Angle, Axis);
}

void CSceneObject::SetRelativePos(const FVector3D& Pos)
{
	mRootComponent->SetRelativePos(Pos);
}

void CSceneObject::SetRelativePos(float x, float y, float z)
{
	mRootComponent->SetRelativePos(x, y, z);
}

void CSceneObject::SetRelativePos(const FVector2D& Pos)
{
	mRootComponent->SetRelativePos(Pos);
}

void CSceneObject::SetRelativePos(float x, float y)
{
	mRootComponent->SetRelativePos(x, y);
}

void CSceneObject::SetWorldScale(const FVector3D& Scale)
{
	mRootComponent->SetWorldScale(Scale);
}

void CSceneObject::SetWorldScale(float x, float y, float z)
{
	mRootComponent->SetWorldScale(x, y, z);
}

void CSceneObject::SetWorldScale(const FVector2D& Scale)
{
	mRootComponent->SetWorldScale(Scale);
}

void CSceneObject::SetWorldScale(float x, float y)
{
	mRootComponent->SetWorldScale(x, y);
}

void CSceneObject::SetWorldRotation(const FVector3D& Rot)
{
	mRootComponent->SetWorldRotation(Rot);
}

void CSceneObject::SetWorldRotation(float x, float y, float z)
{
	mRootComponent->SetWorldRotation(x, y, z);
}

void CSceneObject::SetWorldRotation(const FVector2D& Rot)
{
	mRootComponent->SetWorldRotation(Rot);
}

void CSceneObject::SetWorldRotation(float x, float y)
{
	mRootComponent->SetWorldRotation(x, y);
}

void CSceneObject::SetWorldRotationX(float x)
{
	mRootComponent->SetWorldRotationX(x);
}

void CSceneObject::SetWorldRotationY(float y)
{
	mRootComponent->SetWorldRotationY(y);
}

void CSceneObject::SetWorldRotationZ(float z)
{
	mRootComponent->SetWorldRotationZ(z);
}

void CSceneObject::SetWorldRotationAxis(float Angle,
	const FVector3D& Axis)
{
	mRootComponent->SetWorldRotationAxis(Angle, Axis);
}

void CSceneObject::SetWorldPos(const FVector3D& Pos)
{
	mRootComponent->SetWorldPos(Pos);
}

void CSceneObject::SetWorldPos(float x, float y, float z)
{
	mRootComponent->SetWorldPos(x, y, z);
}

void CSceneObject::SetWorldPos(const FVector2D& Pos)
{
	mRootComponent->SetWorldPos(Pos);
}

void CSceneObject::SetWorldPos(float x, float y)
{
	mRootComponent->SetWorldPos(x, y);
}

void CSceneObject::AddRelativeScale(const FVector3D& Scale)
{
	mRootComponent->AddRelativeScale(Scale);
}

void CSceneObject::AddRelativeScale(float x, float y, float z)
{
	mRootComponent->AddRelativeScale(x, y, z);
}

void CSceneObject::AddRelativeScale(const FVector2D& Scale)
{
	mRootComponent->AddRelativeScale(Scale);
}

void CSceneObject::AddRelativeScale(float x, float y)
{
	mRootComponent->AddRelativeScale(x, y);
}

void CSceneObject::AddRelativeRotation(const FVector3D& Rot)
{
	mRootComponent->AddRelativeRotation(Rot);
}

void CSceneObject::AddRelativeRotation(float x, float y, float z)
{
	mRootComponent->AddRelativeRotation(x, y, z);
}

void CSceneObject::AddRelativeRotation(const FVector2D& Rot)
{
	mRootComponent->AddRelativeRotation(Rot);
}

void CSceneObject::AddRelativeRotation(float x, float y)
{
	mRootComponent->AddRelativeRotation(x, y);
}

void CSceneObject::AddRelativeRotationX(float x)
{
	mRootComponent->AddRelativeRotationX(x);
}

void CSceneObject::AddRelativeRotationY(float y)
{
	mRootComponent->AddRelativeRotationY(y);
}

void CSceneObject::AddRelativeRotationZ(float z)
{
	mRootComponent->AddRelativeRotationZ(z);
}

void CSceneObject::AddRelativePos(const FVector3D& Pos)
{
	mRootComponent->AddRelativePos(Pos);
}

void CSceneObject::AddRelativePos(float x, float y, float z)
{
	mRootComponent->AddRelativePos(x, y, z);
}

void CSceneObject::AddRelativePos(const FVector2D& Pos)
{
	mRootComponent->AddRelativePos(Pos);
}

void CSceneObject::AddRelativePos(float x, float y)
{
	mRootComponent->AddRelativePos(x, y);
}

void CSceneObject::AddWorldScale(const FVector3D& Scale)
{
	mRootComponent->AddWorldScale(Scale);
}

void CSceneObject::AddWorldScale(float x, float y, float z)
{
	mRootComponent->AddWorldScale(x, y, z);
}

void CSceneObject::AddWorldScale(const FVector2D& Scale)
{
	mRootComponent->AddWorldScale(Scale);
}

void CSceneObject::AddWorldScale(float x, float y)
{
	mRootComponent->AddWorldScale(x, y);
}

void CSceneObject::AddWorldRotation(const FVector3D& Rot)
{
	mRootComponent->AddWorldRotation(Rot);
}

void CSceneObject::AddWorldRotation(float x, float y, float z)
{
	mRootComponent->AddWorldRotation(x, y, z);
}

void CSceneObject::AddWorldRotation(const FVector2D& Rot)
{
	mRootComponent->AddWorldRotation(Rot);
}

void CSceneObject::AddWorldRotation(float x, float y)
{
	mRootComponent->AddWorldRotation(x, y);
}

void CSceneObject::AddWorldRotationX(float x)
{
	mRootComponent->AddWorldRotationX(x);
}

void CSceneObject::AddWorldRotationY(float y)
{
	mRootComponent->AddWorldRotationY(y);
}

void CSceneObject::AddWorldRotationZ(float z)
{
	mRootComponent->AddWorldRotationZ(z);
}

void CSceneObject::AddWorldPos(const FVector3D& Pos)
{
	mRootComponent->AddWorldPos(Pos);
}

void CSceneObject::AddWorldPos(float x, float y, float z)
{
	mRootComponent->AddWorldPos(x, y, z);
}

void CSceneObject::AddWorldPos(const FVector2D& Pos)
{
	mRootComponent->AddWorldPos(Pos);
}

void CSceneObject::AddWorldPos(float x, float y)
{
	mRootComponent->AddWorldPos(x, y);
}

#pragma endregion Transform


