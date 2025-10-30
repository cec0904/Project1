#pragma once


// DirectXMath 헤더 : 벡터/행렬 수학 기능 제공
// 내부적으로 SIMD(__m128) 16바이트 단위 연산을 사용
// 64bit 환경은 기본적으로 16바이트 정렬 지원
// 32bit 환경에서는 __declspec(align(16)) 필요할 수도 있음
#include <DirectXMath.h>

// DirectXPackedVector : 정밀도가 낮은 벡터(색상, 노멀 등) 압축 표현 제공
// GPU 버퍼 호환용 타입 (예: XMCOLOR, XMUBYTE4)
#include <DirectXPackedVector.h>


namespace EAxis
{
	enum Type
	{
		None = -1,
		X,
		Y,
		Z,
		End
	};
}