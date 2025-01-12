#include "stdafx.h"
#include "cameraclass.h"


CameraClass::CameraClass()
{
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(XMFLOAT3 p)
{
	m_position = p;
}


void CameraClass::SetRotation(XMFLOAT3 p)
{
	m_rotation = p;
}


XMFLOAT3 CameraClass::GetPosition()
{
	return m_position;
}


XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}


void CameraClass::Render()
{
	// 위쪽을 가리키는 벡터를 설정합니다.
	XMVECTOR upVector = XMVectorSet(0.0f, 1.0f, 0.0f, 0.f);

	// 3D월드에서 카메라의 위치를 ​​설정합니다.
	XMVECTOR positionVector = XMLoadFloat3(&m_position);

	// 기본적으로 카메라가 찾고있는 위치를 설정합니다.
	XMVECTOR lookAtVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.f);

	// yaw (Y 축), pitch (X 축) 및 roll (Z 축)의 회전값을 라디안 단위로 설정합니다.
	float pitch = m_rotation.x * 0.0174532925f;
	float yaw = m_rotation.y * 0.0174532925f;
	float roll = m_rotation.z * 0.0174532925f;

	//  yaw, pitch, roll 값을 통해 회전 행렬을 만듭니다.
	XMMATRIX rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// lookAt 및 up 벡터를 회전 행렬로 변형하여 뷰가 원점에서 올바르게 회전되도록 합니다.
	lookAtVector = XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = XMVector3TransformCoord(upVector, rotationMatrix);

	// 회전 된 카메라 위치를 뷰어 위치로 변환합니다.
	lookAtVector = XMVectorAdd(positionVector, lookAtVector);

	// 마지막으로 세 개의 업데이트 된 벡터에서 뷰 행렬을 만듭니다.
	m_viewMatrix = XMMatrixLookAtLH(positionVector, lookAtVector, upVector);
}


void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}