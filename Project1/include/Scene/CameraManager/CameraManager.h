#pragma once
#include "../../GameInfo.h"

class CCameraManager
{
	friend class CScene;

private:
	CCameraManager();
	~CCameraManager();

private:
	CSharedPtr<class CCameraComponent> mViewTarget;

public:
	class CCameraComponent* GetViewTarget() const
	{
		return mViewTarget;
	}

	const FMatrix& GetViewMatrix() const;
	const FMatrix& GetProjMatrix() const;

	void SetViewTarget(class CCameraComponent* ViewTarget);

public:
	bool Init();
	void Update(float DeltaTime);
	
};

