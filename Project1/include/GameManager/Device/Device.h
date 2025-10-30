﻿#pragma once
#include "../../GameInfo.h"


class CDevice
{
	// dx가 지원하는 친구들은 앞에 I가 붙는다.

	// Device : DX 기능을 모두 이 디바이스를 통해서 가져온다.
	ID3D11Device* mDevice = nullptr;

	// Context를 Device를 통해서 생성된다.
	// Context는 Device가 가지고 있는 기능을 실행시키는 역할을 한다.
	// 아마 Device보다 더 많이 사용할 친구이다.
	ID3D11DeviceContext* mContext = nullptr;

	// 페이지 플리핑
	// 화면을 갱신하기 위해서 추가한다.
	IDXGISwapChain* mSwapChain = nullptr;

	// 핸들은 디바이스에서도 한 번 더 들고 있는다.
	HWND mhWnd = nullptr;

	// 해상도
	// 이 해상도는 CreateWindow에서 사용한 윈도우 크기가 아닌, 실제 클라이언트 영역의 해상도이다.
	// 윈도우의 클라이언트 영역이랑은 해상도가 다를 수 있다.
	FResolution mRS;


	// 창 모드 여부
	bool mWindowMode = true;

	// 화면에 그려질 녀석
	ID3D11RenderTargetView* mTargetView = nullptr;

	// 깊이 스텐실
	ID3D11DepthStencilView* mDepthView = nullptr;

public:
	bool Init(HWND hWnd, unsigned int Width, unsigned int Height, bool WindowMode);

public:
	ID3D11Device* GetDevice() const
	{
		return mDevice;
	}

	ID3D11DeviceContext* GetContext() const
	{
		return mContext;
	}

	IDXGISwapChain* GetSwapChain() const
	{
		return mSwapChain;
	}

	const FResolution& GetResolution() const
	{
		return mRS;
	}

	bool GetWindowMode() const
	{
		return mWindowMode;
	}

public:
	void ClearBackBuffer(float ClearColor[4]);
	void ClearDepthStencil(float Depth, unsigned char Stencil);
	void SetTarget();	// 출력할 타겟을 지정해준다. 어떤 화면 그릴 지 지정해준다.

	// 화면에 출력하기
	void Render();

public:
	DECLARE_SINGLETONE(CDevice);
};

