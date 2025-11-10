#pragma once
#include "../SceneObject.h"

enum class ESkill4State
{
	Expansion,	//확장
	Maintain,	//유지
	Reducion	//축소
};

class CPlayerObject :
	public CSceneObject
{
	friend class CScene;

protected:
	CPlayerObject();
	CPlayerObject(const CPlayerObject& Obj);
	CPlayerObject(CPlayerObject&& Obj);
	virtual ~CPlayerObject();

protected:
	CSharedPtr<class CStaticMeshComponent> mRoot;
	CSharedPtr<class CColliderOBB2D> mBody;
	//CSharedPtr<class CColliderSphere2D> mBody;

	CSharedPtr<class CSceneComponent> mRotationPivot;
	CSharedPtr<class CStaticMeshComponent> mSub;

	// MovementComponent
	CSharedPtr<class CMovementComponent> mMovement;

	// RotationComponent
	CSharedPtr<class CRotationComponent> mRotation;

	// CameraComponent
	CSharedPtr<class CCameraComponent> mCamera;



	//실습1 
	//위성 반대편 방향에 하나더 출력해보기 
	CSharedPtr<class CStaticMeshComponent> mSub1;

	// 총알용 오브젝트 
	//스킬 1
	CSharedPtr<class CBulletObject> mSkill1Object;

	//스킬 3 : 위성에서 발사하기 
	bool mSkill3Enable = false;
	float mSkill3Time = 3.f;	// 3초동안
	float mSkill3TimeAcc = 0.f;	// 시간 측정용  
	float mSkill3Interval = 0.2f; //0.2초마다 총알을 발사할것이다.

	//스킬 4 : 아우솔
	bool mSkill4Enable = false;
	// 스킬 커지는 시간
	float mSkill4Time = 2.f;
	float mSkill4TimeAcc = 0.f;
	float mSkill4ReadyTime = 2.f;	// 확장, 축소하는데 걸리는 시간. 
	float mSkill4MaxRange = 400.f;
	float mSkill4Range = 200.f;
	float mSkill4RangeLength = 200.f;
	//스킬 다시 작아지는 시간 
	ESkill4State mSkill4State = ESkill4State::Expansion;

	float mPivotRotationSpeed = 180.f;

	float mHP = 10;

public:
	virtual bool Init();
	virtual void Update(float DeltaTime);
	void Damage(float Damage);

private:
	void MoveUp(float DeltaTime);
	void MoveDown(float DeltaTime);

	void RotationZ(float DeltaTime);
	void RotationZInv(float DeltaTime);

	void Fire(float DeltaTime);

	//스킬
	void Skill1(float DeltaTime);
	void Skill1Fire(float DeltaTime);

	// 스킬 2 토네이도 샷 
	void Skill2(float DeltaTime);

	//스킬 3 : 위성 2개에서 각각 총알에 생성된다. 날라가는 방향은 플레이어 바라보는 방향으로 
	void Skill3(float DeltaTime);
	void Skill3Update(float DeltaTime);

	//스킬 4 : 위성을 더 멀리 빠르게 돌렸다가 되돌린다. 
	// 예시는 롤 : 아우솔 옛날 W 
	void Skill4(float DeltatTime);
	void Skill4Update(float DeltaTime);

	//스킬5 탈론 궁
	// 8각형 기준으로 스폰해주고 
	// 총알은 각각 돌다가 돌아온다.
	void Skill5(float DeltaTime);

	// 스킬6 중력탄 자리야 궁
	// 총알 발사하면
	// 범위 내 몬스터 한 곳으로 합쳐짐
	void Skill6(float DeltaTime);

	// 스킬7
	// 파라 충격탄
	// 밀쳐내기
	void Skill7(float DeltaTime);


};

