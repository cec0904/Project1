#pragma once
#include <math.h>

#include "EngineMath.h"

/*
	2차원 방향 벡터 구조체를 만들 것이다.
	벡터는 방향과 힘이 있는 것이다. 좌표값은 없다.
	(1, 1) x축으로 1만큼, y축으로 1만큼 이동할 것이다.
	(-1, 10) x축으로 -1만큼, y축으로 10만큼 이동할 것이다.
*/

struct FVector2D
{
	float x = 0.f;
	float y = 0.f;

#pragma region Construction
	FVector2D()
	{

	}
	FVector2D(float _x, float _y)
		: x(_x), y(_y)
	{

	}
	FVector2D(const FVector2D& _v)
		: x(_v.x), y(_v.y)
	{

	}
	FVector2D(FVector2D&& _v) noexcept
		: x(_v.x), y(_v.y)

	{

	}
#pragma endregion

#pragma region Equal

	const FVector2D& operator = (const FVector2D& _v)
	{
		x = _v.x;
		y = _v.y;
		return *this;
	}

	const FVector2D& operator = (float Value)
	{
		x = Value;
		y = Value;
		return *this;
	}
	const FVector2D& operator = (double Value)
	{
		x = (float)Value;
		y = (float)Value;
		return *this;
	}
	const FVector2D& operator = (int Value)
	{
		x = (float)Value;
		y = (float)Value;
		return *this;
	}
#pragma endregion

#pragma region Plus
	FVector2D operator + (const FVector2D& _v) const
	{
		FVector2D result;
		result.x = x + _v.x;
		result.y = y + _v.y;
		return result;
	}

	FVector2D operator + (float Value) const
	{
		FVector2D result;
		result.x = x + Value;
		result.y = y + Value;
		return result;
	}
	FVector2D operator + (double Value) const
	{
		FVector2D result;
		result.x = x + (float)Value;
		result.y = y + (float)Value;
		return result;
	}
	FVector2D operator + (int Value) const
	{
		FVector2D result;
		result.x = x + (float)Value;
		result.y = y + (float)Value;
		return result;
	}


	//+=
	const FVector2D& operator += (const FVector2D& _v)
	{
		x += _v.x;
		y += _v.y;
		return *this;
	}
	FVector2D operator += (float Value)
	{
		x += Value;
		y += Value;
		return *this;
	}
	FVector2D operator += (double Value)
	{
		x += (float)Value;
		y += (float)Value;
		return *this;
	}
	FVector2D operator += (int Value)
	{
		x += (float)Value;
		y += (float)Value;
		return *this;
	}

	//++
	const FVector2D& operator ++ ()
	{
		x += 1.f;
		y += 1.f;
		return *this;
	}
	const FVector2D& operator ++ (int)	// 후위
	{
		FVector2D temp = { x,y };
		x += 1.f;
		y += 1.f;
		return temp;
	}

#pragma endregion

#pragma region Minus
	FVector2D operator - (const FVector2D& _v) const
	{
		FVector2D result;
		result.x = x - _v.x;
		result.y = y - _v.y;
		return result;
	}

	FVector2D operator - (float Value) const
	{
		FVector2D result;
		result.x = x - Value;
		result.y = y - Value;
		return result;
	}
	FVector2D operator - (double Value) const
	{
		FVector2D result;
		result.x = x - (float)Value;
		result.y = y - (float)Value;
		return result;
	}
	FVector2D operator - (int Value) const
	{
		FVector2D result;
		result.x = x - (float)Value;
		result.y = y - (float)Value;
		return result;
	}


	//-=
	const FVector2D& operator -= (const FVector2D& _v)
	{
		x -= _v.x;
		y -= _v.y;
		return *this;
	}
	FVector2D operator -= (float Value)
	{
		x -= Value;
		y -= Value;
		return *this;
	}
	FVector2D operator -= (double Value)
	{
		x -= (float)Value;
		y -= (float)Value;
		return *this;
	}
	FVector2D operator -= (int Value)
	{
		x -= (float)Value;
		y -= (float)Value;
		return *this;
	}

