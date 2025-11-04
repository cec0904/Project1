#include "SceneCollision.h"
#include "../../Component/Collider/ColliderBase.h"
#include "../Collision/CollisionQuadTree.h"

CSceneCollision::CSceneCollision()
{
}
CSceneCollision::~CSceneCollision()
{
	SAFE_DELETE(mQuadTree);
}
void CSceneCollision::AddCollider(CColliderBase* Collider)
{
	if (Collider->GetColliderType() == EColliderType::Collider2D)
	{
		mColliderList2D.emplace_back(Collider);
	}
	else
	{
		mColliderList3D.emplace_back(Collider);
	}
}
bool CSceneCollision::Init()
{
	mQuadTree = new CCollisionQuadTree;

	mQuadTree->mScene = mScene;

	if (!mQuadTree->Init())
	{
		return false;
	}

	return true;
}
void CSceneCollision::Update(float DeltaTime)
{

	// 쿼드트리를 이용해서 카메라 좌표를 먼저 갱신해야 한다.
	mQuadTree->Update(DeltaTime);

	size_t Size = mColliderList2D.size();
	for (size_t i = 0; i < Size;)
	{
		if (!mColliderList2D[i]->IsActive())
		{
			// 그냥 덮어씌우기
			if (1 < Size - 1)
			{
				mColliderList2D[i] = mColliderList2D[Size - 1];
			}
			mColliderList2D.pop_back();
			Size--;
			continue;
		}
		else if (!mColliderList2D[i]->IsEnable())
		{
			i++;
			continue;
		}

		// 쿼드트리 만들고 나서
		// 여기에 쿼드트리에 등록
		mQuadTree->AddCollider(mColliderList2D[i]);
		i++;
	}


	// 충돌 검사
	mQuadTree->Collision(DeltaTime);
}