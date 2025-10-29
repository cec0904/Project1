﻿#pragma once
#include "../SceneObject.h"

enum class ETalonRState
{
	Expansion,
	Maintain,
	Reducion
};



class CTalonR : public CSceneObject
{
	friend class CScene;

protected:
	// 그려질 메쉬
	CSharedPtr<class CStaticMeshComponent> mMesh;

	float mSpeed = 300.f;
	ETalonRState mState = ETalonRState::Expansion;
	CSharedPtr<CSceneObject> mTarget;

	// 스킬 커지는 시간
	float mTime = 5.f;
	float mTimeAcc = 0.f;
	float mReadyTime = 1.f;		// 확장, 축소하는데 걸리는 시간
	float mMaxRange = 400.f;
	float mRangeLength = 200.f;
	float mRange = 0.f;
	// 스킬 다시 작아지는 시간
	
	float mPivotRotationSpeed = 180.f;

public:
	float GetBulletSpeed() const
	{
		return mSpeed;
	}
	void SetBulletSpeed(const float& Speed)
	{
		mSpeed = Speed;
	}
	void SetTarget(CSceneObject* Target)
	{
		mTarget = Target;
	}

protected:
	CTalonR();
	CTalonR(const CTalonR& Obj);
	CTalonR(CTalonR&& Obj);
	virtual ~CTalonR();

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);


};

