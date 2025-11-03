#include "ColliderBase.h"

CColliderBase::CColliderBase()
{
}
CColliderBase::CColliderBase(const CColliderBase& Com)
{
}
CColliderBase::CColliderBase(CColliderBase&& Com)
{
}
CColliderBase::~CColliderBase()	
{
}

bool CColliderBase::Init()
{
	return true;
}
bool CColliderBase::Init(const char* FileName)
{
	return true;
}
void CColliderBase::PreUpdate(float DeltaTime)
{

}
void CColliderBase::Update(float DeltaTime)
{

}
void CColliderBase::PostUpdate(float DeltaTime)
{

}
void CColliderBase::Collision(float DeltaTime)
{

}
void CColliderBase::PreRender()
{

}
void CColliderBase::Render()
{
}
void CColliderBase::PostRender()
{
}
CColliderBase* CColliderBase::Clone()
{
	return nullptr;
}