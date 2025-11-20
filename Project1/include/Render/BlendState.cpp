#include "BlendState.h"
#include "../GameManager/Device/Device.h"

CBlendState::CBlendState()
{
}

CBlendState::~CBlendState()
{
}

void CBlendState::SetBlendFactor(float r, float g, float b, float a)
{
}

void CBlendState::SetSampleMask(UINT Mask)
{
}

void CBlendState::AddBlendDesc(bool Enable, D3D11_BLEND Src, D3D11_BLEND Dest, D3D11_BLEND_OP BlendOp, D3D11_BLEND SrcAlpha, D3D11_BLEND DestAlpha, D3D11_BLEND_OP AlphaOp, UINT8 RenderTargetWriteMask)
{
}

bool CBlendState::CreateState(bool AlphaToCoverageEnable, bool IndependentBlendEnable)
{
    return false;
}

void CBlendState::SetState()
{
}

void CBlendState::ResetState()
{
}
