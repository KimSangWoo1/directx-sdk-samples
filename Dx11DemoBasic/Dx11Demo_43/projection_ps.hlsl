////////////////////////////////////////////////////////////////////////////////
// Filename: projection_ps.hlsl
////////////////////////////////////////////////////////////////////////////////


//////////////
// TEXTURES //
//////////////
Texture2D shaderTexture : register(t0);
Texture2D projectionTexture : register(t1);


//////////////
// SAMPLERS //
//////////////
SamplerState SampleType;


//////////////////////
// CONSTANT BUFFERS //
//////////////////////
cbuffer LightBuffer
{
	float4 ambientColor;
    float4 diffuseColor;
    float3 lightDirection;
	float padding;
};


//////////////
// TYPEDEFS //
//////////////
struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
    float4 viewPosition : TEXCOORD1;
};


////////////////////////////////////////////////////////////////////////////////
// Pixel Shader
////////////////////////////////////////////////////////////////////////////////
float4 ProjectionPixelShader(PixelInputType input) : SV_TARGET
{
	float2 projectTexCoord;

	// ��� �ȼ��� �⺻ ��� ������ �ֺ� ���� ������ �����մϴ�.
	float4 color = ambientColor;

	// ����� ���� �� ������ ������ŵ�ϴ�.
	float3 lightDir = -lightDirection;

    // �� �ȼ��� ���� ���� ����մϴ�.
	float lightIntensity = saturate(dot(input.normal, lightDir));

    if(lightIntensity > 0.0f)
	{
		// Ȯ�� ����� ���� ���� �������� ���� ������ �����մϴ�.
		color += (diffuseColor * lightIntensity);
	}

	// ���� ���� ä��ϴ�.
	color = saturate(color);

	// �� �ؽ�ó ��ǥ ��ġ���� ���÷��� ����Ͽ� �ؽ�ó���� �ȼ� ������ ���ø��մϴ�.
	float4 textureColor = shaderTexture.Sample(SampleType, input.tex);

	// ���� ����� �ؽ�ó ������ �����մϴ�.
	color = color * textureColor;

	// ���� �� �ؽ�ó ��ǥ�� ����մϴ�.
	projectTexCoord.x =  input.viewPosition.x / input.viewPosition.w / 2.0f + 0.5f;
	projectTexCoord.y = -input.viewPosition.y / input.viewPosition.w / 2.0f + 0.5f;

	// ���� �� ��ǥ�� 0���� 1 ������ �ִ��� �����մϴ�. �� ����� �ȼ��� ���� �� �� ��Ʈ �ȿ� �ֽ��ϴ�.
	if((saturate(projectTexCoord.x) == projectTexCoord.x) && (saturate(projectTexCoord.y) == projectTexCoord.y))
	{
		// ���� �� �ؽ�ó ��ǥ ��ġ���� ���÷��� ����Ͽ� ���� �ؽ�ó���� ���� ���� ���ø��մϴ�.
		float4 projectionColor = projectionTexture.Sample(SampleType, projectTexCoord);

		// �� �ȼ��� ��� ������ �Ϲ� ���� ���� �����ϴ� ���� �ؽ�ó�� �����մϴ�.
		color = projectionColor;
	}

    return color;
}