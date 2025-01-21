#pragma once
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

// XMVECTOR는 using XMVECTOR = __m128;로 되어있는데,
// __m128 = 128bit, 즉 16byte를 의미한다.
//		※ 사용성(접근성)이 불편하고 난잡하여 쓰기 어렵다.
//DirectX::XMVECTOR

namespace EAxis
{
	enum Type
	{
		X,
		Y,
		Z,
		End
	};
}