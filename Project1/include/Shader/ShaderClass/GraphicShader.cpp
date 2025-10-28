#include "GraphicShader.h"
#include "../../GameManager/Device/Device.h"

CGraphicShader::CGraphicShader()
{
}

CGraphicShader::~CGraphicShader()
{
	SAFE_RELEASE(mInputLayout);

	SAFE_RELEASE(mVS);
	SAFE_RELEASE(mVSBlob);

	SAFE_RELEASE(mPS);
	SAFE_RELEASE(mPSBlob);

	SAFE_RELEASE(mHS);
	SAFE_RELEASE(mHSBlob);

	SAFE_RELEASE(mDS);
	SAFE_RELEASE(mDSBlob);

	SAFE_RELEASE(mGS);
	SAFE_RELEASE(mGSBlob);
}

void CGraphicShader::AddInputLayoutDesc(const char* Sementic, unsigned int SementicIndex, DXGI_FORMAT Fmt, unsigned int InputSlot, unsigned int Size, D3D11_INPUT_CLASSIFICATION InputSlotClass, unsigned int InstanceDataStepRate)
{
	D3D11_INPUT_ELEMENT_DESC Desc = {};

	Desc.SemanticIndex = SementicIndex;
	Desc.SemanticName = Sementic;

	Desc.Format = Fmt;

	// 인스턴싱을 이용할 때 사용하게 된다.
	Desc.InputSlot = InputSlot;
	Desc.InstanceDataStepRate = InstanceDataStepRate;
	Desc.InputSlotClass = InputSlotClass;

	// 해당 데이터 메모리 위치 오프셋
	Desc.AlignedByteOffset = mInputLayerSize;
	mInputLayerSize += Size;

	// emplace_back:
	mveDesc.emplace_back(Desc);
}

bool CGraphicShader::CreateInputLayout()
{
	// 레이아웃
	if (FAILED(CDevice::GetInst()->GetDevice()->CreateInputLayout(&mveDesc[0], (UINT)mveDesc.size(), mVSBlob->GetBufferPointer(), mVSBlob->GetBufferSize(), &mInputLayout)))
	{
		return false;
	}
	return true;
}

// FileName에는 파일명만 넣어줄 것이고
// 풀 경로는 따로 구할 것이다.
bool CGraphicShader::LoadVertexShader(const char* EntryName, const TCHAR* FileName)
{
	TCHAR FullPath[MAX_PATH] = {};
	lstrcpy(FullPath, TEXT("../bin/Shader"));
	lstrcat(FullPath, FileName);
	// 우리가 원하는 쉐이더 파일의 풀 경로가 나온다.


	// 컴파일 했는데 에러가 나면 여기에 들어올 것이다.
	ID3DBlob* ErrorBlob = nullptr;

	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif // DEBUG

	// 쉐이더 컴파일러
	if (FAILED(D3DCompileFromFile(FullPath, nullptr,D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName, "vs_5_0", Flag, 0, &mVSBlob, &ErrorBlob)))
	{
#ifdef _DEBUG
		/*char ErrorText[512] = {};
		strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
		strcat_s(ErrorText, "\n");
		OutputDebugStringA(ErrorText);*/

		char ErrorText[512] = {};
		if (ErrorBlob)
			strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
		else
			strcpy_s(ErrorText, "Shader compile failed and no error blob was returned.");
		strcat_s(ErrorText, "\n");
		OutputDebugStringA(ErrorText);

#endif // DEBUG
		return false;
	}

	// 컴파일이 성공했으면 해당 쉐이더로 객체를 생성시켜줘야한다.
	// GetBufferPointer -> 컴파일 된 코드 
	// GetBufferSize -> 컴파일 된 코드의 크기 

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer(), mVSBlob->GetBufferSize(), nullptr, &mVS)))
	{
	return false;
		
	}
	return true;
}

bool CGraphicShader::LoadPixelShader(const char* EntryName, const TCHAR* FileName)
{
	TCHAR FullPath[MAX_PATH] = {};
	lstrcpy(FullPath, TEXT("../bin/Shader/"));
	lstrcat(FullPath, FileName);

	// 컴파일 했는데 에러가 나면 여기에 들어 올 것이다.
	ID3DBlob* ErrorBlob = nullptr;

	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif // _DEBUG

	// 쉐이더 컴파일러
	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName, "ps_5_0", Flag, 0, &mPSBlob, &ErrorBlob)))
	{
#ifdef _DEBUG
		char ErrorText[512] = {};
		strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
		strcat_s(ErrorText, "\n");
		OutputDebugStringA(ErrorText);
#endif // _DEBUG
		return false;
	}

	if (FAILED(CDevice::GetInst()->GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer(), mPSBlob->GetBufferSize(), nullptr, &mPS)))
	{
		return false;
	}
	return true;
}

