#pragma once
#include "../../GameInfo.h"

#define QUADTREE_DIVISION_COUNT 10
#define QUADTREE_DEPTH_MAX 4

class CCollisionQuadTreeNode
{
	friend class CCollisionQuadTree;
public:
	CCollisionQuadTreeNode();
	~CCollisionQuadTreeNode();

private:
	// 부모 노트
	CCollisionQuadTreeNode* mParent = nullptr;
	// 자식노드 4개
	CCollisionQuadTreeNode* mChild[4] = {};
	// 노드의 중앙 위치
	FVector2D mCenter;
	// 노드의 길이? 크기
	FVector2D mSize;
	// 트리의 깊이
	int mDepth = QUADTREE_DEPTH_MAX;
	// 몇개라면 분할 할건지
	int mDivisionCount = QUADTREE_DIVISION_COUNT;
	// 해당 노드에 속한 충돌체들
	vector<CSharedPtr<class CColliderBase>> mColliderList;

public:
	void AddCollider(class CColliderBase* Collider);
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

public:
	void SetDivisionCount(int Count);

public:
	bool Init();
	void AddCollider(class CColliderBase* Collder);
	void Update(float DeltaTime);
};

