#include "ShaderManager.h"
#include "../Shader/ShaderClass/ColorMeshShader.h"
#include "ConstantBuffer/ConstantBuffer.h"
#include "../Shader/ShaderClass/FrameMeshShader.h"
#include "../GameManager/Device/Device.h"



CShaderManager::CShaderManager()
{
    // 초기화 코드 (예: 기본 셰이더 세팅)
}

CShaderManager::~CShaderManager()
{
    // 자원 해제 (ex: mShaderMap, mCBufferMap 정리)

    auto iter = mPixelShaderMap.begin();
    auto iterEnd = mPixelShaderMap.end();

    for (; iter != iterEnd; iter++)
    {
        SAFE_DELETE(iter->second);
    }
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
    //머티리얼 용 상수버퍼  
    CreateConstantBuffer("Material", sizeof(FMaterialCBufferInfo), 1, EShaderBufferType::Pixel);


    // 충돌체에 사용할 상수버퍼
    CreateConstantBuffer("Collider", 
        sizeof(FColliderCBufferInfo),
        2,
        EShaderBufferType::Pixel);

    return true;
}

bool CShaderManager::LoadPixelShader(const string& Name, const char* EntryName, const TCHAR* FileName)
{
    if (FindPixelShader(Name))
    {
        return true;
    }

    // 최종 경로가 나온다.
    TCHAR FullPath[MAX_PATH] = {};
    lstrcpy(FullPath, TEXT("../../bin/Shader"));
    lstrcpy(FullPath, FileName);

    // 컴파일 했는데 에러나오면 여기에 들어옴
    ID3DBlob* ErrorBlob = nullptr;

    unsigned int Flag = 0;
#ifdef _DEBUG
    Flag = D3DCOMPILE_DEBUG;
#endif // _DEBUG

    FMaterialPixelShader* mps = new FMaterialPixelShader;

    if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName, "ps_5_0", Flag, 0, &mps->Blob, &ErrorBlob)))
    {
#ifdef _DEBUG
        char ErrorText[512] = {};
        strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
        strcat_s(ErrorText, "\n");
        OutputDebugStringA(ErrorText);
#endif // _DEBUG

        return false;
    }

    // 컴파일 성공
    // 성공했다면 쉐이더 객체 만들어주기

    if (FAILED(CDevice::GetInst()->GetDevice()->CreatePixelShader(mps->Blob->GetBufferPointer(), mps->Blob->GetBufferSize(), nullptr, &mps->PS)))
    {
        return false;
    }

    mPixelShaderMap.insert(std::make_pair(Name, mps));

    return true;
}

const FMaterialPixelShader* CShaderManager::FindPixelShader(const string& Name)
{
    auto iter = mPixelShaderMap.find(Name);

    if (iter == mPixelShaderMap.end())
    {
        return nullptr;
    }

    return iter->second;
}
