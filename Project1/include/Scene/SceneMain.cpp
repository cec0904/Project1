#include "SceneMain.h"

#include "../Object/Player/PlayerObject.h"

CSceneMain::CSceneMain()
{
}

CSceneMain::~CSceneMain()
{
}

bool CSceneMain::Init()
{
	if (!CScene::Init())
	{
		return false;
	}

	CSceneObject* Obj = CreateObj<CPlayerObject>("Player");

	if (Obj == nullptr)
	{
		return false;
	}

	return true;
}
