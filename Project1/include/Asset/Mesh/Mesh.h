#pragma once
#include "../../GameInfo.h"
#include "../Asset.h"

/*
	메쉬는
	정점(버텍스)와 인덱스(정점을 어떻게 연결 할 것인지) 버퍼들을 만들고

	정면부분 LED 부분
	안보여지는 후면 부분을 CASE 부분이라고 한다.
	뒷면이라도 정점을 만들어놔야 한다.

	메쉬 타입을 만들어서 이를 공유 포인터를 만들어서 관리할 것이다.
*/


// 용도 : 정점버퍼와 인덱스 버퍼를 관리하기 위해서 슬록으로 만들었다.
struct FMeshSlot
{
	// 인덱스 버퍼 : 여러 곳에서 사용할 수 있다.
	FIndexBuffer IndexBuffer;
};

class CMesh abstract : public CAsset
{
public:
	CMesh();
	virtual ~CMesh();

protected:
	// 정점버퍼
	FVertexBuffer mVertexBuffer;
	// 메쉬 슬롯
	vector<FMeshSlot*> mMeshSlot;

	D3D11_PRIMITIVE_TOPOLOGY mPrimitive;

public:
	virtual bool CreateMesh(void* VertexData, int Size, int Count, D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitiv, void* IndexData = nullptr, int IndexSize = 0, int IndexCount = 0, DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN, D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);

public:
	bool CreateBuffer(ID3D11Buffer** Buffer, D3D11_BIND_FLAG Flag, void* Data, int Size, int Count, D3D11_USAGE Usage);

public:
	void Render();


};

