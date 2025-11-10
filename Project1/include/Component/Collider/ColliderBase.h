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


	//충돌 프로파일 
	FCollisionProfile* mProfile = nullptr;
	//충돌 중 여부 
	bool mCollision = false;
	
	// 충돌 시점 함수!
	// 충돌 시작
	// 충돌 위치, 누구랑 충돌했는지
	function<void(const FVector3D&, CColliderBase*)> mCollisionBeginFunc;
	// 충돌 종료
	function<void(CColliderBase*)> mCollisionEndFunc;

	//디버그용 출력 해주기 
#ifdef _DEBUG

	//위치용 상수버퍼 
	class CTransformCBuffer* mTransformCBuffer = nullptr;
	//충돌체 상수버퍼 
	class CColliderCBuffer* mCBuffer = nullptr;
	//메쉬
	CSharedPtr<class CMesh> mMesh;
	//쉐이더 
	CSharedPtr<class CShader> mShader;
	// 회전 유무
	bool mEnableRotation = false;

#endif // _DEBUG

public:
	FCollisionProfile* GetProfile() const
	{
		return mProfile;
	}

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
	void SetCollisionProfile(const std::string& Name);
	void CallCollisionBegin(const FVector3D& HitPoint, CColliderBase* Dest);
	void CallCollisionEnd(CColliderBase* Dest);

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

public:
	//순수가상함수 
	virtual bool Collision(FVector3D& HitPoint, CColliderBase* Dest) = 0;

public:
	template<typename T>
	void SetCollisionBeginFunc(T* Obj, void(T::* Func)(const FVector3D&, CColliderBase*))
	{
		mCollisionBeginFunc = bind(Func, Obj, placeholders::_1, placeholders::_2);
	}

	template<typename T>
	void SetCollisionEndFunc(T* Obj, void(T::* Func)(CColliderBase*))
	{
		mCollisionEndFunc = bind(Func, Obj, placeholders::_1);
	}


};

