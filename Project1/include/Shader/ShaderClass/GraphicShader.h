#pragma once
#include "Shader.h"

class CGraphicShader abstract : public CShader
{
	friend class CShaderManager;

protected:
	CGraphicShader();
	virtual ~CGraphicShader();

private:
	// 입력 레이아웃
	// 정점 구조가 어떻게 구성되어 있는지 알려주는 것이다.
	// FVertexColor == VS_Input_Color 같은 타입이다 라고 알려주는 것이다. 매칭시켜준다.
	ID3D11InputLayout* mInputLayout = nullptr;

	// 레지스터에 지정을 위한 구조체 이다.
	vector<D3D11_INPUT_ELEMENT_DESC> mveDesc;

	unsigned int mInputLayerSize = 0;

	// 해당 쉐이더 클래스가 사용할 쉐이더들 들고있는다.

	// 정점 쉐이더
	ID3D11VertexShader* mVS = nullptr;	// 쉐이더의 객체
	// 쉐이더를 컴파일 해서 들고있을 버퍼 Blob이다.
	ID3DBlob* mVSBlob = nullptr;	// 컴파일된 쉐이더를 담고있는 버퍼

	// 픽셀 쉐이더
	ID3D11PixelShader* mPS = nullptr;
	ID3DBlob* mPSBlob = nullptr;

	// 훌 쉐이더
	ID3D11HullShader* mHS = nullptr;
	ID3DBlob* mHSBlob = nullptr;

	// 도메인 쉐이더
	ID3D11DomainShader* mDS = nullptr;
	ID3DBlob* mDSBlob = nullptr;

	// 지오메트리 쉐이더
	ID3D11GeometryShader* mGS = nullptr;
	ID3DBlob* mGSBlob = nullptr;

public:
	void AddInputLayoutDesc(const char* Sementic, unsigned int SementicIndex, DXGI_FORMAT Fmt, unsigned int InputSlot, unsigned int Size, D3D11_INPUT_CLASSIFICATION InputSlotClass, unsigned int InstanceDataStepRate);
	bool CreateInputLayout();

	// 쉐이더를 불러오는 함수
	bool LoadVertexShader(const char* EntryName, const TCHAR* FileName);
	bool LoadPixelShader(const char* EntryName, const TCHAR* FileName);
	bool LoadHullShader(const char* EntryName, const TCHAR* FileName);
	bool LoadDomainShader(const char* EntryName, const TCHAR* FileName);
	bool LoadGeometryShader(const char* EntryName, const TCHAR* FileName);

public:
	virtual bool Init();

	// final
	// 이 함수는 더 이상 오버라이딩 하지 않겠다.
	virtual void SetShader() final;
};

