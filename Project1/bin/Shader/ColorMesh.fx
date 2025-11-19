#include "Share.fx"

cbuffer Collider : register(b2)
{
    float4 ColliderColor;
}

// 정점 정보 
// 위치 색상 
// 위치 12바이트
// 색상 16바이트 
// 이정보로 시멘틱을 만들어둔다. 

struct VS_Input_Color
{
    float3 Pos : POSITION; // POSITION 0번 레지스터 
    float4 Color : COLOR; // COLOR 0번 레지스터 
};

// 정점쉐이더의 반환값 
struct VS_Output_Color
{
    // 위치값이 float4가 되는 이유는 
    // 투영단계에서 W값도 포함 되어야 하기 때문이다. 
    
    // SV를 붙여줘야 레스터라이즈 단계에서 애가 위치값이다. 를 인식한다. 
    // 만약 SV를 안붙이고 일반 POSITION 이라고 한다면 레스터라이즈 단계에서 이게 사용할 위치값인지 아닌지 모른다. 
    float4 Pos : SV_POSITION; // SV_POSITION 0번 레지스터 
    float4 Color : COLOR; // COLOR 0번 레지스터 
};

VS_Output_Color ColorMeshVS(VS_Input_Color input)
{
    //초기화
    VS_Output_Color output = (VS_Output_Color) 0;
    
    //월드 좌표 위치 = 로컬 좌표 * 월드 행렬
    
    //화면에 출력하럭면 WVP 모두 곱한 행렬을 가져와서 곱해주면 
    output.Pos = mul(float4(input.Pos, 1.f), gmatWVP);
                                      //뒤에 1인 이유는 이동량을 포함시키기 위해서이다. 
    output.Color = input.Color;
    
    return output;
}

//중간에 레스터라이즈 단계는 알아서 해줄것이다. 

//VS_Output_Color
PS_Output_Single ColorMeshPS(VS_Output_Color input)
{
    PS_Output_Single output = (PS_Output_Single) 0;
    
    output.Color = input.Color;
    
    return output;
}

// 속성
// 진입점 main -> 시작할 정점쉐이더(ColorMeshVS)
// 쉐이더 형식 -> 효과(/fx)
// 쉐이더 모델 5.0


//FrameCeterRect 
float4 FrameMeshVS(float3 Pos : POSITION) : SV_POSITION
{
    //유연한 형변환 0으로 초기화 
    //
    float4 output = (float4) 0;
    
    // Output.Pos의 X Y Z가 들어가고 
    // W값은 1이 들어간다. 
    output = mul(float4(Pos, 1.f), gmatWVP);
    
    return output;
}

PS_Output_Single FrameMeshPS(float4 Pos : SV_POSITION)
{
    PS_Output_Single output = (PS_Output_Single) 0;
    
    output.Color = ColliderColor;
    
    return output;
}

