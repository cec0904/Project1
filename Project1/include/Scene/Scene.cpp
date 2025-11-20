#include "Scene.h"

#include "Input/Input.h"
#include "CameraManager/CameraManager.h"
#include "Collision/SceneCollision.h"
#include "Asset/SceneAssetManager.h"


CScene::CScene()
{
}

CScene::~CScene()
{
	SAFE_DELETE(mAssetManager);
	SAFE_DELETE(mInput);
	SAFE_DELETE(mCameraManager);
	SAFE_DELETE(mCollision);
}

bool CScene::Init()
{
	mInput = new CInput;
	if (!mInput->Init())
	{
		SAFE_DELETE(mInput);
		return false;
	}

	mCameraManager = new CCameraManager;
	if (!mCameraManager->Init())
	{
		SAFE_DELETE(mCameraManager);
		return false;
	}

	mCollision = new CSceneCollision;
	mCollision->mScene = this;
	if (!mCollision->Init())
	{
		SAFE_DELETE(mCollision);
		return false;
	}

	mAssetManager = new CSceneAssetManager;
	mAssetManager->mScene = this;
	if (!mAssetManager->Init())
	{
		SAFE_DELETE(mAssetManager);
		return false;
	}

	return true;
}


bool CScene::Init(const char* FileName)
{
	mInput = new CInput;
	if (!mInput->Init())
	{
		SAFE_DELETE(mInput);
		return false;
	}

	mCameraManager = new CCameraManager;
	if (!mCameraManager->Init())
	{
		SAFE_DELETE(mCameraManager);
		return false;
	}

	mCollision = new CSceneCollision;

	mCollision->mScene = this;

	if (!mCollision->Init())
	{
		SAFE_DELETE(mCollision);
		return false;
	}

	mAssetManager = new CSceneAssetManager;
	mAssetManager->mScene = this;
	if (!mAssetManager->Init())
	{
		SAFE_DELETE(mAssetManager);
		return false;
	}

	return true;
}

void CScene::Input(float DeltaTime)
{
	mInput->Update(DeltaTime);
}

void CScene::PreUpdate(float DeltaTime)
{
	list<CSharedPtr<CSceneObject>>::iterator iter;
	list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;
			continue;
		}

		(*iter)->PreUpdate(DeltaTime);
		iter++;
	}

}

void CScene::Update(float DeltaTime)
{
	list<CSharedPtr<CSceneObject>>::iterator iter;
	list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;
			continue;
		}

		(*iter)->Update(DeltaTime);
		iter++;
	}

	mCameraManager->Update(DeltaTime);
}

void CScene::PostUpdate(float DeltaTime)
{
	list<CSharedPtr<CSceneObject>>::iterator iter;
	list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;
			continue;
		}

		(*iter)->PostUpdate(DeltaTime);
		iter++;
	}
}

void CScene::Collision(float DeltaTime)
{
	/*list<CSharedPtr<CSceneObject>>::iterator iter;
	list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;
			continue;
		}

		(*iter)->Collision(DeltaTime);
		iter++;
	}*/

	// SceneCollision 이 해당 씬의 충돌을 모두 관리한다.
	mCollision->Update(DeltaTime);
}

void CScene::PreRender()
{
	list<CSharedPtr<CSceneObject>>::iterator iter;
	list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;
			continue;
		}

		(*iter)->PreRender();
		iter++;
	}
}

void CScene::Render()
{
#ifdef _DEBUG
	if (mDebugQuadTree)
	{
		mCollision->Render();
	}
#endif // _DEBUG
	mCollision->ReturnNodePool();


	list<CSharedPtr<CSceneObject>>::iterator iter;
	list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;
			continue;
		}

		(*iter)->Render();
		iter++;
	}
}

void CScene::PostRender()
{
	list<CSharedPtr<CSceneObject>>::iterator iter;
	list<CSharedPtr<CSceneObject>>::iterator iterEnd = mObjList.end();

	for (iter = mObjList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			iter = mObjList.erase(iter);
			iterEnd = mObjList.end();
			continue;
		}
		else if (!(*iter)->IsEnable())
		{
			iter++;
			continue;
		}

		(*iter)->PostRender();
		iter++;
	}
}


