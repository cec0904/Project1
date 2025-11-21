#include "SceneComponent.h"
#include "../../Shader/ConstantBuffer/Transform/TransformCBuffer.h"
#include "../../Scene/Scene.h"
#include "../../Scene/CameraManager/CameraManager.h"
#include "../../Asset/Texture/Texture.h"
#include "../../Asset/Texture/TextureManager.h"



CSceneComponent::CSceneComponent()
{
	mTransformCBuffer = new CTransformCBuffer;
	mTransformCBuffer->Init();
}

CSceneComponent::CSceneComponent(const CSceneComponent& Com)
	: CComponent(Com)
{
	mTransformCBuffer = Com.mTransformCBuffer->Clone();
}

CSceneComponent::CSceneComponent(CSceneComponent&& Com)
	: CComponent(Com)
{
	mTransformCBuffer = Com.mTransformCBuffer;
	Com.mTransformCBuffer = nullptr;
}

CSceneComponent::~CSceneComponent()
{
	SAFE_DELETE(mTransformCBuffer);
	size_t Size = mChildList.size();
	for (size_t i = 0; i < Size; i++)
	{
		mChildList[i]->Destroy();
	}
}

void CSceneComponent::AddChild(CSceneComponent* Child)
{
	Child->mParent = this;
	// 자식으로 추가해준다.
	mChildList.emplace_back(Child);
	// 자식의 트랜스폼을 계산해준다.
	Child->ComputeTransform();
}

bool CSceneComponent::Init()
{
	if (!CComponent::Init())
	{
		return false;
	}
	return true;
}

