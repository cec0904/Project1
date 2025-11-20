#include "RenderStateManager.h"
#include "BlendState.h"

CRenderStateManager::CRenderStateManager()
{
}
CRenderStateManager::~CRenderStateManager()
{
	auto iter = mRenderStateMap.begin();
	auto iterEnd = mRenderStateMap.end();

	for (; iter != iterEnd; iter++)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CRenderStateManager::Init()
{
	AddBlendDesc("AlphaBlend", true, D3D11_BLEND_SRC_ALPHA,
		D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ZERO, D3D11_BLEND_OP_ADD, D3D11_COLOR_WRITE_ENABLE_ALL);
	CreateBlendState("AlphaBlend", true, true);

	return true;
}

void CRenderStateManager::SetBlendFactor(const string& Name, float r, float g, float b, float a)
{
	CBlendState* State = (CBlendState*)FindState(Name);

	if (!State)
	{
		State = new CBlendState;
		mRenderStateMap.insert(make_pair(Name, State));
	}
	State->SetBlendFactor(r, g, b, a);
}

void CRenderStateManager::SetSampleMask(const string& Name, UINT Mask)
{
}

void CRenderStateManager::AddBlendDesc(const string& Name, bool Enable, D3D11_BLEND Src, D3D11_BLEND Dest, D3D11_BLEND_OP BlendOp, D3D11_BLEND SrcAlpha, D3D11_BLEND DestAlpha, D3D11_BLEND_OP AlphaOp, UINT8 RenderTargetWriteMask)
{
}

bool CRenderStateManager::CreateBlendState(const string& Name, bool AlphaToCoverageEnable, bool IndependentBlendEnable)
{
	return false;
}

CRenderState* CRenderStateManager::FindState(const string& Name)
{
	return nullptr;
}
