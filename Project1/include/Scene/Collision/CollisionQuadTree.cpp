#include "CollisionQuadTree.h"

#include "../../Component/Collider/ColliderBase.h"
#include "../../Scene/Scene.h"
#include "../../Scene/CameraManager/CameraManager.h"
#include "../../Component/SceneComponent/CameraComponent.h"
#include "../../GameManager/Device/Device.h"

CCollisionQuadTreeNode::CCollisionQuadTreeNode()
{
}

CCollisionQuadTreeNode::~CCollisionQuadTreeNode()
{
}


//쿼드 트리 
CCollisionQuadTree::CCollisionQuadTree()
{
}

CCollisionQuadTree::~CCollisionQuadTree()
{
	SAFE_DELETE(mRoot);
}

void CCollisionQuadTree::SetDivisionCount(int Count)
{
	mDivisionCount = Count;
}

bool CCollisionQuadTree::Init()
{
	// 루트노드 만들어주기
	mRoot = new CCollisionQuadTreeNode;

	// 해상도 가져오기
	// 쿼드 트리의 노드는 해상도보다 좀 더 넓게 검사해야 한다.
	// 왜냐하면 화면에 짤리는 오브젝트 들도 충돌하는지 검사해야 하기 때문이다.

	const FResolution& RS = CDevice::GetInst()->GetResolution();
	mRoot->mSize.x = RS.Width * 1.5;
	mRoot->mSize.y = RS.Height * 1.5;
	mRoot->mDivisionCount = mDivisionCount;

	return true;


	return true;
}

void CCollisionQuadTree::AddCollider(CColliderBase* Collider)
{

}


void CCollisionQuadTree::Update(float DeltaTime)
{
	// 카메라를 얻어와서 카메라의 위치로 루트의 센터
	CCameraComponent* Camera = mScene->GetCameraManager()->GetViewTarget();

	// 카메라를 얻어와서 카메라의 위치로 루트의 센터를 지정해준다.
	// 현재 중앙은 카메라 기준이기 때문이다.
	if (!Camera)
	{
		mRoot->mCenter.x = Camera->GetWorldPosition().x;
		mRoot->mCenter.y = Camera->GetWorldPosition().y;
	}
}

