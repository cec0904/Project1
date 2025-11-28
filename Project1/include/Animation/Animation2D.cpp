#include "Animation2D.h"

#include "../Asset/AssetManager.h"
#include "../Asset/Animation/Animation2DData.h"
#include "../Asset/Animation/Animation2DManager.h"
#include "../Asset/Texture/Texture.h"
#include "../Component/SceneComponent/SpriteComponent.h"
#include "../Scene/Scene.h"
#include "../Scene/Asset/SceneAssetManager.h"

CAnimation2D::CAnimation2D()
{
}

CAnimation2D::CAnimation2D(const CAnimation2D& Anim)
{
}

CAnimation2D::~CAnimation2D()
{

}

void CAnimation2D::CreateCBuffer()
{
}

void CAnimation2D::DestroyCBuffer()
{
}

void CAnimation2D::DisableAnimation()
{
}

void CAnimation2D::SetAnimFlip(bool Flip)
{
}

CAnimation2DSequence* CAnimation2D::FindSequence(const string& Name)
{
	return nullptr;
}

bool CAnimation2D::AddSequence(const string& Name, float PlayTime, float PlayRate, bool Loop, bool Reverse)
{
	return false;
}

bool CAnimation2D::AddSequence(CAnimation2DData* Asset, float PlayTime, float PlayRate, bool Loop, bool Reverse)
{
	return false;
}

void CAnimation2D::SetPlayTime(const string& Name, float PlayTime)
{
}

void CAnimation2D::SetPlayRate(const string& Name, float PlayRate)
{
}

void CAnimation2D::SetLoop(const string& Name, bool Loop)
{
}

void CAnimation2D::SetReverse(const string& Name, bool Reverse)
{
}

void CAnimation2D::ChangeAnimation(const string& Name)
{
}
