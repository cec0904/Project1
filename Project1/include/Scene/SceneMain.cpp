#include "SceneMain.h"

#include "../Object/Player/PlayerObject.h"
#include "../Object/Monster/MonsterObject.h"
#include "../Object/Monster/GunnerMonster.h"
#include "../Object/Monster/NearingMonster.h"
#include "../Object/Monster/ObjectSpawnPoint.h"
#include "../Asset/Material/Material.h"
#include "../Scene/Asset/SceneAssetManager.h"

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

	// 사용할 메테리얼 미리 만든다
	mAssetManager->CreateMaterial("Monster1");

	CMaterial* material = mAssetManager->FindMaterial("Monster1");
	material->SetPixelShader("DefaultMaterialShader");
	material->SetSamplerType(ETextureSamplerType::Linear);
	material->AddTexture("Monster1", TEXT("Texture/Porori.png"), 0);

	CPlayerObject* Player = CreateObj<CPlayerObject>("Player");

	if (Player == nullptr)
	{
		return false;
	}

	CMonsterObject* Monster = CreateObj<CGunnerMonster>("GunnerMonster");
	Monster->SetWorldPos(-400.f, 300.f);
	Monster->SetTarget(Player);

	CObjectSpawnPoint* MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint");
	MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Once);
	MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::CountDestroy);
	MonsterPoint->SetDestroySpawnCount(3);
	MonsterPoint->SetWorldPos(400.f, 300.f);


	MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint1");
	MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetSpawnCountType(EObjectSpawnCountType::CountDestroy);
	MonsterPoint->SetImmediateSpawn(false);
	MonsterPoint->SetSpawnTime(5.f);
	MonsterPoint->SetDestroySpawnCount(3);
	MonsterPoint->SetWorldPos(400.f, -300.f);


	MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint2");
	MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetImmediateSpawn(false);
	MonsterPoint->SetSpawnTime(5.f);
	MonsterPoint->SetWorldPos(400.f, -100.f);


	MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint3");
	MonsterPoint->SetSpawnType(EObjectSpawnType::GunnerMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetImmediateSpawn(false);
	MonsterPoint->SetSpawnTime(3.5f);
	MonsterPoint->SetWorldPos(400.f, -200.f);


	MonsterPoint = CreateObj<CObjectSpawnPoint>("MonsterPoint4");
	MonsterPoint->SetSpawnType(EObjectSpawnType::NearingMonster);
	MonsterPoint->SetSpawnLoopType(EObjectSpawnLoopType::Loop);
	MonsterPoint->SetImmediateSpawn(true);
	MonsterPoint->SetSpawnTime(10.f);
	MonsterPoint->SetWorldPos(200.f, 0.f);

	return true;




	/*CMonsterObject* Monster1 = CreateObj<CGunnerMonster>("GunnerMonster1");
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

	CMonsterObject* Monster5 = CreateObj<CGunnerMonster>("GunnerMonster4");
	Monster5->SetWorldPos(200.f, -300.f);
	Monster5->SetTarget(Player);

	CMonsterObject* Monster6 = CreateObj<CGunnerMonster>("GunnerMonster5");
	Monster6->SetWorldPos(0.f, -150.f);
	Monster6->SetTarget(Player);

	return true;*/
}
