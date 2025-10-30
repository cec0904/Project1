#include "Vector3D.h"
#include "Matrix.h"

FVector3D FVector3D::Zero = { 0.f, 0.f, 0.f };
FVector3D FVector3D::One = { 1.f, 1.f, 1.f };
FVector3D FVector3D::Axis[EAxis::End] =
{
	{1.f, 0.f, 0.f},
	{0.f, 1.f, 0.f},
	{0.f, 0.f, 1.f}
};



#pragma region Construction
FVector3D::FVector3D()
{
}

FVector3D::FVector3D(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z)
{
}

FVector3D::FVector3D(const FVector3D& _v)
	: x(_v.x), y(_v.y), z(_v.z)
{
}

FVector3D::FVector3D(FVector3D&& _v)
	: x(_v.x), y(_v.y), z(_v.z)
{
}

FVector3D::FVector3D(const DirectX::XMVECTOR& v)
{
	DirectX::XMStoreFloat3((DirectX::XMFLOAT3*)this, v);
}

#pragma endregion

#pragma region Equal

const FVector3D& FVector3D::operator = (const FVector3D& _v)
{
	x = _v.x;
	y = _v.y;
	z = _v.z;
	return *this;
}

const FVector3D& FVector3D::operator=(const DirectX::XMVECTOR& v)
{
	DirectX::XMStoreFloat3((DirectX::XMFLOAT3*)this, v);
	return *this;
}

const FVector3D& FVector3D::operator = (float Value)
{
	x = Value;
	y = Value;
	z = Value;
	return *this;
}
const FVector3D& FVector3D::operator = (double Value)
{
	x = (float)Value;
	y = (float)Value;
	z = (float)Value;
	return *this;
}
const FVector3D& FVector3D::operator = (int Value)
{
	x = (float)Value;
	y = (float)Value;
	z = (float)Value;
	return *this;
}
#pragma endregion 

#pragma region Plus
FVector3D FVector3D::operator + (const FVector3D& _v)	const
{
	FVector3D result;
	result.x = x + _v.x;
	result.y = y + _v.y;
	result.z = z + _v.z;
	return result;
}

FVector3D FVector3D::operator + (float Value) const
{
	FVector3D result;
	result.x = x + Value;
	result.y = y + Value;
	result.z = z + Value;
	return result;
}
FVector3D FVector3D::operator + (double Value) const
{
	FVector3D result;
	result.x = x + (float)Value;
	result.y = y + (float)Value;
	result.z = z + (float)Value;
	return result;
}
FVector3D FVector3D::operator + (int  Value) const
{
	FVector3D result;
	result.x = x + (float)Value;
	result.y = y + (float)Value;
	result.z = z + (float)Value;
	return result;
}

// += 

const FVector3D& FVector3D::operator += (const FVector3D& _v)
{
	x += _v.x;
	y += _v.y;
	z += _v.z;
	return *this;
}

const FVector3D& FVector3D::operator += (float Value)
{
	x += Value;
	y += Value;
	z += Value;
	return *this;
}
const FVector3D& FVector3D::operator += (double Value)
{
	x += (float)Value;
	y += (float)Value;
	z += (float)Value;
	return *this;
}
const FVector3D& FVector3D::operator += (int Value)
{
	x += (float)Value;
	y += (float)Value;
	z += (float)Value;
	return *this;
}

//++
const FVector3D& FVector3D::operator ++ () //전위 
{
	x += 1.f;
	y += 1.f;
	z += 1.f;
	return *this;
}

const FVector3D& FVector3D::operator ++ (int) //후위
{
	FVector3D temp = { x, y, z };
	x += 1.f;
	y += 1.f;
	z += 1.f;
	return temp;
}

#pragma endregion

#pragma region Minus

FVector3D FVector3D::operator - (const FVector3D& _v)	const
{
	FVector3D result;
	result.x = x - _v.x;
	result.y = y - _v.y;
	result.z = z - _v.z;
	return result;
}

FVector3D FVector3D::operator - (float Value) const
{
	FVector3D result;
	result.x = x - Value;
	result.y = y - Value;
	result.z = z - Value;
	return result;
}
FVector3D FVector3D::operator - (double Value) const
{
	FVector3D result;
	result.x = x - (float)Value;
	result.y = y - (float)Value;
	result.z = z - (float)Value;
	return result;
}
FVector3D FVector3D::operator - (int  Value) const
{
	FVector3D result;
	result.x = x - (float)Value;
	result.y = y - (float)Value;
	result.z = z - (float)Value;
	return result;
}

// -= 

const FVector3D& FVector3D::operator -= (const FVector3D& _v)
{
	x -= _v.x;
	y -= _v.y;
	z -= _v.z;
	return *this;
}

const FVector3D& FVector3D::operator -= (float Value)
{
	x -= Value;
	y -= Value;
	z -= Value;
	return *this;
}
const FVector3D& FVector3D::operator -= (double Value)
{
	x -= (float)Value;
	y -= (float)Value;
	z -= (float)Value;
	return *this;
}
const FVector3D& FVector3D::operator -= (int Value)
{
	x -= (float)Value;
	y -= (float)Value;
	z -= (float)Value;
	return *this;
}

//--
const FVector3D& FVector3D::operator -- () //전위 
{
	x -= 1.f;
	y -= 1.f;
	z -= 1.f;
	return *this;
}

const FVector3D& FVector3D::operator -- (int) //후위
{
	
	x -= 1.f;
	y -= 1.f;
	z -= 1.f;
	return *this;
}
#pragma endregion

#pragma region Multiply
FVector3D FVector3D::operator * (const FVector3D& _v)	const
{
	FVector3D result;
	result.x = x * _v.x;
	result.y = y * _v.y;
	result.z = z * _v.z;
	return result;
}

