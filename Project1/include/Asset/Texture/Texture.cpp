#include "Texture.h"
#include "../../GameManager/Device/Device.h"



//#ifdef _DEBUG
//#pragma comment(lib, "../../../bin/DirectXTex_Debug.lib")
//#else
//#pragma comment(lib, "../../../bin/DirectXTex.lib")
//#endif // _DEBUG




CTexture::CTexture()
{
	mAssetType = EAssetType::Texture;
}
CTexture::~CTexture()
{
}

bool CTexture::LoadTexture(const TCHAR* FileName)
{
	return false;
}

bool CTexture::LoadTextureFullPath(const TCHAR* FullPath)
{
	return false;
}

void CTexture::SetShader(int REgister, int ShaderBufferType, int TextureIndex)
{
}

void CTexture::ResetShader(int Register, int ShaderBufferType)
{
}

bool CTexture::CreateResourceView(int Index)
{
	return false;
}
