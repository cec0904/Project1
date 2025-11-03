#include "Scene.h"
#include "../Object/SceneObject.h"
#include "Input/Input.h"
#include "CameraManager/CameraManager.h"


CScene::CScene()
{
}

CScene::~CScene()
{
	SAFE_DELETE(mInput);
	SAFE_DELETE(mCameraManager);
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

		(*iter)->Collision(DeltaTime);
		iter++;
	}
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


