#include "stdafx.h"
#include "PositionClass.h"


PositionClass::PositionClass()
{
}


PositionClass::PositionClass(const PositionClass& other)
{
}


PositionClass::~PositionClass()
{
}


void PositionClass::SetPosition(float x, float y, float z)
{
	m_position = XMFLOAT3(x, y, z);
}


void PositionClass::SetRotation(float x, float y, float z)
{
	m_rotation = XMFLOAT3(x, y, z);
}


void PositionClass::GetPosition(XMFLOAT3& p)
{
	p = m_position;
}


void PositionClass::GetRotation(XMFLOAT3& p)
{
	p = m_rotation;
}


void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
}


void PositionClass::MoveForward(bool keydown)
{
	// Ű�� ������ ī�޶� �������� ���ƴ� �ӵ��� �����մϴ�. ȸ�� �ӵ��� ������ ������.
	if (keydown)
	{
		m_forwardSpeed += m_frameTime * 0.001f;

		if(m_forwardSpeed > (m_frameTime * 0.03f))
		{
			m_forwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_forwardSpeed -= m_frameTime * 0.0007f;

		if(m_forwardSpeed < 0.0f)
		{
			m_forwardSpeed = 0.0f;
		}
	}

	// ���� �������� ��ȯ�Ͻʽÿ�.
	float radians = m_rotation.y * 0.0174532925f;

	// ��ġ�� ������Ʈ �մϴ�.
	m_position.x += sinf(radians) * m_forwardSpeed;
	m_position.z += cosf(radians) * m_forwardSpeed;
}


void PositionClass::MoveBackward(bool keydown)
{
	// Ű�� ������ ī�޶� ���������� ȸ���ϴ� �ӵ��� �����մϴ�. ȸ�� �ӵ��� ������ ������.
	if (keydown)
	{
		m_backwardSpeed += m_frameTime * 0.001f;

		if(m_backwardSpeed > (m_frameTime * 0.03f))
		{
			m_backwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_backwardSpeed -= m_frameTime * 0.0007f;
		
		if(m_backwardSpeed < 0.0f)
		{
			m_backwardSpeed = 0.0f;
		}
	}

	// ���� �������� ��ȯ�Ͻʽÿ�.
	float radians = m_rotation.y * 0.0174532925f;

	// ��ġ�� ������Ʈ �մϴ�.
	m_position.x -= sinf(radians) * m_backwardSpeed;
	m_position.z -= cosf(radians) * m_backwardSpeed;
}


void PositionClass::MoveUpward(bool keydown)
{
	// ����ڰ� Ű�� ������ �ִ� ������ �ð��� ���� ���� �̵� �ӵ��� �����մϴ�.
	if(keydown)
	{
		m_upwardSpeed += m_frameTime * 0.003f;

		if(m_upwardSpeed > (m_frameTime * 0.03f))
		{
			m_upwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_upwardSpeed -= m_frameTime * 0.002f;

		if(m_upwardSpeed < 0.0f)
		{
			m_upwardSpeed = 0.0f;
		}
	}

	// ���� ��ġ�� ������Ʈ �մϴ�.
	m_position.y += m_upwardSpeed;
}


void PositionClass::MoveDownward(bool keydown)
{
	// ����ڰ� Ű�� ������ �ִ� ������ �ð��� ���� ���� �̵� �ӵ��� �����մϴ�.
	if(keydown)
	{
		m_downwardSpeed += m_frameTime * 0.003f;

		if(m_downwardSpeed > (m_frameTime * 0.03f))
		{
			m_downwardSpeed = m_frameTime * 0.03f;
		}
	}
	else
	{
		m_downwardSpeed -= m_frameTime * 0.002f;

		if(m_downwardSpeed < 0.0f)
		{
			m_downwardSpeed = 0.0f;
		}
	}

	// ���� ��ġ�� ������Ʈ �մϴ�.
	m_position.y -= m_downwardSpeed;
}


void PositionClass::TurnLeft(bool keydown)
{
	// ����ڰ� Ű�� ������ �ִ� ������ �ð��� ���� ���� ȸ�� �ӵ��� �����մϴ�.
	if(keydown)
	{
		m_leftTurnSpeed += m_frameTime * 0.01f;

		if(m_leftTurnSpeed > (m_frameTime * 0.15f))
		{
			m_leftTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime* 0.005f;

		if(m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	// ȸ���� ������Ʈ �մϴ�.
	m_rotation.y -= m_leftTurnSpeed;

	// ȸ������ ������ 0 ~360 ���� �����մϴ�.
	if(m_rotation.y < 0.0f)
	{
		m_rotation.y += 360.0f;
	}
}


void PositionClass::TurnRight(bool keydown)
{
	// ����ڰ� Ű�� ������ �ִ� ������ �ð��� ���� ������ ȸ�� �ӵ��� �����մϴ�.
	if(keydown)
	{
		m_rightTurnSpeed += m_frameTime * 0.01f;

		if(m_rightTurnSpeed > (m_frameTime * 0.15f))
		{
			m_rightTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime* 0.005f;

		if(m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	// ȸ���� ������Ʈ �մϴ�.
	m_rotation.y += m_rightTurnSpeed;

	// ȸ������ ������ 0 ~360 ���� �����մϴ�.
	if(m_rotation.y > 360.0f)
	{
		m_rotation.y -= 360.0f;
	}
}


void PositionClass::LookUpward(bool keydown)
{
	// ����ڰ� Ű�� ������ �ִ� ������ �ð��� ���� ���� ȸ�� �ӵ��� �����մϴ�.
	if(keydown)
	{
		m_lookUpSpeed += m_frameTime * 0.01f;

		if(m_lookUpSpeed > (m_frameTime * 0.15f))
		{
			m_lookUpSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_lookUpSpeed -= m_frameTime* 0.005f;

		if(m_lookUpSpeed < 0.0f)
		{
			m_lookUpSpeed = 0.0f;
		}
	}

	// ȸ���� ������Ʈ �մϴ�.
	m_rotation.x -= m_lookUpSpeed;

	// ȸ���� �ִ� 90 ���� ���� �մϴ�.
	if(m_rotation.x > 90.0f)
	{
		m_rotation.x = 90.0f;
	}
}


void PositionClass::LookDownward(bool keydown)
{
	// ����ڰ� Ű�� ������ �ִ� ������ �ð��� ���� �Ʒ��� ȸ�� �ӵ��� �����մϴ�.
	if(keydown)
	{
		m_lookDownSpeed += m_frameTime * 0.01f;

		if(m_lookDownSpeed > (m_frameTime * 0.15f))
		{
			m_lookDownSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_lookDownSpeed -= m_frameTime* 0.005f;

		if(m_lookDownSpeed < 0.0f)
		{
			m_lookDownSpeed = 0.0f;
		}
	}

	// ȸ���� ������Ʈ �մϴ�.
	m_rotation.x += m_lookDownSpeed;

	//ȸ���� �ִ� 90 ���� ���� �մϴ�.
	if(m_rotation.x < -90.0f)
	{
		m_rotation.x = -90.0f;
	}
}