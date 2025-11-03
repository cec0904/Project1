#pragma once
#include "../SceneComponent/SceneComponent.h"



class CColliderBase : public CSceneComponent
{
	friend class CScene;
	friend class CSceneObject;

protected:
	CColliderBase();
	CColliderBase(const CColliderBase& Com);
	CColliderBase(CColliderBase&& Com);
	virtual ~CColliderBase();

protected:
	// 2D 인지 3D 인지
	EColliderType mColliderType;

	// 충돌 모양
	EColliderShape mColliderShape;

	// 충돌 정보
	FVector3D mMin;
	FVector3D mMax;

public:
	EColliderType GetColliderType()
	{
		return mColliderType;
	}

	EColliderShape GetColliderShape()
	{
		return mColliderShape;
	}

	const FVector3D& GetMin()
	{
		return mMin;
	}

	const FVector3D& GetMax()
	{
		return mMax;
	}


public:
	virtual bool Init();
	virtual bool Init(const char* FileName);
	virtual void PreUpdate(float DeltaTime);
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual void Collision(float DeltaTime);
	virtual void PreRender();
	virtual void Render();
	virtual void PostRender();
	virtual CColliderBase* Clone();


};

