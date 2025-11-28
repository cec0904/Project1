#include "Animation2DManager.h"
#include "Animation2DData.h"

CAnimation2DManager::CAnimation2DManager()
{
}

CAnimation2DManager::~CAnimation2DManager()
{
    
}

bool CAnimation2DManager::Init()
{
    return true;
}

bool CAnimation2DManager::CreateAnimation(const string& Name)
{
    // 생성해야하는데 같은 이름이 있으면 false
    if (FindAnimation(Name))
    {
    return false;
        
    }
    CAnimation2DData* Animation = new CAnimation2DData;

    Animation->SetName(Name);

    mAnimationMap.insert(make_pair(Name, Animation));

    return true;
}

class CAnimation2DData* CAnimation2DManager::FindAnimation(const string& Name)
{
    auto iter = mAnimationMap.find(Name);

    if (iter == mAnimationMap.end())
    {
    return nullptr;

    }
    return iter->second;
}

void CAnimation2DManager::ReleaseAnimation(CAsset* Animation)
{
    auto iter = mAnimationMap.find(Animation->GetName());
    if (iter != mAnimationMap.end())
    {
        mAnimationMap.erase(iter);
    }
}

bool CAnimation2DManager::SetAnimationTextureType(const string& Name, EAnimationTextureType Type)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
    {
        return false;
    }

    Animation->SetAnimationTextureType(Type);

    return true;
}

bool CAnimation2DManager::SetTexture(const string& Name, CTexture* Texture)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
    {
        return false;
    }

    Animation->SetTexture(Texture);

    return true;
}

bool CAnimation2DManager::SetTexture(const string& Name, const string& TextureName)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
    {
        return false;
    }

    Animation->SetTexture(TextureName);

    return true;
}

bool CAnimation2DManager::SetTexture(const string& Name, const string& TextureName, const TCHAR* FileName)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
    {
        return false;
    }

    Animation->SetTexture(TextureName, FileName);

    return true;
}

bool CAnimation2DManager::SetTexture(const string& Name, const string& TextureName, vector<const TCHAR*> FileName)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
    {
        return false;
    }

    Animation->SetTexture(TextureName, FileName);

    return true;
}

bool CAnimation2DManager::SetTexture(const string& Name, const string& TextureName, const TCHAR* FileName, const TCHAR* Ext, int Count)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
    {
        return false;
    }

    Animation->SetTexture(TextureName, FileName, Ext, Count);

    return true;
}

bool CAnimation2DManager::SetTextureFullPath(const string& Name, const string& TextureName, const TCHAR* FullPath)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
    {
        return false;
    }

    Animation->SetTextureFullPath(TextureName, FullPath);

    return true;
}

bool CAnimation2DManager::SetTextureFullPath(const string& Name, const string& TextureName, const vector<const TCHAR*>& FullPath)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
    {
        return false;
    }

    Animation->SetTextureFullPath(TextureName, FullPath);

    return true;
}

bool CAnimation2DManager::AddFrame(const string& Name, const FVector2D& Start, const FVector2D& Size)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
    {
        return false;
    }

    Animation->AddFrame(Start, Size);

    return true;
}

bool CAnimation2DManager::AddFrame(const string& Name, float StartX, float StartY, float SizeX, float SizeY)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
    {
        return false;
    }

    Animation->AddFrame(StartX, StartY, SizeX, SizeY);

    return true;
}

bool CAnimation2DManager::AddFrameCount(const string& Name, int Count, const FVector2D& Start, const FVector2D& Size)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
    {
        return false;
    }

    Animation->AddFrameCount(Count, Start, Size);

    return true;
}

bool CAnimation2DManager::AddFrameCount(const string& Name, int Count, float StartX, float StartY, float SizeX, float SizeY)
{
    CAnimation2DData* Animation = FindAnimation(Name);

    if (!Animation)
    {
        return false;
    }

    Animation->AddFrameCount(Count, StartX, StartY, SizeX, SizeY);

    return true;
}
