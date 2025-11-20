#pragma once
#include "RenderState.h"

class CBlendState :
	public CRenderState
{
	friend class CRenderStateManager;

protected:
	CBlendState();
	virtual ~CBlendState();

protected:
	// DX11 은 최대 8개의 렌더타겟을 지원한다.
	vector<D3D11_RENDER_TARGET_BLEND_DESC> mDesc;
	// 색상을 섞어줄 때 사용하는 RGBA값
	float mBlendFactor[4] = {};
	float mPrevBlendFactor[4] = {};
	// 색상을 걸러내는 용도
	UINT mSampleMask = 0xffffffff;
	UINT mPrevSampleMask = 0;

public:
	void SetBlendFactor(float r, float g, float b, float a);
	void SetSampleMask(UINT Mask);
	// Src : 출력물체 대상
	// Dest : 백버퍼
	void AddBlendDesc(bool Enable,
		D3D11_BLEND Src, D3D11_BLEND Dest, D3D11_BLEND_OP BlendOp,
		D3D11_BLEND SrcAlpha, D3D11_BLEND DestAlpha, D3D11_BLEND_OP AlphaOp,
		UINT8 RenderTargetWriteMask);
	bool CreateState(bool AlphaToCoverageEnable, bool IndependentBlendEnable);

	/*
		BOOL BlendEnable;
		D3D11_BLEND SrcBlend;
		D3D11_BLEND DestBlend;
		D3D11_BLEND_OP BlendOp;
		D3D11_BLEND SrcBlendAlpha;
		D3D11_BLEND DestBlendAlpha;
		D3D11_BLEND_OP BlendOpAlpha;
		UINT8 RenderTargetWriteMask;
	 */

public:
	// 내 블랜드 스테이트로 설정해줘
	virtual void SetState() override;
	// 이전 스테이트로 복구해줘
	virtual void ResetState() override;

};

