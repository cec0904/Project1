#include "ShaderManager.h"
#include "../Shader/ShaderClass/ColorMeshShader.h"
#include "ConstantBuffer/ConstantBuffer.h"
#include "../Shader/ShaderClass/FrameMeshShader.h"



CShaderManager::CShaderManager()
{
    // 초기화 코드 (예: 기본 셰이더 세팅)
}

CShaderManager::~CShaderManager()
{
    // 자원 해제 (ex: mShaderMap, mCBufferMap 정리)
}


CShader* CShaderManager::FindShader(const string& Name)
{
    auto iter = mShaderMap.find(Name);

    if (iter == mShaderMap.end())
    {
    return nullptr;
       
    }
    return (CShader*)iter->second.Get();
}

void CShaderManager::ReleaseShader(const string& Name)
{
    auto iter = mShaderMap.find(Name);

    if (iter != mShaderMap.end())
    {
        mShaderMap.erase(iter);
    }
}

bool CShaderManager::CreateConstantBuffer(const string& Name, int Size, int Register, int ShaderBufferType)
{
    CConstantBuffer* CBuffer = FindCBuffer(Name);

    if (CBuffer)
    {
        return true;
    }

    CBuffer = new CConstantBuffer;

    if (!CBuffer->Init(Size, Register, ShaderBufferType))
    {
        SAFE_DELETE(CBuffer);
        return false;
    }

    mCBufferMap.insert(make_pair(Name, CBuffer));
    return true;
}

CConstantBuffer* CShaderManager::FindCBuffer(const string& Name)
{
    auto iter = mCBufferMap.find(Name);
    if (iter == mCBufferMap.end())
    {
        return nullptr;
    }

    return (CConstantBuffer*)iter->second.Get();
}

void CShaderManager::ReleaseCBuffer(const string& Name)
{
    auto iter = mCBufferMap.find(Name);
    if (iter != mCBufferMap.end())
    {
        mCBufferMap.erase(iter);
    }

    
}

bool CShaderManager::Init()
{
    CreateShader<CColorMeshShader>("ColorMeshShader");

    CreateShader<CFrameMeshShader>("FrameMeshShader");

    // 우리가 사용할 상수버퍼도 만들어둔다.
    CreateConstantBuffer("Transform",
        sizeof(FTransformCBufferInfo),
        0,
        EShaderBufferType::Vertex);

    return true;
}
