#pragma once
#include "../Share/Object/Object.h"

class CComponent : public CObject
{
	// 씬이랑 오브젝트 모두 사용할 것 같다.
	friend class CScene;
	friend class CSceneObject;

protected:
	CComponent();
	CComponent(const CComponent& Com);
	CComponent(CComponent&& Com);
	virtual ~CComponent();

protected:
	class CScene* mScene = nullptr;
	class CSceneObject* mOwnerObject = nullptr;
	string mName;

public:
	class CScene* GetScene() const
	{
		return mScene;
	}
	class CSceneObject* GetOwner() const
	{
		return mOwnerObject;
	}
	const char* GetName() const
	{
		// c_str() 함수는 string이 가지고 있는 문자열 포인터를 반환한다.
		return mName.c_str();
	}
	void SetName(const string& Name)
	{
		mName = Name;
	}

	// 시점 함수
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
	virtual CComponent* Clone();


};

