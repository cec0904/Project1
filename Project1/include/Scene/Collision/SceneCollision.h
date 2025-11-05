#pragma once
#include "../../GameInfo.h"

class CSceneCollision
{
	friend class CScene;

private:
	CSceneCollision();
	~CSceneCollision();

private:
	vector<CSharedPtr<class CColliderBase>> mColliderList2D;

	vector<CSharedPtr<class CColliderBase>> mColliderList3D;

	class CCollisionQuadTree* mQuadTree = nullptr;
	class CScene* mScene = nullptr;

public:
	void AddCollider(class CColliderBase* Collider);

public:
	bool Init();
	void Update(float DeltaTime);
	void Render();
	void ReturnNodePool();
};

