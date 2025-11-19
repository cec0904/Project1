#pragma once
#include "../Asset.h"

// Mesh라는 모양도 갔고있고

// 머티리얼을 이용해서 색칠을 할것이다.
// 어떤 텍스쳐를 사용하는지
// 어떤 쉐이더를 사용하는지 

namespace ETextureSamplerType
{
    enum Type
    {
        Point,
        Linear,
        Anisotropic,
        End
    };
}

//머티리얼이 들고있을 텍스쳐 정보
struct FMaterialTextureInfo
{
    //텍스쳐 이름 
    std::string Name;
    //사용할 텍스쳐
    CSharedPtr<class CTexture> Texture;
    // 이미지 텍스쳐 같이 쌍으로 들어가야할 데이터가
    // 샘플러
    ETextureSamplerType::Type SamplerType = ETextureSamplerType::Linear;
    //텍스쳐를 넣을 레지스터 번호
    int Register = 0;
    // ShaderBufferType 쉐이더 타입도 넣어준다. 
    int ShaderBufferType = (int)EShaderBufferType::Pixel;
    // 텍스쳐 인덱스
    int TextureIndex = 0;
};

class CMaterial :
    public CAsset
{
    friend class CMaterialManager;

protected:
    CMaterial();
    ~CMaterial();

protected:
    //머티리얼의 구성 요소
    // 텍스쳐 리스트 
    std::vector<FMaterialTextureInfo*> mTextureList;
    // 해당 머티리얼을 그리는 픽셀 쉐이더
    ID3D11PixelShader* mPS = nullptr;

public:
    //텍스쳐 가져오기
    // CTexture 를 넣어주는 방법 
    void AddTexture(class CTexture* Texture,
        int Register,
        int ShaderBufferType = EShaderBufferType::Pixel,
        int TextureIndex = 0);
    //Name으로 찾아와서 텍스쳐를 넣어주는 바업
    void AddTexture(const std::string& Name,
        int Register,
        int ShaderBufferType = EShaderBufferType::Pixel,
        int TextureIndex = 0);
    //파일 이름으로 텍스쳐 매니져에서 로드 후 추가하기 
    void AddTexture(const std::string& Name,
        const TCHAR* FileName,
        int Register,
        int ShaderBufferType = EShaderBufferType::Pixel,
        int TextureIndex = 0);


    //PS
    //쉐이더 가져오기 
    void SetPixelShader(const std::string& Name);
    void SetPixelShader(const std::string& Name, const char* EntryName, const TCHAR* FileName);


};

