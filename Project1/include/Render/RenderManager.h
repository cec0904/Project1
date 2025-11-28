#pragma once

#include "../GameInfo.h"
class CRenderManager
{
	DECLARE_SINGLETONE(CRenderManager);

private:
	class CRenderStateManager* mStateManager = nullptr;

	// Render 할 SceneComponent 를 모아둘 것이다.
	list<CSharedPtr<class CSceneComponent>> mRenderList;
	// 정렬 타입
	ERenderSortType mRenderSortType = ERenderSortType::Y;

public:
	class CRenderStateManager* GetStateManager()
	{
		return mStateManager;
	}

	// RenderList 등록함수
	void AddRenderList(class CSceneComponent* Component);
	void ClearRenderList();

public:
	bool Init();
	void Render();

private:
	static bool SortY(const CSharedPtr<class CSceneComponent>& Src, const CSharedPtr<class CSceneComponent>& Dest);
	static bool SortAlpha(const CSharedPtr<class CSceneComponent>& Src, const CSharedPtr<class CSceneComponent>& Dest);

};

