#pragma once


/*
	공용체 union
	메모리를 공유하는 문법
*/

//union MyTestUnion
//{
//	int Number;	//4바이트
//	float fNum;	//4바이트 
//};

// 4차원 행렬을 이용할 것이다
#include "Vector4D.h"
#include "Vector3D.h"
#include "Vector2D.h"
#include "string.h"

// DX 에서는 행렬을 지원 안해주냐? 해주고있어요 다만 사용이 까다롭다. 
// __declspec(align(16)) : DX 에서 지원하는 수학 라이브러에서 행렬 연산할때 이거 없으면 크래쉬남.
// XM_ALIGNED_STRUCT(16) XMMATRIX
// __declspec(align(x)) x만큼 메모리 정렬을 지정하는키워드 입니다. 
__declspec(align(16)) union  FMatrix
{
	//DX 에서 제공하는 행렬 
	DirectX::XMMATRIX m;	// 사용하기 까다롭기 때문에 랩핑을 해줄려고 공용체Union을 사용한것이다. 

	// 이름을 안붙이는 이유 
	struct
	{
		float _11, _12, _13, _14;
		float _21, _22, _23, _24;
		float _31, _32, _33, _34;
		float _41, _42, _43, _44;
	};

	FVector4D v[4];

	//생성자
	FMatrix()
	{
		//기본이면 단위행렬로 초기화 해주자
		// XMMatrixIdentity() == 단위행렬 
		m = DirectX::XMMatrixIdentity();
	}
	FMatrix(const FMatrix& _m)
	{
		m = _m.m;
	}
	FMatrix(FMatrix&& _m) noexcept
	{
		m = _m.m;
	}
	FMatrix(const DirectX::XMMATRIX& _m)
	{
		m = _m;
	}
	FMatrix(const FVector4D _v[4])
	{
		memcpy(v, _v, sizeof(FVector4D) * 4);
	}

	//연사자 
	//대입연산자 

	const FMatrix& operator = (const FMatrix& _m)
	{
		m = _m.m;
		return *this;
	}

	const FMatrix& operator = (const DirectX::XMMATRIX& _m)
	{
		m = _m;
		return *this;
	}

	const FMatrix& operator = (const FVector4D _v[4])
	{
		memcpy(v, _v, sizeof(FVector4D) * 4);
		return *this;
	}

	//곱셈
	// DirectX::XMMATRIX 곱셈 연산을 지원해준다. 
	FMatrix operator * (const FMatrix& _m) const
	{
		return FMatrix(m * _m.m);
	}

	FMatrix operator * (const DirectX::XMMATRIX& _m) const
	{
		return FMatrix(m * _m);
	}

	//기능
	//단위행렬 만들어주는 기능
	void Identity()
	{
		m = DirectX::XMMatrixIdentity();
	}

	//전치행렬 만들어 주는기능
	void Transpose()
	{
		m = DirectX::XMMatrixTranspose(m);
	}

	//역행렬 만들어 주는 기능 
	void Inverse()
	{
		// 행렬식 먼저 구해주고 
		DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(m); // 행렬식을 구해준다. 
		//역행렬을 만들어줘야한다. 
		m = DirectX::XMMatrixInverse(&det, m);
	}


	//로컬좌표계 -> 월드좌표계 계산하는 행렬 만들어볼것이다. 
	//월드 행렬을 만들때 사용하는 것들

	//크기 행렬 
	void Scaling(const FVector3D& _v)
	{
		m = DirectX::XMMatrixScaling(_v.x, _v.y, _v.z);
	}

	void Scaling(float x, float y, float z)
	{
		m = DirectX::XMMatrixScaling(x, y, z);
	}

	void Scaling(const FVector2D& _v)
	{
		m = DirectX::XMMatrixScaling(_v.x, _v.y, 1.f);
	}

	void Scaling(float x, float y)
	{
		m = DirectX::XMMatrixScaling(x, y, 1.f);
	}


	//회전 행렬 
	// 라디안 : 호도법 180도 == PI(원주율) PI == 180도를 의미한다. 
	// 디그리 : 우리가 사용하는 각도
	// 라디안 = 각도 * PI /180
	// 디그리 = 라디안 * 180 / PI

	//우리가 사용할때는 디그리 사용할거고 
	void Rotation(const FVector3D& _v)
	{
		//행렬 만들때는 라디안을 사용한다. 
		float x = DirectX::XMConvertToRadians(_v.x);
		float y = DirectX::XMConvertToRadians(_v.y);
		float z = DirectX::XMConvertToRadians(_v.z);

		//라디안으로 변환 후 
		//x, y, z, 회전값을 이용하여 사원수를 만들어야 한다. 
		// roll : x축 회전
		// yaw : y축 회전 
		// pitch : z축 회전
		DirectX::XMVECTOR Quat = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

		// 위에서 구해준 사원수를 이용해서 회전행렬을 만들어준다. 
		m = DirectX::XMMatrixRotationQuaternion(Quat);

		//다 따로 구해서 곱하면 위와 같이 나온다. 
		//DirectX::XMMatrixRotationX();
	}

	void Rotation(float _x, float _y, float _z)
	{
		//행렬 만들때는 라디안을 사용한다. 
		float x = DirectX::XMConvertToRadians(_x);
		float y = DirectX::XMConvertToRadians(_y);
		float z = DirectX::XMConvertToRadians(_z);

		//라디안으로 변환 후 
		//x, y, z, 회전값을 이용하여 사원수를 만들어야 한다. 
		// roll : x축 회전
		// yaw : y축 회전 
		// pitch : z축 회전
		DirectX::XMVECTOR Quat = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

		// 위에서 구해준 사원수를 이용해서 회전행렬을 만들어준다. 
		m = DirectX::XMMatrixRotationQuaternion(Quat);

		//다 따로 구해서 곱하면 위와 같이 나온다. 
		//DirectX::XMMatrixRotationX();
	}

	void RotationX(float _x)
	{
		float x = DirectX::XMConvertToRadians(_x);

		m = DirectX::XMMatrixRotationX(x);
	}
	void RotationY(float _y)
	{
		float y = DirectX::XMConvertToRadians(_y);

		m = DirectX::XMMatrixRotationY(y);
	}

	void RotationZ(float _z)
	{
		float z = DirectX::XMConvertToRadians(_z);

		m = DirectX::XMMatrixRotationZ(z);
	}

	//축회전 
	void RotationAxis(const FVector3D& Axis, float Angle)
	{
		float angle = DirectX::XMConvertToRadians(Angle);
		//기준축 만들어주기 
		DirectX::XMVECTOR _Axis = DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&Axis);

		//해당 축으로 몇도 회전하는 회전행렬을 만들어 준다!
		m = DirectX::XMMatrixRotationAxis(_Axis, angle);
	}

	// 이동 행렬
	void Translation(const FVector3D& _v)
	{
		m = DirectX::XMMatrixTranslation(_v.x, _v.y, _v.z);
	}

	void Translation(float x, float y, float z)
	{
		m = DirectX::XMMatrixTranslation(x, y, z);
	}

	void Translation(const FVector2D& _v)
	{
		m = DirectX::XMMatrixTranslation(_v.x, _v.y, 0);
	}

	void Translation(float x, float y)
	{
		m = DirectX::XMMatrixTranslation(x, y, 0);
	}

	//static
	//항등행렬 
	static FMatrix StaticIdentity()
	{
		return DirectX::XMMatrixIdentity();
	}

	// 전치
	static FMatrix StaticTranspose(const FMatrix& _m)
	{
		return DirectX::XMMatrixTranspose(_m.m);
	}

	//역
	static FMatrix StaticInverse(const FMatrix& _m)
	{
		DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(_m.m);
		return DirectX::XMMatrixInverse(&det, _m.m);
	}

	//////// 실습 
	// 월드 행렬 구하는 함수들 Static 으로 만들어보기 
		//크기 행렬 


	static FMatrix StaticScaling(const FVector3D& _v)
	{
		return DirectX::XMMatrixScaling(_v.x, _v.y, _v.z);
	}

	static FMatrix StaticScaling(float x, float y, float z)
	{
		return DirectX::XMMatrixScaling(x, y, z);
	}

	static FMatrix StaticScaling(const FVector2D& _v)
	{
		return DirectX::XMMatrixScaling(_v.x, _v.y, 1.f);
	}

	static FMatrix StaticScaling(float x, float y)
	{
		return DirectX::XMMatrixScaling(x, y, 1.f);
	}

	//우리가 사용할때는 디그리 사용할거고 
	static FMatrix StaticRotation(const FVector3D& _v)
	{
		//행렬 만들때는 라디안을 사용한다. 
		float x = DirectX::XMConvertToRadians(_v.x);
		float y = DirectX::XMConvertToRadians(_v.y);
		float z = DirectX::XMConvertToRadians(_v.z);

		//라디안으로 변환 후 
		//x, y, z, 회전값을 이용하여 사원수를 만들어야 한다. 
		// roll : x축 회전
		// yaw : y축 회전 
		// pitch : z축 회전
		DirectX::XMVECTOR Quat = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

		// 위에서 구해준 사원수를 이용해서 회전행렬을 만들어준다. 
		return DirectX::XMMatrixRotationQuaternion(Quat);
	}

	static FMatrix StaticRotation(float _x, float _y, float _z)
	{
		//행렬 만들때는 라디안을 사용한다. 
		float x = DirectX::XMConvertToRadians(_x);
		float y = DirectX::XMConvertToRadians(_y);
		float z = DirectX::XMConvertToRadians(_z);

		//라디안으로 변환 후 
		//x, y, z, 회전값을 이용하여 사원수를 만들어야 한다. 
		// roll : x축 회전
		// yaw : y축 회전 
		// pitch : z축 회전
		DirectX::XMVECTOR Quat = DirectX::XMQuaternionRotationRollPitchYaw(x, y, z);

		// 위에서 구해준 사원수를 이용해서 회전행렬을 만들어준다. 
		return DirectX::XMMatrixRotationQuaternion(Quat);
	}

	static FMatrix StaticRotationX(float _x)
	{
		float x = DirectX::XMConvertToRadians(_x);

		return DirectX::XMMatrixRotationX(x);
	}
	static FMatrix StaticRotationY(float _y)
	{
		float y = DirectX::XMConvertToRadians(_y);

		return DirectX::XMMatrixRotationY(y);
	}

	static FMatrix StaticRotationZ(float _z)
	{
		float z = DirectX::XMConvertToRadians(_z);

		return DirectX::XMMatrixRotationZ(z);
	}

	//축회전 
	static FMatrix StaticRotationAxis(const FVector3D& Axis, float Angle)
	{
		float angle = DirectX::XMConvertToRadians(Angle);
		//기준축 만들어주기 
		DirectX::XMVECTOR _Axis = DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)&Axis);

		//해당 축으로 몇도 회전하는 회전행렬을 만들어 준다!
		return DirectX::XMMatrixRotationAxis(_Axis, angle);
	}

	// 이동 행렬
	static FMatrix StaticTranslation(const FVector3D& _v)
	{
		return DirectX::XMMatrixTranslation(_v.x, _v.y, _v.z);
	}

	static FMatrix StaticTranslation(float x, float y, float z)
	{
		return DirectX::XMMatrixTranslation(x, y, z);
	}

	static FMatrix StaticTranslation(const FVector2D& _v)
	{
		return DirectX::XMMatrixTranslation(_v.x, _v.y, 0);
	}

	static FMatrix StaticTranslation(float x, float y)
	{
		return DirectX::XMMatrixTranslation(x, y, 0);
	}
};




