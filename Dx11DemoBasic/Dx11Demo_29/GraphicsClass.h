#pragma once

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


class D3DClass;
class CameraClass;
class ModelClass;
class LightClass;
class RenderTextureClass;
class LightShaderClass;
class RefractionShaderClass;
class WaterShaderClass;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	bool Render();

private:
	bool RenderRefractionToTexture();
	bool RenderReflectionToTexture();
	bool RenderScene();

private:
	D3DClass* m_Direct3D = nullptr;
	CameraClass* m_Camera = nullptr;
	ModelClass* m_GroundModel = nullptr;
	ModelClass* m_WallModel = nullptr;
	ModelClass* m_BathModel = nullptr;
	ModelClass* m_WaterModel = nullptr;
	LightClass* m_Light = nullptr;
	RenderTextureClass* m_RefractionTexture = nullptr;
	RenderTextureClass* m_ReflectionTexture = nullptr;
	LightShaderClass* m_LightShader = nullptr;
	RefractionShaderClass* m_RefractionShader = nullptr;
	WaterShaderClass* m_WaterShader = nullptr;
	float m_waterHeight = 0;
	float m_waterTranslation = 0;
};