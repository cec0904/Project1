﻿#include "Device.h"

CDevice::CDevice()
{

}
CDevice::~CDevice()
{
	SAFE_RELEASE(mTargetView);
	SAFE_RELEASE(mDepthView);
	SAFE_RELEASE(mSwapChain);

	// Context는 Device를 통해서 생성되기 때문에 Device보다 나중에 해제해야 한다.
	if (mContext)
	{
		// Context가 가지고 있는 모든 상태를 초기화 한다.
		mContext->ClearState();
	}

	SAFE_RELEASE(mContext);
	SAFE_RELEASE(mDevice);
}



bool CDevice::Init(HWND hWnd, unsigned int Width, unsigned int Height, bool WindowMode)
{
	mhWnd = hWnd;
	mRS.Width = Width;
	mRS.Height = Height;
	mWindowMode = WindowMode;

	// 디바이스 생성 플래그
	unsigned int Flag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;


#ifdef _DEBUG
	Flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif // DEBUG

	// 피처레벨
	// dx 버전 몇 쓸거임? 질문임
	D3D_FEATURE_LEVEL FLevel = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL FLevelResult;

	if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, Flag, &FLevel, 1, D3D11_SDK_VERSION, &mDevice, &FLevelResult, &mContext)))
	{
		// 디바이스 생성 실패
		return false;
	}

	// 멀티 샘플링
	// UNORM : 0 ~ 1 사이의 실수로 표현하겠다. 표현하는 방식
	// MSAA
	unsigned int SampleCount = 4;
	unsigned int Check = 0;
	mDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &Check);

	if (Check < 1)
	{
		SampleCount = 1;
	}

	// SwapChain 생성
	// DESC가 붙은 구조체가 나온다.
	// 이 구조체를 채워서 넣어주면 그 설정대로 원하는 것이 나온다.
	DXGI_SWAP_CHAIN_DESC SwapDesc = {};

	// 버퍼의 가로크기
	SwapDesc.BufferDesc.Width = Width;

	// 버퍼의 세로크기
	SwapDesc.BufferDesc.Height = Height;

	// 버퍼의 픽셀 포멧
	SwapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// 주사율
	// 화면 출력시 몇 번 그려질 건지
	// 화면 주사율 1/60 -> 초당 60분 화면에 그린다.
	SwapDesc.BufferDesc.RefreshRate.Numerator = 1;
	SwapDesc.BufferDesc.RefreshRate.Denominator = 60;

	// 스케일링
	// 화면 출력 시 스케일링(크기 조정) 방식을 시스템이나 드라이버에게 맡기겠다.
	SwapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	// 백버퍼의 수를 지정
	SwapDesc.BufferCount = 1;

	// 버퍼의 용도
	// DXGI_USAGE_RENDER_TARGET_OUTPUT : 버퍼를 화면 출력용으로 사용하겠다.
	SwapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// 출력할 윈도우 창을 정해줘야 하므로 윈도우 핸들을 요구한다.
	SwapDesc.OutputWindow = hWnd;

	// 멀티샘플링 여부 넣어줘야한다.
	// 멀티 샘플링(MSAA : Multi Sample Anit Aliasing)
	SwapDesc.SampleDesc.Quality = 0;	// 품질
	SwapDesc.SampleDesc.Count = SampleCount;	// 샘플링 카운트

	// 창모드 여부
	SwapDesc.Windowed = WindowMode;

	// 버퍼 전환
	// SwapChain 이 버퍼를 전환할 때 사용하는 동작을 지정한다.
	// DXGI_SWAP_EFFECT_DISCARD : 버퍼의 이전 내용을 무시하고 전환한다.
	SwapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// SwapChain버퍼를 만들 정보를 채운거다.
	// 만들기 위한 장치들을 불러와야 한다.

	// GDUI를 이용해서 버퍼를 만들기 위한 과정이다.
	// __uuidof :: 해당 클래스의 GUID를 얻어오는 연산자이다. 디바이스 구분
	IDXGIDevice* DXGIDevice = nullptr;
	mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&DXGIDevice);

	// 어댑터 ? 그래픽카드(GPU)와 비디오 출력장치
	IDXGIAdapter* Adapter = nullptr;
	DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&Adapter);

	IDXGIFactory* Factory = nullptr;
	Adapter->GetParent(__uuidof(IDXGIFactory), (void**)&Factory);

	if (FAILED(Factory->CreateSwapChain(mDevice, &SwapDesc, &mSwapChain)))
	{
		SAFE_RELEASE(Factory);
		SAFE_RELEASE(Adapter);
		SAFE_RELEASE(DXGIDevice);
		return false;
	}

	// 참조 카운트
	// 사용하고 꼭 지워줘야한다.
	SAFE_RELEASE(Factory);
	SAFE_RELEASE(Adapter);
	SAFE_RELEASE(DXGIDevice);


	// SwapChain에 사용할 진짜 "백버퍼"를 만들어 줘야한다.
	// 도화지를 만들어줘야한다.

	ID3D11Texture2D* BackBuffer = nullptr;

	if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer)))
	{
		return false;
	}
	if (FAILED(mDevice->CreateRenderTargetView(BackBuffer, nullptr, &mTargetView)))
	{
		return false;
	}

	SAFE_RELEASE(BackBuffer);

	// 깊이 스텐실 버퍼를 만들어 줄 것이다.
	D3D11_TEXTURE2D_DESC DepthDesc = {};

	DepthDesc.Width = Width;
	DepthDesc.Height = Height;
	DepthDesc.ArraySize = 1;

	// D24 : 깊이 24비트를 사용할 거고, UNORM(0~1)
	// S8 : 스텐실 8비트 UINT(0~256)
	DepthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	DepthDesc.SampleDesc.Count = SampleCount;
	DepthDesc.SampleDesc.Quality = 0;
	DepthDesc.MipLevels = 1;

	ID3D11Texture2D* DepthBuffer = nullptr;
	// 깊이 버퍼용 Texture2D를 생성한다.
	mDevice->CreateTexture2D(&DepthDesc, nullptr, &DepthBuffer);

	// 깊이 버퍼를 만들었다.
	if (FAILED(mDevice->CreateDepthStencilView(DepthBuffer, nullptr, &mDepthView)))
	{
		return false;
	}
	SAFE_RELEASE(DepthBuffer);

	// 뷰포트 만들기
	// 화면에 그려지는 화면을 뷰포트라고 한다.
	D3D11_VIEWPORT VP = {};
	VP.Width = (float)Width;
	VP.Height = (float)Height;
	VP.MaxDepth = 1.f;	// 깊이 버퍼 0~1로 표현한다. 그러므로 1을 넣어준다.
	mContext->RSSetViewports(1, &VP);


	
	return true;
}

void CDevice::ClearBackBuffer(float ClearColor[4])
{
	// 해당 색상으로 초기화 한다.
	mContext->ClearRenderTargetView(mTargetView, ClearColor);
}

void CDevice::ClearDepthStencil(float Depth, unsigned char Stencil)
{
	// 들어온 인자로 깊이와 스텐실을 초기화 하겠다.
	mContext->ClearDepthStencilView(mDepthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, Depth, Stencil);
}

void CDevice::SetTarget()
{
	mContext->OMSetRenderTargets(1, &mTargetView, mDepthView);
}

void CDevice::Render()
{
	// 페이지 플리핑
	mSwapChain->Present(0, 0);
}
