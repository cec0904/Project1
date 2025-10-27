#include "MeshManager.h"

#include "StaticMesh.h"

CMeshManager::CMeshManager()
{
}
CMeshManager::~CMeshManager()
{
}

bool CMeshManager::Init()
{
	// 육면체
	// 8개의 점을 만든다.
}

bool CMeshManager::CreateMesh(const string& Name, void* VertexData, int Size, int Count, D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitiv, void* IndexData, int IndexSize, int IndexCount, DXGI_FORMAT Fmt, D3D11_USAGE IndexUsage)
{
	return false;
}

CMesh* CMeshManager::FindMesh(const string& Name)
{
	return nullptr;
}
