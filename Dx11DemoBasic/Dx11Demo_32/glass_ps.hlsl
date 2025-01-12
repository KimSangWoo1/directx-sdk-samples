////////////////////////////////////////////////////////////////////////////////
// Filename: glass_ps.hlsl
////////////////////////////////////////////////////////////////////////////////


/////////////
// GLOBALS //
/////////////
SamplerState SampleType;
Texture2D colorTexture : register(t0);
Texture2D normalTexture : register(t1);
Texture2D refractionTexture : register(t2);

cbuffer GlassBuffer
{
    float refractionScale;
    float3 padding;
};


//////////////
// TYPEDEFS //
//////////////
struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
    float4 refractionPosition : TEXCOORD1;
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 GlassPixelShader(PixelInputType input) : SV_TARGET
{
	float2 refractTexCoord;
	float4 normalMap;
	float3 normal;
	float4 refractionColor;
	float4 textureColor;
	float4 color;

	
	// 투영 된 굴절 텍스처 좌표를 계산합니다.
	refractTexCoord.x = input.refractionPosition.x / input.refractionPosition.w / 2.0f + 0.5f;
	refractTexCoord.y = -input.refractionPosition.y / input.refractionPosition.w / 2.0f + 0.5f;

	// 노멀 맵 텍스처로부터 법선을 샘플링합니다.
	normalMap = normalTexture.Sample(SampleType, input.tex);

	// 법선의 범위를 (0,1)에서 (-1, + 1)로 확장합니다.
	normal = (normalMap.xyz * 2.0f) - 1.0f;

	// 유리를 통해 가벼운 왜곡을 시뮬레이트하기 위해 텍스처 좌표 샘플링 위치를 법선 맵 값으로 다시 배치합니다.
	refractTexCoord = refractTexCoord + (normal.xy * refractionScale);

	// 교란 된 텍스처 좌표를 사용하여 굴절 텍스처에서 텍스처 픽셀을 샘플링합니다.
	refractionColor = refractionTexture.Sample(SampleType, refractTexCoord);

	// 유리색 텍스처에서 텍스처 픽셀을 샘플링합니다.
	textureColor = colorTexture.Sample(SampleType, input.tex);

	// 최종 색상의 유리 색상과 굴절 값을 균등하게 결합합니다.
    color = lerp(refractionColor, textureColor, 0.5f);

    return color;
}
