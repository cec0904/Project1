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
	//육면체 
	// 8개의 점을 만든다. 
	FVertexColor BoxVtx[8] =
	{
		FVertexColor(-0.5f, 0.5f, -0.5f, 1.f, 0.f, 0.f, 1.f),	//0
		FVertexColor(0.5f, 0.5f, -0.5f, 0.f, 1.f, 0.f, 1.f),	//1
		FVertexColor(-0.5f, -0.5f, -0.5f, 0.f, 0.f, 1.f, 1.f),	//2
		FVertexColor(0.5f, -0.5f, -0.5f, 1.f, 1.f, 0.f, 1.f),	//3

		FVertexColor(-0.5f, 0.5f, 0.5f, 1.f, 0.f, 1.f, 1.f),	//4
		FVertexColor(0.5f, 0.5f, 0.5f, 0.f, 1.f, 1.f, 1.f),		//5
		FVertexColor(-0.5f, -0.5f, 0.5f, 1.f, 1.f, 1.f, 1.f),	//6
		FVertexColor(0.5f, -0.5f, 0.5f, 1.f, 0.f, 0.f, 1.f),	//7
	};

	//점들을 연결해줄 선들을 만들어 줘야한다. 

	//화면에는 앞면만 나오는데 
	// 앞면에 기준은 인덱스가 시계방향으로 그려줘야한다. 
	// 인덱스를 반시계 반향으로 그리면
	// 뒤면이 보이게 된다. 
	// 뒤면이 보이면 화면에 안그려지게 백스페이스 컬링이 된다. 

	unsigned short BoxIdx[36] =
	{
		0, 1, 3,  0, 3, 2,
		1, 5, 7,  1, 7, 3,
		5, 4, 6,  5, 6, 7,
		4, 0, 2,  4 ,2, 6,
		4, 5, 1,  4, 1, 0,
		2, 3, 7,  2, 7, 6
	};

	if (!CreateMesh("Box", BoxVtx, sizeof(FVertexColor), 8, D3D11_USAGE_DEFAULT, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, BoxIdx, sizeof(unsigned short), 36, DXGI_FORMAT_R16_UINT))
	{
		return false;
	}

	//사각형 
	FVertexColor CenterRect[4] =
	{
		FVertexColor(-0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f, 1.f),
		FVertexColor(0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f, 1.f),
		FVertexColor(-0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f, 1.f),
		FVertexColor(0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f, 1.f)
	};

	unsigned short RectIdx[6] = { 0 , 1, 3, 0, 3, 2 };

	if (!CreateMesh("CenterRect", CenterRect, sizeof(FVertexColor), 4, D3D11_USAGE_DEFAULT, D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST, RectIdx, sizeof(unsigned short), 6, DXGI_FORMAT_R16_UINT))
	{
		return false;
	}

	return true;
}

bool CMeshManager::CreateMesh(const string& Name, void* VertexData, int Size, int Count, D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitiv, void* IndexData, int IndexSize, int IndexCount, DXGI_FORMAT Fmt, D3D11_USAGE IndexUsage)
{
	// 메쉬 찾아오기
	// 기존에 같은이름을 등록된 mesh가 있는지 검사한다.
	CMesh* Mesh = FindMesh(Name);

	if (Mesh)
	{
		return true;
	}

	// 기존에 사용한 mesh가 없으면 새로 추가
	Mesh = new CStaticMesh;

	if (!Mesh->CreateMesh(VertexData, Size, Count, VertexUsage, Primitiv, IndexData,IndexSize, IndexCount, Fmt, IndexUsage))
	{
		SAFE_DELETE(Mesh);
		return false;
	}

	mMeshMap.insert(make_pair(Name, CSharedPtr<CMesh>(Mesh)));

	return true;
}

CMesh* CMeshManager::FindMesh(const string& Name)
{
	unordered_map<string, CSharedPtr<CMesh>>::iterator iter = mMeshMap.find(Name);

	if (iter == mMeshMap.end())
	{
		return nullptr;
	}

	return (CMesh*)iter->second.Get();
}
