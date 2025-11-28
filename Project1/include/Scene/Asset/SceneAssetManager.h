#pragma once
#include "../../GameInfo.h"
#include <unordered_map>

class CSceneAssetManager
{
	friend class CScene;

private:
	CSceneAssetManager();
	~CSceneAssetManager();

private:
	class CScene* mScene = nullptr;

private:
	// 관리할 에셋들
	unordered_map<string, CSharedPtr<class CAsset>> mAssetMap;

public:
	bool Init();

#pragma region Mesh

	bool CreateMesh(const std::string& Name, void* VertexData, int Size, int Count, D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitiv, void* IndexData = nullptr, int IndexSize = 0, int IndexCount = 0, DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN, D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

	class CMesh* FindMesh(const std::string& Name);

#pragma endregion Mesh

#pragma region Texture
	bool LoadTexture(const string& Name, const TCHAR* FileName);
	bool LoadTextureFullPath(const string& Name, const TCHAR* FullPath);

	// 텍스쳐 여러장 불러오기
	bool LoadTexture(const string& Name, const vector<const TCHAR*>& FileName);
	bool LoadTextureFullPath(const string& Name, const vector<const TCHAR*>& FullPath);
	// 규칙적인 파일이름으로 여러장 불러온다.
	bool LoadTexture(const string& Name, const TCHAR* FileName, const TCHAR* Ext, int Count);

	class CTexture* FindTexture(const string& Name);
#pragma endregion Texture

#pragma region Material
	bool CreateMaterial(const string& Name);

	class CMaterial* FindMaterial(const string& Name);

#pragma endregion Material
};

