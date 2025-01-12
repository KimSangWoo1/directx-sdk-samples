#include "stdafx.h"
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightclass.h"
#include "rendertextureclass.h"
#include "depthshaderclass.h"
#include "shadowshaderclass.h"
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	// Direct3D 객체 생성
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	// Direct3D 객체 초기화
	bool result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// m_Camera 객체 생성
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// 카메라 포지션을 설정한다
	m_Camera->SetPosition(XMFLOAT3(0.0f, 0.0f, -10.0f));

	// 큐브 모델 오브젝트를 생성합니다.
	m_CubeModel = new ModelClass;
	if(!m_CubeModel)
	{
		return false;
	}

	// 큐브 모델 오브젝트를 초기화 합니다.
	result = m_CubeModel->Initialize(m_Direct3D->GetDevice(), "../Dx11Demo_41/data/cube.txt", L"../Dx11Demo_41/data/wall01.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the cube model object.", L"Error", MB_OK);
		return false;
	}

	// 큐브 모델의 위치를 ​​설정 합니다.
	m_CubeModel->SetPosition(-2.0f, 2.0f, 0.0f);

	// 구형 모델 객체를 만듭니다.
	m_SphereModel = new ModelClass;
	if(!m_SphereModel)
	{
		return false;
	}

	// 구형 모델 객체를 초기화합니다.
	result = m_SphereModel->Initialize(m_Direct3D->GetDevice(), "../Dx11Demo_41/data/sphere.txt", L"../Dx11Demo_41/data/ice.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the sphere model object.", L"Error", MB_OK);
		return false;
	}

	// 구형 모델의 위치를 ​​설정합니다.
	m_SphereModel->SetPosition(2.0f, 2.0f, 0.0f);

	// 지면 모델 객체를 만듭니다.
	m_GroundModel = new ModelClass;
	if(!m_GroundModel)
	{
		return false;
	}

	// 지면 모델 객체를 초기화합니다.
	result = m_GroundModel->Initialize(m_Direct3D->GetDevice(), "../Dx11Demo_41/data/plane01.txt", L"../Dx11Demo_41/data/metal001.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the ground model object.", L"Error", MB_OK);
		return false;
	}

	// 지면 모델의 위치를 ​​설정합니다.
	m_GroundModel->SetPosition(0.0f, 1.0f, 0.0f);

	// light 객체를 만듭니다.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// 조명 객체를 초기화합니다.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetLookAt(0.0f, 0.0f, 0.0f);
	m_Light->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);

	// 렌더링을 텍스처 오브젝트에 생성한다.
	m_RenderTexture = new RenderTextureClass;
	if(!m_RenderTexture)
	{
		return false;
	}

	// 렌더링을 텍스처 오브젝트에 초기화한다.
	result = m_RenderTexture->Initialize(m_Direct3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the render to texture object.", L"Error", MB_OK);
		return false;
	}

	// 깊이 셰이더 개체를 만듭니다.
	m_DepthShader = new DepthShaderClass;
	if(!m_DepthShader)
	{
		return false;
	}

	// 깊이 셰이더 개체를 초기화합니다.
	result = m_DepthShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
		return false;
	}

	// 그림자 셰이더 개체를 만듭니다.
	m_ShadowShader = new ShadowShaderClass;
	if(!m_ShadowShader)
	{
		return false;
	}

	// 그림자 쉐이더 객체를 초기화합니다.
	result = m_ShadowShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shadow shader object.", L"Error", MB_OK);
		return false;
	}

	// 두 번째 조명 객체를 만듭니다.
	m_Light2 = new LightClass;
	if(!m_Light2)
	{
		return false;
	}

	// 두 번째 조명 객체를 초기화합니다.
	m_Light2->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light2->SetLookAt(0.0f, 0.0f, 0.0f);
	m_Light2->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR);

	// 텍스처 오브젝트에 두 번째 렌더링을 만듭니다.
	m_RenderTexture2 = new RenderTextureClass;
	if(!m_RenderTexture2)
	{
		return false;
	}

	// 텍스처 오브젝트에 두 번째 렌더를 초기화한다.
	result = m_RenderTexture2->Initialize(m_Direct3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the second render to texture object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// 두 번째 렌더를 텍스처 객체로 해제합니다.
	if(m_RenderTexture2)
	{
		m_RenderTexture2->Shutdown();
		delete m_RenderTexture2;
		m_RenderTexture2 = 0;
	}

	// 두 번째 조명 객체를 해제합니다.
	if(m_Light2)
	{
		delete m_Light2;
		m_Light2 = 0;
	}

	// 그림자 쉐이더 객체를 해제합니다.
	if(m_ShadowShader)
	{
		m_ShadowShader->Shutdown();
		delete m_ShadowShader;
		m_ShadowShader = 0;
	}

	// 깊이 셰이더 개체를 해제합니다.
	if(m_DepthShader)
	{
		m_DepthShader->Shutdown();
		delete m_DepthShader;
		m_DepthShader = 0;
	}

	// 렌더 투 텍스쳐 객체를 해제합니다.
	if(m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	// 조명 객체를 해제합니다.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// 지면 모델 객체를 해제합니다.
	if(m_GroundModel)
	{
		m_GroundModel->Shutdown();
		delete m_GroundModel;
		m_GroundModel = 0;
	}

	// 구형 모델 객체를 해제합니다.
	if(m_SphereModel)
	{
		m_SphereModel->Shutdown();
		delete m_SphereModel;
		m_SphereModel = 0;
	}

	// 큐브 모델 객체를 해제합니다.
	if(m_CubeModel)
	{
		m_CubeModel->Shutdown();
		delete m_CubeModel;
		m_CubeModel = 0;
	}

	// 카메라 객체를 해제합니다.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Direct3D 객체를 해제합니다.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
}


bool GraphicsClass::Frame(float posX, float posY, float posZ, float rotX, float rotY, float rotZ)
{
	// 카메라 위치를 설정합니다.
	m_Camera->SetPosition(XMFLOAT3(posX, posY, posZ));
	m_Camera->SetRotation(XMFLOAT3(rotX, rotY, rotZ));

	// 첫 번째 빛의 위치를 ​​설정합니다.
	m_Light->SetPosition(5.0f, 8.0f, -5.0f);

	// 두 번째 빛의 위치를 ​​설정합니다.
	m_Light2->SetPosition(-5.0f, 8.0f, -5.0f);

	// 그래픽 장면을 렌더링합니다.
	return Render();
}


bool GraphicsClass::RenderSceneToTexture()
{
	XMMATRIX worldMatrix, lightViewMatrix, lightProjectionMatrix;

	float posX = 0;
	float posY = 0;
	float posZ = 0;

	// 렌더링 대상을 렌더링에 맞게 설정합니다.
	m_RenderTexture->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// 렌더링을 텍스처에 지웁니다.
	m_RenderTexture->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// 조명의 위치에 따라 조명보기 행렬을 생성합니다.
	m_Light->GenerateViewMatrix();

	// d3d 객체에서 세계 행렬을 가져옵니다.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// 라이트 오브젝트에서 뷰 및 정사각형 매트릭스를 가져옵니다.
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetProjectionMatrix(lightProjectionMatrix);

	// 큐브 모델에 대한 변환 행렬을 설정하십시오.
	m_CubeModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	// 깊이 셰이더로 큐브 모델을 렌더링합니다.
	m_CubeModel->Render(m_Direct3D->GetDeviceContext());
	bool result = m_DepthShader->Render(m_Direct3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if(!result)
	{
		return false;
	}

	// 월드 행렬을 재설정합니다.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// 구형 모델에 대한 변환 행렬을 설정합니다.
	m_SphereModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	// 깊이 셰이더로 구형 모델을 렌더링합니다.
	m_SphereModel->Render(m_Direct3D->GetDeviceContext());
	result = m_DepthShader->Render(m_Direct3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if(!result)
	{
		return false;
	}

	// 월드 행렬을 재설정합니다.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// ground 모델에 대한 변환 행렬을 설정합니다.
	m_GroundModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	// 깊이 셰이더로 그라운드 모델을 렌더링합니다.
	m_GroundModel->Render(m_Direct3D->GetDeviceContext());
	result = m_DepthShader->Render(m_Direct3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if(!result)
	{
		return false;
	}

	// 렌더링 대상을 원래의 백 버퍼로 다시 설정하고 렌더링에 대한 렌더링을 더 이상 다시 설정하지 않습니다.
	m_Direct3D->SetBackBufferRenderTarget();

	// 뷰포트를 원본으로 다시 설정합니다.
	m_Direct3D->ResetViewport();

	return true;
}


bool GraphicsClass::RenderSceneToTexture2()
{
	XMMATRIX worldMatrix, lightViewMatrix, lightProjectionMatrix;
	float posX, posY, posZ;
	bool result;


	// 렌더링 대상을 렌더링에 맞게 설정합니다.
	m_RenderTexture2->SetRenderTarget(m_Direct3D->GetDeviceContext());

	// 렌더링을 텍스처에 지웁니다.
	m_RenderTexture2->ClearRenderTarget(m_Direct3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// 조명의 위치에 따라 조명보기 행렬을 생성합니다.
	m_Light2->GenerateViewMatrix();

	// d3d 객체에서 월드 행렬을 가져옵니다.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// 라이트 오브젝트에서 뷰 및 정사각형 매트릭스를 가져옵니다.
	m_Light2->GetViewMatrix(lightViewMatrix);
	m_Light2->GetProjectionMatrix(lightProjectionMatrix);

	// 큐브 모델에 대한 변환 행렬을 설정하십시오.
	m_CubeModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	// 깊이 셰이더로 큐브 모델을 렌더링합니다.
	m_CubeModel->Render(m_Direct3D->GetDeviceContext());
	result = m_DepthShader->Render(m_Direct3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if(!result)
	{
		return false;
	}

	// 월드 행렬을 재설정합니다.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// 구형 모델에 대한 변환 행렬을 설정합니다.
	m_SphereModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	// 깊이 셰이더로 구형 모델을 렌더링합니다.
	m_SphereModel->Render(m_Direct3D->GetDeviceContext());
	result = m_DepthShader->Render(m_Direct3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if(!result)
	{
		return false;
	}

	// 월드 행렬을 재설정합니다.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// ground 모델에 대한 변환 행렬을 설정합니다.
	m_GroundModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	// 깊이 셰이더로 그라운드 모델을 렌더링합니다.
	m_GroundModel->Render(m_Direct3D->GetDeviceContext());
	result = m_DepthShader->Render(m_Direct3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if(!result)
	{
		return false;
	}

	// 렌더링 대상을 원래의 백 버퍼로 다시 설정하고 렌더링에 대한 렌더링을 더 이상 다시 설정하지 않습니다.
	m_Direct3D->SetBackBufferRenderTarget();

	// 뷰포트를 원본으로 다시 설정합니다.
	m_Direct3D->ResetViewport();

	return true;
}


bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	XMMATRIX lightViewMatrix, lightProjectionMatrix;
	XMMATRIX lightViewMatrix2, lightProjectionMatrix2;

	float posX = 0;
	float posY = 0;
	float posZ = 0;
	
	// 먼저 장면을 텍스처로 렌더링합니다.
	bool result = RenderSceneToTexture();
	if(!result)
	{
		return false;
	}
	// 먼저 장면을 텍스처로 렌더링합니다.
	result = RenderSceneToTexture2();
	if(!result)
	{
		return false;
	}

	// 장면을 시작할 버퍼를 지운다.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// 카메라의 위치에 따라 뷰 행렬을 생성합니다.
	m_Camera->Render();

	// 조명의 위치에 따라 조명보기 행렬을 생성합니다.
	m_Light->GenerateViewMatrix();

	// 두 번째 빛에 대해서도 똑같이 설정합니다.
	m_Light2->GenerateViewMatrix();
	
	// 카메라 및 d3d 객체에서 월드, 뷰 및 투영 행렬을 가져옵니다.
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	// 라이트 오브젝트로부터 라이트의 뷰와 투영 행렬을 가져옵니다.
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetProjectionMatrix(lightProjectionMatrix);

	// 두 번째 빛에 대해서도 똑같이 설정합니다.
	m_Light2->GetViewMatrix(lightViewMatrix2);
	m_Light2->GetProjectionMatrix(lightProjectionMatrix2);
	
	// 큐브 모델에 대한 변환 행렬을 설정하십시오.
	m_CubeModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);
	
	// 큐브 모델 정점과 인덱스 버퍼를 그래픽 파이프 라인에 배치하여 그리기를 준비합니다.
	m_CubeModel->Render(m_Direct3D->GetDeviceContext());

	// 그림자 쉐이더를 사용하여 모델을 렌더링합니다.
	result = m_ShadowShader->Render(m_Direct3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, 
									lightProjectionMatrix, m_CubeModel->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetPosition(),
									m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), lightViewMatrix2, lightProjectionMatrix2, 
									m_RenderTexture2->GetShaderResourceView(), m_Light2->GetPosition(), m_Light2->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	// 월드 행렬을 재설정합니다.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// 구형 모델에 대한 변환 행렬을 설정합니다.
	m_SphereModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	// 모델 버텍스와 인덱스 버퍼를 그래픽 파이프 라인에 배치하여 드로잉을 준비합니다.
	m_SphereModel->Render(m_Direct3D->GetDeviceContext());
	result = m_ShadowShader->Render(m_Direct3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix, 
									lightProjectionMatrix, m_SphereModel->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetPosition(), 
									m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), lightViewMatrix2, lightProjectionMatrix2, 
									m_RenderTexture2->GetShaderResourceView(), m_Light2->GetPosition(), m_Light2->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	// 월드 행렬을 재설정합니다.
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// ground 모델에 대한 변환 행렬을 설정합니다.
	m_GroundModel->GetPosition(posX, posY, posZ);
	worldMatrix = XMMatrixTranslation(posX, posY, posZ);

	// 그림자 쉐이더를 사용하여 그라운드 모델을 렌더링합니다.
	m_GroundModel->Render(m_Direct3D->GetDeviceContext());
	result = m_ShadowShader->Render(m_Direct3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
									lightProjectionMatrix, m_GroundModel->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetPosition(), 
									m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), lightViewMatrix2, lightProjectionMatrix2, 
									m_RenderTexture2->GetShaderResourceView(), m_Light2->GetPosition(), m_Light2->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	// 렌더링 된 장면을 화면에 표시합니다.
	m_Direct3D->EndScene();

	return true;
}