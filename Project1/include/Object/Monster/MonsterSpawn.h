#pragma once
#include "../SceneObject.h"
#include "MonsterObject.h"


class CMonsterSpawn : protected CSceneObject
{
	friend class CScene;

	CMonsterSpawn();
	CMonsterSpawn(const CMonsterSpawn& Obj);
	CMonsterSpawn(CMonsterSpawn&& Obj);
	virtual ~CMonsterSpawn();

protected:
	// 몬스터 상태
	bool mAlive = true;	// false 면 죽은 상태
	//bool mDeath = true;	// fasle 면 아직 안죽었다. true면 5초뒤에 IsAlive로 바꿔주자
	
	FVector3D mDeathMonPos;

	list<CSharedPtr<CSceneObject>>* m_list_ptr = nullptr;

	class CSceneObject* DeathMonster = nullptr;
	float MonsterRespawnTime = 5.f;
	float MonsterDeathTime = 0.f;

public:
	bool IsAlive()
	{
		m_list_ptr = mScene->Getlist();

		list<CSharedPtr<CSceneObject>>::iterator iter;
		list<CSharedPtr<CSceneObject>>::iterator iterEnd = m_list_ptr->end();

		for (iter = m_list_ptr->begin(); iter != iterEnd;)
		{
			if (!(*iter)->IsActive())
			{
				mDeathMonPos = m_list_ptr->front().Get()->GetWorldPosition();
			}
		}
		return mAlive;
	}
	
	/*bool IsDeath()
	{
		return mDeath;
	}*/


	virtual void MonsterRespawn(float DeltaTime, class CseneObject* Obj);

};

