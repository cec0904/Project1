#pragma once


#include "../GameInfo.h"

class CRenderStateManager
{
	friend class CRenderManager;

private:
	CRenderStateManager();
	~CRenderStateManager();

private:
	unordered_map<string, class CRenderState*> mRenderStateMap;

public:
	bool Init();

public:
	void SetBlendFactor(const string& Name, float r, float g, float b, float a);
	void SetSampleMask(const string& Name, UINT Mask);
	// src : 출력물체 대상
	// Dest : 백버퍼
	void AddBlendDesc(const string& Name, bool Enable, D3D11_BLEND Src, D3D11_BLEND Dest, D3D11_BLEND_OP BlendOp,
		D3D11_BLEND SrcAlpha, D3D11_BLEND DestAlpha, D3D11_BLEND_OP AlphaOp,
		UINT8 RenderTargetWriteMask);

	bool CreateBlendState(const string& Name, bool AlphaToCoverageEnable, bool IndependentBlendEnable);

	class CRenderState* FindState(const string& Name);

};

