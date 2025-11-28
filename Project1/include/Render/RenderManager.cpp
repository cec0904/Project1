#include "RenderManager.h"
#include "RenderStateManager.h"
#include "../Component/SceneComponent/SceneComponent.h"

CRenderManager::CRenderManager()
{

}

CRenderManager::~CRenderManager()
{
	ClearRenderList();
	SAFE_DELETE(mStateManager);
}

void CRenderManager::AddRenderList(CSceneComponent* Component)
{
	mRenderList.emplace_back(Component);
}

void CRenderManager::ClearRenderList()
{
	mRenderList.clear();
}

bool CRenderManager::Init()
{
	mStateManager = new CRenderStateManager;

	if (!mStateManager->Init())
	{
		return false;
	}

	return true;
}

void CRenderManager::Render()
{
	// 정렬해주기
	switch (mRenderSortType)
	{
	case ERenderSortType::None:
		break;
	case ERenderSortType::Y:
		if (mRenderList.size() > 1)
		{
			mRenderList.sort(CRenderManager::SortY);
		}
		break;
	case ERenderSortType::Alpha:
		if (mRenderList.size() > 1)
		{
			mRenderList.sort(CRenderManager::SortAlpha);
		}
		break;
	default:
		break;
	}

	// 그리기
	auto iter = mRenderList.begin();
	auto iterEnd = mRenderList.end();

	for (; iter != iterEnd;)
	{
		// Active
		if (!(*iter)->IsActive())
		{
			iter = mRenderList.erase(iter);
			iterEnd = mRenderList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;
			continue;
		}

		// 그려줘
		(*iter)->PreRender();
		(*iter)->Render();
		(*iter)->PostRender();
		iter++;
	}

}

bool CRenderManager::SortY(const CSharedPtr<class CSceneComponent>& Src, const CSharedPtr<class CSceneComponent>& Dest)
{
	float SrcY = Src->GetWorldPosition().y - Src->GetPivot().y * Src->GetWorldScale().y;

	float DestY = Dest->GetWorldPosition().y - Dest->GetPivot().y * Dest->GetWorldScale().y;

	return SrcY < DestY;
}

bool CRenderManager::SortAlpha(const CSharedPtr<class CSceneComponent>& Src, const CSharedPtr<class CSceneComponent>& Dest)
{
	return false;
}
