#include "Camera.h"

Camera::Camera()
{
	m_view = mf4x4(1.0f);
	m_projection = mf4x4(1.0f);

	m_position = { 0.0f, 0.0f, 0.0f };
	m_front = { 0.0f, 0.0f, -1.0f };
	m_up = { 0.0f, 1.0f, 0.0f };
	m_right;
	m_worldUp = { 0.0f, 1.0f, 0.0f };

	m_near = 1.0f;
	m_far = 100.0f;
	m_FOV = 45.0f;
	m_aspect = 0.0f;

	m_yaw = -90.0f;
	m_pitch = 0.0f;

	m_speed = 1.0f;
	m_sensitivity = 0.1f;

	m_firstMouse = true;
	m_mouse_prev = { 0.0f, 0.0f };

	UpdateVectors();
}

Camera::Camera(vf3 position, vf3 worldup, f32 yaw, f32 pitch, f32 speed, f32 sensitivity)
{
	m_view = mf4x4(1.0f);
	m_projection = mf4x4(1.0f);

	m_position = position;
	m_front = { 0.0f, 0.0f, -1.0f };
	m_up = { 0.0f, 1.0f, 0.0f };
	m_right;
	m_worldUp = worldup;

	m_near = 1.0f;
	m_far = 100.0f;
	m_FOV = 45.0f;
	m_aspect = 0.0f;

	m_yaw = yaw;
	m_pitch = pitch;

	m_speed = speed;
	m_sensitivity = sensitivity;

	m_firstMouse = true;
	m_mouse_prev = { 0.0f, 0.0f };

	UpdateVectors();
}

mf4x4 Camera::GetViewMatrix()
{
	m_view = glm::lookAt(m_position, m_position + m_front, m_up);
	return m_view;
}

mf4x4 Camera::GetProjectionMatrix(f32 aspect)
{
	m_projection = glm::perspective(glm::radians(m_FOV), aspect, m_near, m_far);
	return m_projection;
}

vf3 Camera::GetPosition()
{
	return m_position;
}

void Camera::SetPerspective(f32 fov, f32 aspect, f32 near, f32 far)
{
	m_FOV = fov; m_aspect = aspect; m_near = near; m_far = far;
	m_projection = glm::perspective(glm::radians(m_FOV), m_aspect, m_near, m_far);
}

void Camera::SetOrthographic(f32 left, f32 right, f32 top, f32 bottom, f32 near, f32 far)
{
	m_near = near; m_far = far;
	m_projection = glm::ortho(left, right, top, bottom, m_near, m_far);
}

void Camera::KeyControl(Direction direction, f32 fElapsedTime) 
{
	f32 velocity = m_speed * fElapsedTime;

	switch (direction) 
	{
	case Direction::FORWARD:  m_position += m_front * velocity; break;
	case Direction::BACKWARD: m_position -= m_front * velocity; break;
	case Direction::LEFT:     m_position -= m_right * velocity; break;
	case Direction::RIGHT:    m_position += m_right * velocity; break;
	case Direction::UP:       m_position += m_worldUp * velocity; break;
	case Direction::DOWN:     m_position -= m_worldUp * velocity; break;
	}
}

void Camera::MouseControl(vf2 mouse_pos)
{
	if (m_firstMouse) {
		m_mouse_prev = mouse_pos;
		m_firstMouse = false;
	}

	vf2 delta = { (mouse_pos.x - m_mouse_prev.x) * m_sensitivity, (m_mouse_prev.y - mouse_pos.y) * m_sensitivity };

	m_mouse_prev = mouse_pos;

	m_yaw += delta.x;
	m_pitch += delta.y;

	if (m_yaw == 0.0f) m_yaw = 0.01f;
	if (m_pitch == 0.0f) m_pitch = 0.01f;

	if (m_pitch > 89.0f)  m_pitch = 89.0f;
	if (m_pitch < -89.0f) m_pitch = -89.0f;

	UpdateVectors();
}

void Camera::UpdateVectors()
{
	m_front.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
	m_front.y = std::sin(glm::radians(m_pitch));
	m_front.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
	m_front = glm::normalize(m_front);

	m_right = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up = glm::normalize(glm::cross(m_right, m_front));
}