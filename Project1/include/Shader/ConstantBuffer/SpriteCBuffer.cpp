#include "SpriteCBuffer.h"

CSpriteCBuffer::CSpriteCBuffer()
{
}

CSpriteCBuffer::CSpriteCBuffer(const CSpriteCBuffer& Data)
{
}

CSpriteCBuffer::CSpriteCBuffer(CSpriteCBuffer&& Data)
{
}

CSpriteCBuffer::~CSpriteCBuffer()
{
}
bool CSpriteCBuffer::Init()
{
	//
	SetConstantBuffer("Sprite");

	return true;
}

void CSpriteCBuffer::UpdateBuffer()
{
	mBuffer->Update(&mData);
}

CSpriteCBuffer* CSpriteCBuffer::Clone()
{
	return new CSpriteCBuffer(*this);
}