FVector3D FVector3D::operator * (float Value) const
{
	FVector3D result;
	result.x = x * Value;
	result.y = y * Value;
	result.z = z * Value;
	return result;
}
FVector3D FVector3D::operator * (double Value) const
{
	FVector3D result;
	result.x = x * (float)Value;
	result.y = y * (float)Value;
	result.z = z * (float)Value;
	return result;
}
FVector3D FVector3D::operator * (int  Value) const
{
	FVector3D result;
	result.x = x * (float)Value;
	result.y = y * (float)Value;
	result.z = z * (float)Value;
	return result;
}

// *= 

const FVector3D& FVector3D::operator *= (const FVector3D& _v)
{
	x *= _v.x;
	y *= _v.y;
	z *= _v.z;
	return *this;
}

const FVector3D& FVector3D::operator *= (float Value)
{
	x *= Value;
	y *= Value;
	z *= Value;
	return *this;
}
const FVector3D& FVector3D::operator *= (double Value)
{
	x *= (float)Value;
	y *= (float)Value;
	z *= (float)Value;
	return *this;
}
const FVector3D& FVector3D::operator *= (int Value)
{
	x *= (float)Value;
	y *= (float)Value;
	z *= (float)Value;
	return *this;
}
#pragma endregion

#pragma region Divide
FVector3D FVector3D::operator / (const FVector3D& _v)	const
{
	FVector3D result;
	result.x = x / _v.x;
	result.y = y / _v.y;
	result.z = z / _v.z;
	return result;
}

FVector3D FVector3D::operator / (float Value) const
{
	FVector3D result;
	result.x = x / Value;
	result.y = y / Value;
	result.z = z / Value;
	return result;
}
FVector3D FVector3D::operator / (double Value) const
{
	FVector3D result;
	result.x = x / (float)Value;
	result.y = y / (float)Value;
	result.z = z / (float)Value;
	return result;
}
FVector3D FVector3D::operator / (int  Value) const
{
	FVector3D result;
	result.x = x / (float)Value;
	result.y = y / (float)Value;
	result.z = z / (float)Value;
	return result;
}

// /= 

const FVector3D& FVector3D::operator /= (const FVector3D& _v)
{
	x /= _v.x;
	y /= _v.y;
	z /= _v.z;
	return *this;
}

const FVector3D& FVector3D::operator /= (float Value)
{
	x /= Value;
	y /= Value;
	z /= Value;
	return *this;
}
const FVector3D& FVector3D::operator /= (double Value)
{
	x /= (float)Value;
	y /= (float)Value;
	z /= (float)Value;
	return *this;
}
const FVector3D& FVector3D::operator /= (int Value)
{
	x /= (float)Value;
	y /= (float)Value;
	z /= (float)Value;
	return *this;
}
#pragma endregion

#pragma region Function

//벡터의 크기를 구한다. 
float FVector3D::Length() const
{
	//피타고라스를 이용해서 벡터의 크기를 구했다
	// sqrtf : 루트값 구해주는 기능
	return sqrtf(x * x + y * y + z * z);
}

//정규화 Normalize
void FVector3D::Normalize() //해당 vector을 단위백터로 만들어준다. -> 크기가 1인 벡터로 만드는 기능을 한다. 
{
	float size = Length();
	if (0.f == size)
	{
		return;
	}

	x /= size;
	y /= size;
	z /= size;
}

FVector3D FVector3D::Normalize(const FVector3D& v)
{
	FVector3D result;
	float size = v.Length();

	if (size == 0.f)
	{
		return result;
	}

	result.x = v.x / size;
	result.y = v.y / size;
	result.z = v.z / size;
	return result;
	
}

//static FVector3D Normalize(const FVector3D& _v)	//벡터가 들어오면 단위벡터를 만들어서 내보내준다. 
//{
//	FVector3D result;
//
//	float size = _v.Length();
//
//	if (size == 0.f)
//		return result;
//
//	result.x = _v.x / size;
//	result.y = _v.y / size;
//	result.z = _v.z / size;
//	return result;
//}

float FVector3D::Dot(const FVector3D& _v) const
{
	//내적이다.
	return x * _v.x + y * _v.y + z * _v.z;
}

FVector3D FVector3D::Cross(const FVector3D& _v) const
{
	// 외적
	//직교하는 방향벡터를 구할 수 있다. 
	// 결과값에 길이는 sin값이 나온다.
	FVector3D result;
	result.x = y * _v.z - z * _v.y;
	result.y = z * _v.x - x * _v.z;
	result.z = x * _v.y - y * _v.x;
	return result;
}

//두 벡터의 거리를 구한다. 
float FVector3D::Distnace(const FVector3D& _v) const
{
	FVector3D diff = *this - _v;

	return diff.Length();
}

DirectX::XMVECTOR FVector3D::Convert() const
{
	return DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)this);
}


//TransformNormal	: 행렬을 곱할때 W값을 0으로하냐
FVector3D FVector3D::TransformNormal(FMatrix& mat) const
{
	DirectX::XMVECTOR result = DirectX::XMVector3TransformNormal(Convert(), mat.m);

	return result;
}

//TrnasformCoord	: 행렬을 곱할때 W값을 1로 하냐 
FVector3D FVector3D::TransformCoord(FMatrix& mat) const
{
	DirectX::XMVECTOR result = DirectX::XMVector3TransformCoord(Convert(), mat.m);

	return result;
}


FVector3D FVector3D::GetRotation(const FVector3D& Rot) const
{
	FMatrix matRot;
	matRot.Rotation(Rot);

	return TransformNormal(matRot);
}




#pragma endregion