bool CSceneComponent::Init(const char* FileName)
{
	return true;
}
void CSceneComponent::PreUpdate(float DeltaTime)
{
	CComponent::PreUpdate(DeltaTime);

	// 자식들 호출해줘야 한다.
	vector<CSharedPtr<CSceneComponent>>::iterator iter;
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive()) // 삭제할 타이밍
		{
			// 삭제할 컴포넌트랑 자료구조의 마지막 요소랑 스왑 해준다.
			swap(*iter, mChildList.back());

			mChildList.pop_back();
			iterEnd = mChildList.end();
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

void CSceneComponent::Update(float DeltaTime)
{
	CComponent::Update(DeltaTime);

	vector<CSharedPtr<CSceneComponent>>::iterator iter;
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			swap(*iter, mChildList.back());

			mChildList.pop_back();
			iterEnd = mChildList.end();
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
void CSceneComponent::PostUpdate(float DeltaTime)
{
	CComponent::PostUpdate(DeltaTime);

	vector<CSharedPtr<CSceneComponent>>::iterator iter;
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			swap(*iter, mChildList.back());

			mChildList.pop_back();
			iterEnd = mChildList.end();
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
void CSceneComponent::Collision(float DeltaTime)
{
	CComponent::Collision(DeltaTime);

	vector<CSharedPtr<CSceneComponent>>::iterator iter;
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			swap(*iter, mChildList.back());

			mChildList.pop_back();
			iterEnd = mChildList.end();
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
void CSceneComponent::PreRender()
{
	CComponent::PreRender();

	// 행렬을 미리 계산해준다.
	mmatScale.Scaling(mWorldScale);
	mmatRot.Rotation(mWorldRot);
	mmatTranslate.Translation(mWorldPos);

	//			   크기   *    자전  *     이동
	mmatWorld = mmatScale * mmatRot * mmatTranslate;

	vector<CSharedPtr<CSceneComponent>>::iterator iter;
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			swap(*iter, mChildList.back());

			mChildList.pop_back();
			iterEnd = mChildList.end();
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
void CSceneComponent::Render()
{
	CComponent::Render();

	vector<CSharedPtr<CSceneComponent>>::iterator iter;
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			swap(*iter, mChildList.back());

			mChildList.pop_back();
			iterEnd = mChildList.end();
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

	mTransformCBuffer->SetWorldMatrix(mmatWorld);
	FMatrix matView, matProj;

	matView = mScene->GetCameraManager()->GetViewMatrix();
	matProj = mScene->GetCameraManager()->GetProjMatrix();

	mTransformCBuffer->SetViewMatrix(matView);
	mTransformCBuffer->SetProjMatrix(matProj);
	mTransformCBuffer->SetPivot(mPivot);

	mTransformCBuffer->UpdateBuffer();

}
void CSceneComponent::PostRender()
{
	CComponent::PostRender();

	vector<CSharedPtr<CSceneComponent>>::iterator iter;
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (iter = mChildList.begin(); iter != iterEnd;)
	{
		if (!(*iter)->IsActive())
		{
			swap(*iter, mChildList.back());

			mChildList.pop_back();
			iterEnd = mChildList.end();
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

CSceneComponent* CSceneComponent::Clone()
{
	return new CSceneComponent(*this);
}

void CSceneComponent::EraseOwner()
{
	CComponent::EraseOwner();

	vector<CSharedPtr<CSceneComponent>>::iterator iter = mChildList.begin();
	vector<CSharedPtr<CSceneComponent>>::iterator iterEnd = mChildList.end();

	for (; iter != iterEnd; iter++)
	{
		(*iter)->EraseOwner();
	}
}

/////// 좌표 
void CSceneComponent::SetRelativeScale(const FVector3D& Scale)
{
	mRelativeScale = Scale;

	//부모 영향 받았으면 
	if (mParent)
	{
		mWorldScale = mRelativeScale * mParent->mWorldScale;
	}
	else
	{
		mWorldScale = mRelativeScale;
	}

	//내 크기가 정했으면 자식에게도 영향을 줘야한다. 
	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		//자식의 월드 위치 = 자식의 상대 위치 * 내 월드스케일 + 내 월드위치 
		mChildList[i]->mWorldPos = mChildList[i]->mRelativePos * mWorldScale + mWorldPos;

		//자식의 월드 스케일도 셋팅 해줘야한다. 
		//자식의 크기 = 자식의 상대크기 * 내 월드 스케일 
		mChildList[i]->SetWorldScale(mChildList[i]->mRelativeScale * mWorldScale);
	}
}

void CSceneComponent::SetRelativeScale(float x, float y, float z)
{
	SetRelativeScale(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativeScale(const FVector2D& Scale)
{
	SetRelativeScale(FVector3D(Scale.x, Scale.y, mRelativeScale.z));
}

void CSceneComponent::SetRelativeScale(float x, float y)
{
	SetRelativeScale(FVector3D(x, y, mRelativeScale.z));
}


//회전 

void CSceneComponent::SetRelativeRotation(const FVector3D& Rot)
{
	mRelativeRot = Rot;

	if (mParent)
	{
		mWorldRot = mRelativeRot + mParent->mWorldRot;
	}
	else
	{
		mWorldRot = mRelativeRot;
	}

	// 축 회전
	FVector3D Axis[EAxis::End] =
	{
		FVector3D(1.f, 0.f, 0.f),
		FVector3D(0.f, 1.f, 0.f),
		FVector3D(0.f, 0.f, 1.f)
	};

	FMatrix matRot;
	matRot.Rotation(mWorldRot);

	// 회전된 축 구하기
	mAxis[EAxis::X] = Axis[EAxis::X].TransformNormal(matRot);
	mAxis[EAxis::Y] = Axis[EAxis::Y].TransformNormal(matRot);
	mAxis[EAxis::Z] = Axis[EAxis::Z].TransformNormal(matRot);

	mAxis[EAxis::X].Normalize();
	mAxis[EAxis::Y].Normalize();
	mAxis[EAxis::Z].Normalize();

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		////자식의 월드 위치 = 자식의 상대 위치를 내 월드 회전값으로 횐전한 값 + 내 월드 위치 
		//mChildList[i]->mWorldPos = mChildList[i]->mRelativePos.GetRotation(mWorldRot) + mWorldPos;

		////자식의 월드 회전 = 자식의 상대회전 + 내 월드회전 
		//mChildList[i]->SetWorldRotation(mChildList[i]->mRelativeRot + mWorldRot);


		FVector3D ParentRot = GetWorldRotation();

		FMatrix matRot;
		matRot.Rotation(ParentRot);

		// 행렬의 41, 42, 43 에 부모의 위치를 넣어 부모의 위치를 중심으로
		// 회전하는 행렬을 만들어 준다.
		memcpy(&matRot._41, &mWorldPos, sizeof(FVector3D));

		mChildList[i]->mWorldPos = mChildList[i]->mRelativePos.TransformCoord(matRot);

		mChildList[i]->SetWorldRotation(mChildList[i]->mRelativeRot + mWorldRot);
	}
}

void CSceneComponent::SetRelativeRotation(float x, float y, float z)
{
	SetRelativeRotation(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativeRotation(const FVector2D& Rot)
{
	SetRelativeRotation(FVector3D(Rot.x, Rot.y, mRelativeRot.z));
}

void CSceneComponent::SetRelativeRotation(float x, float y)
{
	SetRelativeRotation(FVector3D(x, y, mRelativeRot.z));
}

void CSceneComponent::SetRelativeRotationX(float x)
{
	SetRelativeRotation(FVector3D(x, mRelativeRot.y, mRelativeRot.z));
}

void CSceneComponent::SetRelativeRotationY(float y)
{
	SetRelativeRotation(FVector3D(mRelativeRot.x, y, mRelativeRot.z));
}

void CSceneComponent::SetRelativeRotationZ(float z)
{
	SetRelativeRotation(FVector3D(mRelativeRot.x, mRelativeRot.y, z));
}

void CSceneComponent::SetRelativeRotationAxis(float Angle, const FVector3D& Axis)
{
	//추후에 구현하겠다. 
}

void CSceneComponent::SetRelativePos(const FVector3D& Pos)
{
	mRelativePos = Pos;

	if (mParent)
	{
		 
		//mWorldPos = mRelativePos + mParent->mWorldPos;
		FVector3D ParentRot = mParent->GetWorldRotation();
		FMatrix matRot;
		matRot.Rotation(ParentRot);	//부모의 월드 회전행렬 

		//회전과 이동모두 가지고 있는 행렬을 만들고 
		memcpy(&matRot._41, &mParent->mWorldPos, sizeof(FVector3D));

		mWorldPos = mRelativePos.TransformCoord(matRot);
	}
	else
	{
		mWorldPos = mRelativePos;
	}

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		//자식 위치 = 자식의 상대 위치 + 내 월드 위치 
		mChildList[i]->SetWorldPos(mChildList[i]->mRelativePos + mWorldPos);
	}
}

void CSceneComponent::SetRelativePos(float x, float y, float z)
{
	SetRelativePos(FVector3D(x, y, z));
}

void CSceneComponent::SetRelativePos(const FVector2D& Pos)
{
	SetRelativePos(FVector3D(Pos.x, Pos.y, mRelativePos.z));
}

void CSceneComponent::SetRelativePos(float x, float y)
{
	SetRelativePos(FVector3D(x, y, mRelativePos.z));
}

//월드
void CSceneComponent::SetWorldScale(const FVector3D& Scale)
{
	mWorldScale = Scale;
	if (mParent)
	{
		//내 상대 크기 = 내 월드 크기 / 부모의 월드 크기 
		mRelativeScale = mWorldScale / mParent->mWorldScale;
	}
	else
	{
		mRelativeScale = mWorldScale;
	}

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		//자식의 월드 스케일 = 자식의 상대 스케일 * 내 월드스케일 
		mChildList[i]->SetWorldScale(mChildList[i]->mRelativeScale * mWorldScale);

		// 자식의 월드 위치 = 자식의 상대위치 * 내 월드 스케일 + 내월드 위치 
		mChildList[i]->SetWorldPos(mChildList[i]->mRelativePos * mWorldScale + mWorldPos);
	}
}

void CSceneComponent::SetWorldScale(float x, float y, float z)
{
	SetWorldScale(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldScale(const FVector2D& Scale)
{
	SetWorldScale(FVector3D(Scale.x, Scale.y, mWorldScale.z));
}

void CSceneComponent::SetWorldScale(float x, float y)
{
	SetWorldScale(FVector3D(x, y, mWorldScale.z));
}

void CSceneComponent::SetWorldRotation(const FVector3D& Rot)
{
	mWorldRot = Rot;

	if (mParent)
	{
		mRelativeRot = mWorldRot - mParent->mWorldRot;
	}
	else
	{
		mRelativeRot = mWorldRot;
	}

	FVector3D Axis[EAxis::End] =
	{
		FVector3D(1.f, 0.f, 0.f),
		FVector3D(0.f, 1.f, 0.f),
		FVector3D(0.f, 0.f, 1.f)
	};


	//회전이 적용되면 그 회전만큼축도 회전시켜 줄것이다.
	FMatrix matRot;
	matRot.Rotation(mWorldRot);

	//회전된 만큼 충을 돌려줄것이다. 
	mAxis[EAxis::X] = Axis[EAxis::X].TransformNormal(matRot);
	mAxis[EAxis::Y] = Axis[EAxis::Y].TransformNormal(matRot);
	mAxis[EAxis::Z] = Axis[EAxis::Z].TransformNormal(matRot);

	mAxis[EAxis::X].Normalize();
	mAxis[EAxis::Y].Normalize();
	mAxis[EAxis::Z].Normalize();


	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; ++i)
	{
		////자식의 월드 회전 = 자식의 상대 회전 + 내 월드 회전 
		//mChildList[i]->SetWorldRotation(mChildList[i]->mRelativeRot + mWorldRot);

		//// 회전 시킨만큼 자식의 위치에도 영향을 주어야한다. 
		//// 자식의 상대 위치에 내 월드만큼 회전을 시키고 + 내 위치만큼 이동
		//mChildList[i]->SetWorldPos(mChildList[i]->mRelativePos.GetRotation(mWorldRot) + mWorldPos);

		// 이전 수식
		// 문제점 : 부모가 회전했을 때 자식이 부모의 회전축을 중심으로 회전하지 않는다. 공전이 아니다.
		// mChildList[i]->SetWorldPos(
		//	mChildList[i]->mRelativePos.GetRotation(mWorldRot) + mWorldPos);

		mChildList[i]->SetWorldRotation(mChildList[i]->mRelativeRot + mWorldRot);


		FVector3D ParentRot = GetWorldRotation();

		FMatrix matRot;
		matRot.Rotation(ParentRot);

		// 행렬의 41, 42, 43 에 부모의 위치를 넣어 부모의 위치를 중심으로
		// 회전하는 행렬을 만들어 준다.
		memcpy(&matRot._41, &mWorldPos, sizeof(FVector3D));

		mChildList[i]->mWorldPos = mChildList[i]->mRelativePos.TransformCoord(matRot);

		


		
		
	}
}

void CSceneComponent::SetWorldRotation(float x, float y, float z)
{
	SetWorldRotation(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldRotation(const FVector2D& Rot)
{
	SetWorldRotation(FVector3D(Rot.x, Rot.y, mWorldRot.z));
}

void CSceneComponent::SetWorldRotation(float x, float y)
{
	SetWorldRotation(FVector3D(x, y, mWorldRot.z));
}

void CSceneComponent::SetWorldRotationX(float x)
{
	SetWorldRotation(FVector3D(x, mWorldRot.y, mWorldRot.z));
}

void CSceneComponent::SetWorldRotationY(float y)
{
	SetWorldRotation(FVector3D(mWorldRot.x, y, mWorldRot.z));
}

void CSceneComponent::SetWorldRotationZ(float z)
{
	SetWorldRotation(FVector3D(mWorldRot.x, mWorldRot.y, z));
}

void CSceneComponent::SetWorldRotationAxis(float Angle, const FVector3D& Axis)
{
	// 추후에 
}

void CSceneComponent::SetWorldPos(const FVector3D& Pos)
{
	//mWorldPos = Pos;

	//if (mParent)
	//{
	//	FVector3D ParentRot = mParent->mWorldRot;

	//	FMatrix matRot;
	//	matRot.Rotation(ParentRot);

	//	//회전 행렬이 나왔다.
	//	// 성분중에 _41, _42, _43이 이동을 담당하는 부분이니까 부모의위치를 넣어서 부모의 위치를 중심으로 회전하는 행렬를 만들줄것이다. 
	//	memcpy(&matRot._41, &mParent->mWorldPos, sizeof(FVector3D));

	//	// matRot -> 회전과 이동을 동시에 가지고있는 행렬이 되었다. 
	//	mWorldPos = mRelativePos.TransformCoord(matRot);
	//}
	//else
	//{
	//	mRelativePos = mWorldPos;
	//}

	//size_t Size = mChildList.size();

	//for (size_t i = 0; i < Size; ++i)
	//{
	//	mChildList[i]->SetWorldPos(mChildList[i]->mRelativePos + mWorldPos);
	//}


	// 위 수식이 잘못된 이유
	// 자식의 월드 위치 = 자식의 상대 위치 + 부모의 월드 위치 -> 이 수식은 부모의 회전량을 반영하지 못한다.
	// 근데 위의 수식으로는 부모의 회전량을 못 받은 로컬 위치를 사용했기 때문에
	// 부모의 월드 위치가 변한만큼 자식의 월드 위치도 변해야 한다.
	// mChildList[i]->SetWorldPos(mChildList[i]->mWorldPos + Step);



	// 수정

	mWorldPos = Pos;

	if (mParent)
	{
		FVector3D ParentRot = mParent->GetWorldRotation();

		FMatrix matRot;
		matRot.Rotation(ParentRot);

		// 행렬의 41, 42, 43 에 부모의 위치를 넣어 부모의 위치를 중심으로
		// 회전하는 행렬을 만들어 준다.
		memcpy(&matRot._41, &mParent->mWorldPos, sizeof(FVector3D));

		mWorldPos = mRelativePos.TransformCoord(matRot);
	}
	else
	{
		mRelativePos = mWorldPos;
	}

	size_t Size = mChildList.size();

	for (size_t i = 0; i < Size; i++)
	{
		mChildList[i]->SetWorldPos(mChildList[i]->mRelativePos + mWorldPos);
	}
}

void CSceneComponent::SetWorldPos(float x, float y, float z)
{
	SetWorldPos(FVector3D(x, y, z));
}

void CSceneComponent::SetWorldPos(const FVector2D& Pos)
{
	SetWorldPos(FVector3D(Pos.x, Pos.y, mWorldPos.z));
}

void CSceneComponent::SetWorldPos(float x, float y)
{
	SetWorldPos(FVector3D(x, y, mWorldPos.z));
}




//Add
void CSceneComponent::AddRelativeScale(const FVector3D& Scale)
{
	mRelativeScale += Scale;

	SetRelativeScale(mRelativeScale);
}

void CSceneComponent::AddRelativeScale(float x, float y, float z)
{
	AddRelativeScale(FVector3D(x, y, z));
}

void CSceneComponent::AddRelativeScale(const FVector2D& Scale)
{
	AddRelativeScale(FVector3D(Scale.x, Scale.y, mRelativeScale.z));
}

void CSceneComponent::AddRelativeScale(float x, float y)
{
	AddRelativeScale(FVector3D(x, y, mRelativeScale.z));
}


void CSceneComponent::AddRelativeRotation(const FVector3D& Rot)
{
	mRelativeRot += Rot;
	SetRelativeRotation(mRelativeRot);
}

void CSceneComponent::AddRelativeRotation(float x, float y, float z)
{
	AddRelativeRotation(FVector3D(x, y, z));
}

void CSceneComponent::AddRelativeRotation(const FVector2D& Rot)
{
	AddRelativeRotation(FVector3D(Rot.x, Rot.y, mRelativeRot.z));
}

void CSceneComponent::AddRelativeRotation(float x, float y)
{
	AddRelativeRotation(FVector3D(x, y, mRelativeRot.z));
}

void CSceneComponent::AddRelativeRotationX(float x)
{
	AddRelativeRotation(FVector3D(x, mRelativeRot.y, mRelativeRot.z));
}

void CSceneComponent::AddRelativeRotationY(float y)
{
	AddRelativeRotation(FVector3D(mRelativeRot.x, y, mRelativeRot.z));
}

void CSceneComponent::AddRelativeRotationZ(float z)
{
	AddRelativeRotation(FVector3D(mRelativeRot.x, mRelativeRot.y, z));
}


void CSceneComponent::AddRelativePos(const FVector3D& Pos)
{
	mRelativePos += Pos;
	SetRelativePos(mRelativePos);
}

void CSceneComponent::AddRelativePos(float x, float y, float z)
{
	AddRelativePos(FVector3D(x, y, z));
}

void CSceneComponent::AddRelativePos(const FVector2D& Pos)
{
	AddRelativePos(FVector3D(Pos.x, Pos.y, mRelativePos.z));
}

void CSceneComponent::AddRelativePos(float x, float y)
{
	AddRelativePos(FVector3D(x, y, mRelativePos.z));
}

void CSceneComponent::AddWorldScale(const FVector3D& Scale)
{
	mWorldScale += Scale;

	SetWorldScale(mWorldScale);
}

void CSceneComponent::AddWorldScale(float x, float y, float z)
{
	AddWorldScale(FVector3D(x, y, z));
}

void CSceneComponent::AddWorldScale(const FVector2D& Scale)
{
	AddWorldScale(FVector3D(Scale.x, Scale.y, mWorldScale.z));
}

void CSceneComponent::AddWorldScale(float x, float y)
{
	AddWorldScale(FVector3D(x, y, mWorldScale.z));
}

void CSceneComponent::AddWorldRotation(const FVector3D& Rot)
{
	mWorldRot += Rot;
	SetWorldRotation(mWorldRot);
}

void CSceneComponent::AddWorldRotation(float x, float y, float z)
{
	AddWorldRotation(FVector3D(x, y, z));
}

void CSceneComponent::AddWorldRotation(const FVector2D& Rot)
{
	AddWorldRotation(FVector3D(Rot.x, Rot.y, mWorldRot.z));
}

void CSceneComponent::AddWorldRotation(float x, float y)
{
	AddWorldRotation(FVector3D(x, y, mWorldRot.z));
}

void CSceneComponent::AddWorldRotationX(float x)
{
	AddWorldRotation(FVector3D(x, mWorldRot.y, mWorldRot.z));
}

void CSceneComponent::AddWorldRotationY(float y)
{
	AddWorldRotation(FVector3D(mWorldRot.x, y, mWorldRot.z));
}

void CSceneComponent::AddWorldRotationZ(float z)
{
	AddWorldRotation(FVector3D(mWorldRot.x, mWorldRot.y, z));
}

void CSceneComponent::AddWorldPos(const FVector3D& Pos)
{
	mWorldPos += Pos;
	SetWorldPos(mWorldPos);
}

void CSceneComponent::AddWorldPos(float x, float y, float z)
{
	AddWorldPos(FVector3D(x, y, z));
}

void CSceneComponent::AddWorldPos(const FVector2D& Pos)
{
	AddWorldPos(FVector3D(Pos.x, Pos.y, mRelativePos.z));
}

void CSceneComponent::AddWorldPos(float x, float y)
{
	AddWorldPos(FVector3D(x, y, mRelativePos.z));
}

void CSceneComponent::ComputeTransform()
{
	//AddChild 해줄때 자식의 월드좌표를 계산해줄것이다. 
	SetWorldScale(mRelativeScale * mParent->mWorldScale);
	SetWorldRotation(mRelativeRot + mParent->mWorldRot);
	SetWorldPos(mRelativePos + mParent->mWorldPos);

	// if (!mParent) return;
}
