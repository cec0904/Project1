#pragma once
#include "../../GameInfo.h"

#define QUADTREE_DIVISION_COUNT 5
#define QUADTREE_DEPTH_MAX 4

class CCollisionQuadTreeNode
{
	friend class CCollisionQuadTree;
public:
	CCollisionQuadTreeNode();
	~CCollisionQuadTreeNode();

private:
	class CScene* mScene = nullptr;
	CCollisionQuadTree* mTree = nullptr;
	// 부모 노드
	CCollisionQuadTreeNode* mParent = nullptr;
	// 자식노드 4개
	CCollisionQuadTreeNode* mChild[4] = {};
	// 노드의 중앙 위치
	FVector2D mCenter;
	// 노드의 길이? 크기
	FVector2D mSize;
	// 트리의 깊이
	int mDepth = 0;
	// 몇개라면 분할 할건지
	int mDivisionCount = QUADTREE_DIVISION_COUNT;
	// 해당 노드에 속한 충돌체들
	vector<CSharedPtr<class CColliderBase>> mColliderList;

public:
	void AddCollider(class CColliderBase* Collider, vector<CCollisionQuadTreeNode*>& NodePool);
	void CreateChild(vector<CCollisionQuadTreeNode*>& NodePool);
	void Collision(float DeltaTime);
	void ReturnNodePool(vector<CCollisionQuadTreeNode*>& NodePool);

private:
	// 충돌체가 이 노드에 속하는지 검사한다.
	bool IsInCollider(class CColliderBase* Collider);

};



class CCollisionQuadTree
{
	friend class CSceneCollision;

private:
	CCollisionQuadTree();
	~CCollisionQuadTree();

private:
	class CScene* mScene = nullptr;
	CCollisionQuadTreeNode* mRoot = nullptr;
	int mDivisionCount = QUADTREE_DIVISION_COUNT;

	// 노드 풀 : 이미 할당된 노드를 재사용하기 위해서
	vector<CCollisionQuadTreeNode*> mNodePool;

	// 재귀를 줄이기 위한 노드 충돌 리스트
	// 노드 내에 2개 이상의 충돌체가 있을 경우에만 충돌 검사를 하겠다.
	// 노드들을 저장하기 위한 리스트
	vector<CCollisionQuadTreeNode*> mCollisionNodeList;

public:
	void SetDivisionCount(int Count);
	void AddCollisionNodeList(CCollisionQuadTreeNode* Node)
	{
		mCollisionNodeList.emplace_back(Node);
	}
	void EraseCollisionNodeList(CCollisionQuadTreeNode* Node);

public:
	bool Init();
	void AddCollider(class CColliderBase* Collder);
	void Update(float DeltaTime);
	void Collision(float DeltaTime);
};

