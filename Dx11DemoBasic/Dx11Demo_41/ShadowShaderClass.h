#pragma once

class ShadowShaderClass
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
		XMMATRIX lightView;
		XMMATRIX lightProjection;
		XMMATRIX lightView2;
		XMMATRIX lightProjection2;
	};

	struct LightBufferType
	{
		XMFLOAT4 ambientColor;
		XMFLOAT4 diffuseColor;
		XMFLOAT4 diffuseColor2;
	};

	struct LightBufferType2
	{
		XMFLOAT3 lightPosition;
		float padding1;
		XMFLOAT3 lightPosition2;
		float padding2;
	};
public:
	ShadowShaderClass();
	ShadowShaderClass(const ShadowShaderClass&);
	~ShadowShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*,
				ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4, XMFLOAT4, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT3,
				XMFLOAT4);

private:
	bool InitializeShader(ID3D11Device*, HWND, const WCHAR*, const WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, const WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*,
				ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4, XMFLOAT4, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*,
				XMFLOAT3, XMFLOAT4);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11InputLayout* m_layout = nullptr;
	ID3D11SamplerState* m_sampleStateWrap = nullptr;
	ID3D11SamplerState* m_sampleStateClamp = nullptr;
	ID3D11Buffer* m_matrixBuffer = nullptr;
	ID3D11Buffer* m_lightBuffer = nullptr;
	ID3D11Buffer* m_lightBuffer2 = nullptr;
};