	// --
	const FVector2D& operator -- ()
	{
		x -= 1.f;
		y -= 1.f;
		return *this;
	}
	const FVector2D& operator -- (int)	// 후위
	{
		FVector2D temp = { x,y };
		x -= 1.f;
		y -= 1.f;
		return temp;
	}

#pragma endregion

#pragma region Multiply
	FVector2D operator * (const FVector2D& _v) const
	{
		FVector2D result;
		result.x = x * _v.x;
		result.y = y * _v.y;
		return result;
	}

	FVector2D operator * (float Value) const
	{
		FVector2D result;
		result.x = x * Value;
		result.y = y * Value;
		return result;
	}
	FVector2D operator * (double Value) const
	{
		FVector2D result;
		result.x = x * (float)Value;
		result.y = y * (float)Value;
		return result;
	}
	FVector2D operator * (int Value) const
	{
		FVector2D result;
		result.x = x * (float)Value;
		result.y = y * (float)Value;
		return result;
	}


	//*=
	const FVector2D& operator *= (const FVector2D& _v)
	{
		x *= _v.x;
		y *= _v.y;
		return *this;
	}
	FVector2D operator *= (float Value)
	{
		x *= Value;
		y *= Value;
		return *this;
	}
	FVector2D operator *= (double Value)
	{
		x *= (float)Value;
		y *= (float)Value;
		return *this;
	}
	FVector2D operator *= (int Value)
	{
		x *= (float)Value;
		y *= (float)Value;
		return *this;
	}

#pragma endregion

#pragma region Divide
	FVector2D operator / (const FVector2D& _v) const
	{
		FVector2D result;
		result.x = x / _v.x;
		result.y = y / _v.y;
		return result;
	}

	FVector2D operator / (float Value) const
	{
		FVector2D result;
		result.x = x / Value;
		result.y = y / Value;
		return result;
	}
	FVector2D operator / (double Value) const
	{
		FVector2D result;
		result.x = x / (float)Value;
		result.y = y / (float)Value;
		return result;
	}
	FVector2D operator / (int Value) const
	{
		FVector2D result;
		result.x = x / (float)Value;
		result.y = y / (float)Value;
		return result;
	}


	// /=
	const FVector2D& operator /= (const FVector2D& _v)
	{
		x /= _v.x;
		y /= _v.y;
		return *this;
	}
	FVector2D operator /= (float Value)
	{
		x /= Value;
		y /= Value;
		return *this;
	}
	FVector2D operator /= (double Value)
	{
		x /= (float)Value;
		y /= (float)Value;
		return *this;
	}
	FVector2D operator /= (int Value)
	{
		x /= (float)Value;
		y /= (float)Value;
		return *this;
	}

#pragma endregion



#pragma region Function
	// 벡터의 크기를 구한다.
	float Length() const
	{
		// 피타고라스를 이용해서 벡터의 크기를 구했다.
		return sqrtf(x * x + y * y);
	}

	// 정규화 Normalize

	// 해당 vector를 단위벡터로 만들어준다. -> 크기가 1인 벡터로 만드는 기능을 한다.
	void Normalize()
	{
		float size = Length();
		if (0.f == size)
		{
			return;
		}

		x /= size;
		y /= size;
	}

	static FVector2D Normalize(const FVector2D& _v)	// 벡터가 들어오면 단위벡터를 만들어서 내보내준다.
	{
		FVector2D result;

		float size = _v.Length();

		if (size == 0.f)
		{
			return result;
		}

		result.x = _v.x / size;
		result.y = _v.y / size;
		return result;
	}
		

		float Dot(const FVector2D & _v) const
		{
			// 내적
			return x * _v.x + y * _v.y;
		}

		// 두 벡터의 거리를 구한다.
		float Distance(const FVector2D& _v) const
		{
			FVector2D diff = *this - _v;
			return diff.Length();
		}

#pragma endregion

};