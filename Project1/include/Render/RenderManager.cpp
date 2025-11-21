#include "RenderManager.h"
#include "RenderStateManager.h"

CRenderManager::CRenderManager()
{

}

CRenderManager::~CRenderManager()
{
	SAFE_DELETE(mStateManager);
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

}
