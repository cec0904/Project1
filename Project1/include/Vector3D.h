#pragma once

#include <math.h>
#include "EngineMath.h"


struct FVector3D
{
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;


#pragma region Construction
	FVector3D();
	FVector3D(float _x, float _y, float _z);
	FVector3D(const FVector3D& _v);
	FVector3D(FVector3D&& _v);
	FVector3D(const DirectX::XMVECTOR& v);

#pragma endregion

#pragma region Equal

	const FVector3D& operator = (const FVector3D& _v);
	const FVector3D& operator = (float Value);
	const FVector3D& operator = (double Value);
	const FVector3D& operator = (int Value);
#pragma endregion 

#pragma region Plus
	FVector3D operator + (const FVector3D& _v)	const;
	FVector3D operator + (float Value) const;
	FVector3D operator + (double Value) const;
	FVector3D operator + (int  Value) const;

	// += 
	const FVector3D& operator += (const FVector3D& _v);
	const FVector3D& operator += (float Value);
	const FVector3D& operator += (double Value);
	const FVector3D& operator += (int Value);

	//++
	const FVector3D& operator ++ (); //전위
	const FVector3D& operator ++ (int); //후위

#pragma endregion

#pragma region Minus

	FVector3D operator - (const FVector3D& _v)	const;

	FVector3D operator - (float Value) const;
	FVector3D operator - (double Value) const;
	FVector3D operator - (int  Value) const;

	// -= 
	const FVector3D& operator -= (const FVector3D& _v);
	const FVector3D& operator -= (float Value);
	const FVector3D& operator -= (double Value);
	const FVector3D& operator -= (int Value);
	//--
	const FVector3D& operator -- (); //전위 
	const FVector3D& operator -- (int); //후위
#pragma endregion

#pragma region Multiply
	FVector3D operator * (const FVector3D& _v)	const;
	FVector3D operator * (float Value) const;
	FVector3D operator * (double Value) const;
	FVector3D operator * (int  Value) const;

	// *= 
	const FVector3D& operator *= (const FVector3D& _v);
	const FVector3D& operator *= (float Value);
	const FVector3D& operator *= (double Value);
	const FVector3D& operator *= (int Value);

#pragma endregion

#pragma region Divide
	FVector3D operator / (const FVector3D& _v)	const;
	FVector3D operator / (float Value) const;
	FVector3D operator / (double Value) const;
	FVector3D operator / (int  Value) const;

	// /= 
	const FVector3D& operator /= (const FVector3D& _v);
	const FVector3D& operator /= (float Value);
	const FVector3D& operator /= (double Value);
	const FVector3D& operator /= (int Value);
#pragma endregion

#pragma region Function

	//벡터의 크기를 구한다. 
	float Length() const;

	//정규화 Normalize
	void Normalize(); //해당 vector을 단위백터로 만들어준다. -> 크기가 1인 벡터로 만드는 기능을 한다. 

	static FVector3D Normalize(const FVector3D& _v);	//벡터가 들어오면 단위벡터를 만들어서 내보내준다. 

	float Dot(const FVector3D& _v) const;

	FVector3D Cross(const FVector3D& _v) const;

	//두 벡터의 거리를 구한다. 
	float Distnace(const FVector3D& _v) const;

	DirectX::XMVECTOR Convert() const;

	//TransformNormal	: 행렬을 곱할때 W값을 0으로하냐
	FVector3D TransformNormal(union FMatrix& mat) const;
	//TrnasformCoord	: 행렬을 곱할때 W값을 1로 하냐 
	FVector3D TransformCoord(union FMatrix& mat) const;
	FVector3D GetRotation(const FVector3D& Rot) const;


#pragma endregion



};