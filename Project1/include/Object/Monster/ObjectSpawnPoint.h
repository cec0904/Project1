#pragma once
#include "../SceneObject.h"

// 스폰할 오브젝트 타입
enum class EObjectSpawnType
{
	None,
	Player,
	Bullet,
	GravityBullet,
	TalonR,
	TornadoBullet,
	GunnerMonster,
	NearingMonster
};

// 스폰하는데 반복여부 ? 한번 또는 반복
enum class EObjectSpawnLoopType
{
	Once,
	Loop
};

// 횟수로 스폰 할것인가
enum class EObjectSpawnCountType
{
	OnceDestroy,	// 생성되고 스폰 포인트 제거
	Loop,			// 무한으로 생성
	CountDestroy	// 일정 수 만큼 생성하고 스폰 포인트 제거
};



class CObjectSpawnPoint :
	public CSceneObject
{
	friend class CScene;

protected:
	CObjectSpawnPoint();
	CObjectSpawnPoint(const CObjectSpawnPoint& Obj);
	CObjectSpawnPoint(CObjectSpawnPoint&& Obj);
	virtual ~CObjectSpawnPoint();

protected:
	CSharedPtr<class CSceneComponent> mRoot;
	// 어떤 오브젝트를 스폰할까
	EObjectSpawnType mSpawnType = EObjectSpawnType::None;

	// 스폰하는데 반복여부
	EObjectSpawnLoopType mSpawnLoopType = EObjectSpawnLoopType::Once;

	// 횟수로 스폰할것인가
	// 5 5번만 반복 스폰하고 그만 스폰할 것이다.
	EObjectSpawnCountType mSpawnCountType = EObjectSpawnCountType::Loop;

	// 스폰 시간
	float mSpawnTime = 0.f;
	float mTime = 0.f;

	// 만약 횟수로 한다면 몇 번 실행시킬건지 횟수도 저장할 것이다.
	int mDestroySpawnCount = 0;

	bool mOnceSpawn = false;

	// 1회 한정 즉시 스폰해준다.
	bool mImmediateSpawn = true;

public:
	CSceneObject* mSpawnObject = nullptr;

public:
	void SetSpawnType(EObjectSpawnType Type)
	{
		mSpawnType = Type;
	}
	void SetSpawnLoopType(EObjectSpawnLoopType Type)
	{
		mSpawnLoopType = Type;
	}
	void SetSpawnCountType(EObjectSpawnCountType Type)
	{
		mSpawnCountType = Type;
	}
	void SetSpawnTime(float Time)
	{
		mSpawnTime = Time;
	}
	void SetDestroySpawnCount(int Count)
	{
		mDestroySpawnCount = Count;
	}
	void SetImmediateSpawn(bool Spawn)
	{
		mImmediateSpawn = Spawn;
	}
	void ClearObject()
	{
		mSpawnObject = nullptr;
	}


public:
	virtual bool Init();
	virtual void Update(float DeltaTime);

private:
	void Spawn();
	void ComputeSpawnCountType();
	bool ComputeSpawnTime(float DeltaTime);

};

