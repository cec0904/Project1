#include "SceneMain.h"

#include "../Object/Player/PlayerObject.h"
#include "../Object/Monster/MonsterObject.h"
#include "../Object/Monster/GunnerMonster.h"
#include "../Object/Monster/NearingMonster.h"

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

	CPlayerObject* Player = CreateObj<CPlayerObject>("Player");

	if (Player == nullptr)
	{
		return false;
	}

	CMonsterObject* Monster = CreateObj<CGunnerMonster>("GunnerMonster");
	Monster->SetWorldPos(-400.f, 300.f);
	Monster->SetTarget(Player);

	CMonsterObject* Monster1 = CreateObj<CGunnerMonster>("GunnerMonster1");
	Monster1->SetWorldPos(400.f, 300.f);
	Monster1->SetTarget(Player);

	CMonsterObject* Monster2 = CreateObj<CNearingMonster>("NearingMonster");
	Monster2->SetWorldPos(0.f, 300.f);
	Monster2->SetTarget(Player);

	CMonsterObject* Monster3 = CreateObj<CGunnerMonster>("GunnerMonster2");
	Monster3->SetWorldPos(400.f, -300.f);
	Monster3->SetTarget(Player);

	CMonsterObject* Monster4 = CreateObj<CGunnerMonster>("GunnerMonster3");
	Monster4->SetWorldPos(0.f, -300.f);
	Monster4->SetTarget(Player);

	return true;
}
