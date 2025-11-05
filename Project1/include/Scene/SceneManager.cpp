#include "SceneManager.h"
#include "SceneMain.h"


CSceneManager::CSceneManager()
{

}
CSceneManager::~CSceneManager()
{
	SAFE_DELETE(mCurrentScene);

}
bool CSceneManager::Init()
{
	mCurrentScene = CreateScene<CSceneMain>();
	if (mCurrentScene == nullptr)
	{
		return false;
	}
	return true;
}

void CSceneManager::Input(float DeltaTime)
{
	mCurrentScene->Input(DeltaTime);
}


void CSceneManager::Update(float DeltaTime)
{
	mCurrentScene->PreUpdate(DeltaTime);

	mCurrentScene->Update(DeltaTime);

	mCurrentScene->PostUpdate(DeltaTime);
}

void CSceneManager::Collision(float DeltaTime)
{
	mCurrentScene->Collision(DeltaTime);
}
void CSceneManager::Render()
{
	mCurrentScene->PreRender();

	mCurrentScene->Render();

	mCurrentScene->PostRender();
}