/*

단위 행렬
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1

월드 좌표계
로컬 좌표계 : 모델 ,메쉬 모양 정해진 좌표계
-> 월드(게임세상)에 배치하기위 사용하는 좌표계

월드행렬의 구성 요소
월드 행렬 =  크기 * 자전(자기자신 회전) * 위치(이동) * 공전 * 부모
			크 자 이 공 부


//크기 행렬
x 0 0 0
0 y 0 0
0 0 z 0
0 0 0 1

(1, 1, 0, 1) *	100	0	0	0 = (100, 100, 0, 1)
				0	100	0	0
				0	0	100	0
				0	0	0	1

(1, 2, 0, 1) *	100	0	0	0 = (100, 200, 0, 1)
				0	100	0	0
				0	0	100	0
				0	0	0	1


// 회전 행렬
// 오일러 회전
cos -sin
sin cos

x축 회전
1	0	0	  0
0	cos	-sin  0
0	sin	cos	  0
0	0	0	  1

Y축 회전
cos	 0  sin 0
0	 1	0	0
-sin 0  cos 0
0	 0	0	1

Z축 회전
cos -sin 0  0
sin cos	 0  0
0	0	 1  0
0	0	 0  1

최종 회전행렬 = x축회전행렬 * Y축회전행렬 * Z축 회전행렬
왜 삼각함수 덧샘을이용하나요 -> 회전만하고 이동량에는 영향을 안주기 대문에 사용한다.


//이동행렬
1 0 0 0
0 1 0 0
0 0 1 0
x y z 1

(1, 1, 0, 1) *	1	0	0	0 = 201, 201, 0 1
				0	1	0	0
				0	0	1	0
				200	200	0	1

*/