bool CGraphicShader::LoadHullShader(const char* EntryName, const TCHAR* FileName)
{
	TCHAR FullPath[MAX_PATH] = {};
	lstrcpy(FullPath, TEXT("../bin/Shader/"));
	lstrcat(FullPath, FileName);

	// 컴파일 했는데 에러가 나면 여기에 들어 올 것이다.
	ID3DBlob* ErrorBlob = nullptr;

	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif // _DEBUG

	// 쉐이더 컴파일러
	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName, "hs_5_0", Flag, 0, &mHSBlob, &ErrorBlob)))
	{
#ifdef _DEBUG
		char ErrorText[512] = {};
		strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
		strcat_s(ErrorText, "\n");
		OutputDebugStringA(ErrorText);
#endif // _DEBUG
		return false;
	}

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateHullShader(mHSBlob->GetBufferPointer(), mHSBlob->GetBufferSize(), nullptr, &mHS)))
	{
		return false;
	}
	return true;
}

bool CGraphicShader::LoadDomainShader(const char* EntryName, const TCHAR* FileName)
{
	TCHAR FullPath[MAX_PATH] = {};
	lstrcpy(FullPath, TEXT("../bin/Shader/"));
	lstrcat(FullPath, FileName);

	// 컴파일 했는데 에러가 나면 여기에 들어 올 것이다.
	ID3DBlob* ErrorBlob = nullptr;

	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif // _DEBUG

	// 쉐이더 컴파일러
	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName, "ds_5_0", Flag, 0, &mDSBlob, &ErrorBlob)))
	{
#ifdef _DEBUG
		char ErrorText[512] = {};
		strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
		strcat_s(ErrorText, "\n");
		OutputDebugStringA(ErrorText);
#endif // _DEBUG
		return false;
	}

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateDomainShader(mDSBlob->GetBufferPointer(), mDSBlob->GetBufferSize(), nullptr, &mDS)))
	{
		return false;
	}
	return true;
}

bool CGraphicShader::LoadGeometryShader(const char* EntryName, const TCHAR* FileName)
{
	TCHAR FullPath[MAX_PATH] = {};
	lstrcpy(FullPath, TEXT("../bin/Shader/"));
	lstrcat(FullPath, FileName);

	// 컴파일 했는데 에러가 나면 여기에 들어 올 것이다.
	ID3DBlob* ErrorBlob = nullptr;

	unsigned int Flag = 0;
#ifdef _DEBUG
	Flag = D3DCOMPILE_DEBUG;
#endif // _DEBUG

	// 쉐이더 컴파일러
	if (FAILED(D3DCompileFromFile(FullPath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName, "gs_5_0", Flag, 0, &mGSBlob, &ErrorBlob)))
	{
#ifdef _DEBUG
		char ErrorText[512] = {};
		strcpy_s(ErrorText, (const char*)ErrorBlob->GetBufferPointer());
		strcat_s(ErrorText, "\n");
		OutputDebugStringA(ErrorText);
#endif // _DEBUG
		return false;
	}

	if (FAILED(CDevice::GetInst()->GetDevice()->CreateGeometryShader(mGSBlob->GetBufferPointer(), mGSBlob->GetBufferSize(), nullptr, &mGS)))
	{
		return false;
	}
	return true;
}

bool CGraphicShader::Init()
{
	return true;
}

void CGraphicShader::SetShader()
{
	// 내가 출력에 사용하고자 하는 쉐이더를 지정해준다.
	// 생성한 쉐이더들을 사용할거라고 지정해준다.
	CDevice::GetInst()->GetContext()->VSSetShader(mVS, nullptr, 0);
	CDevice::GetInst()->GetContext()->PSSetShader(mPS, nullptr, 0);
	CDevice::GetInst()->GetContext()->HSSetShader(mHS, nullptr, 0);
	CDevice::GetInst()->GetContext()->DSSetShader(mDS, nullptr, 0);
	CDevice::GetInst()->GetContext()->GSSetShader(mGS, nullptr, 0);



	CDevice::GetInst()->GetContext()->IASetInputLayout(mInputLayout);
}
