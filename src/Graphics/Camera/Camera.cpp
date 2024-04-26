#include "Camera.h"

Camera::Camera()
{
	m_view = mf4x4(1.0f);
	m_projection = mf4x4(1.0f);

	m_near = 1.0f;
	m_far = 100.0f;
	m_FOV = 45.0f;
	m_aspect_ratio = 0.0f;
	m_orthographic_scale = 40.0f;

	m_position = { 0.0f, 0.0f, 0.0f };
	m_front = { 0.0f, 0.0f, -1.0f };
	m_up = { 0.0f, 1.0f, 0.0f };
	m_right;
	m_worldUp = { 0.0f, 1.0f, 0.0f };
	m_yaw = -90.0f;
	m_pitch = 0.0f;
	m_speed = 1.0f;
	m_sensitivity = 0.1f;
	m_mouse_prev = { 0.0f, 0.0f };

	m_mode = CameraMode::PERSPECTIVE;

	UpdateVectors();
}

Camera::Camera(vf3 position, vf3 worldup, f32 yaw, f32 pitch, f32 speed, f32 sensitivity)
{
	m_view = mf4x4(1.0f);
	m_projection = mf4x4(1.0f);

	m_near = 0.1f;
	m_far = 1000.0f;
	m_FOV = 45.0f;
	m_aspect_ratio = 0.0f;
	m_orthographic_scale = 5.0f;

	m_position = position;
	m_front = { 0.0f, 0.0f, -1.0f };
	m_up = { 0.0f, 1.0f, 0.0f };
	m_right;
	m_worldUp = worldup;
	m_yaw = yaw;
	m_pitch = pitch;
	m_speed = speed;
	m_sensitivity = sensitivity;
	m_mouse_prev = { 0.0f, 0.0f };

	m_distance = 5.0f;

	m_mode = CameraMode::PERSPECTIVE;

	UpdateVectors();
}

mf4x4 Camera::GetViewMatrix()
{	
	if (m_mode == CameraMode::ORBIT)
		m_view = glm::lookAt(m_target, m_position + m_front, m_up);
	else
		m_view = glm::lookAt(m_position, m_position + m_front, m_up);

	return m_view;
}

mf4x4 Camera::GetProjectionMatrix(f32 width, f32 height)
{
	switch (m_mode)
	{
		case CameraMode::ORBIT:		
		case CameraMode::PERSPECTIVE:
		{
			f32 aspect_ratio = width / height;
			m_projection = glm::perspective(glm::radians(m_FOV), aspect_ratio, m_near, m_far);
			break;
		}
		case CameraMode::ORTHOGRAPHIC:
		{
			f32 aspect_ratio = width / height;
			f32 distance = 0.5f * (m_far - m_near);
			m_projection = glm::ortho(-m_orthographic_scale * aspect_ratio, m_orthographic_scale * aspect_ratio, -m_orthographic_scale, m_orthographic_scale, -distance, distance);
			break;
		}
	}

	return m_projection;
}

vf3 Camera::GetPosition()
{
	return m_position;
}

vf3 Camera::GetFront()
{
	return m_front;
}

CameraMode Camera::GetMode()
{
	return m_mode;
}

void Camera::SetPerspective(f32 fov, f32 aspect, f32 near, f32 far)
{
	m_FOV = fov; m_aspect_ratio = aspect; m_near = near; m_far = far;
	m_projection = glm::perspective(glm::radians(m_FOV), m_aspect_ratio, m_near, m_far);
}

void Camera::SetOrthographic(f32 left, f32 right, f32 top, f32 bottom, f32 near, f32 far)
{
	m_near = near; m_far = far;
	m_projection = glm::ortho(left, right, top, bottom, m_near, m_far);
}

void Camera::SetMode(CameraMode mode)
{
	m_mode = mode;
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
	vf2 delta = { (mouse_pos.x - m_mouse_prev.x), (m_mouse_prev.y - mouse_pos.y) };

	// Prevent Camera Jump if delta is too large
	if (glm::length(delta) > 10.0f)
	{
		m_mouse_prev = mouse_pos;
		return;
	}
	
	m_mouse_prev = mouse_pos;

	delta *= m_sensitivity;
	m_yaw += delta.x;
	m_pitch += delta.y;

	if (m_pitch > 89.0f)  m_pitch = 89.0f;
	if (m_pitch < -89.0f) m_pitch = -89.0f;

	UpdateVectors();
}

void Camera::MouseScrollControl(f32 delta)
{
	switch (m_mode)
	{
		case CameraMode::ORBIT:
		{
			m_distance += delta;
		}
		case CameraMode::PERSPECTIVE:
		{
			m_FOV += delta;
			if (m_FOV <= 1.0f)  m_FOV = 1.0f;
			if (m_FOV >= 90.0f) m_FOV = 90.0f;
			break;
		}
		case CameraMode::ORTHOGRAPHIC:
		{
			m_orthographic_scale += delta;
			break;
		}
	}
}

void Camera::MousePanControl(vf2 mouse_pos)
{
	vf2 delta = { (mouse_pos.x - m_mouse_prev.x), (m_mouse_prev.y - mouse_pos.y) };

	if (glm::length(delta) > 10.0f)
	{
		m_mouse_prev = mouse_pos;
		return;
	}

	m_mouse_prev = mouse_pos;
	
	// horizontal movement
	if (delta.x < 0) m_position += m_right * delta.x * 0.01f; // left
	if (delta.x > 0) m_position += m_right * delta.x * 0.01f; // right
	// vertical movement
	if (delta.y > 0) m_position += m_up * delta.y * 0.01f; // up
	if (delta.y < 0) m_position += m_up * delta.y * 0.01f; // down

	UpdateVectors();
}

void Camera::MouseOrbitControl(vf2 mouse_pos)
{
	vf2 delta = { (mouse_pos.x - m_mouse_prev.x), (m_mouse_prev.y - mouse_pos.y) };
	
	if (glm::length(delta) > 10.0f)
	{
		m_mouse_prev = mouse_pos;
		return;
	}

	m_mouse_prev = mouse_pos;

	m_yaw   += delta.x * 0.1f;
	m_pitch += delta.y * 0.1f;

	if (m_pitch >  89.0f) m_pitch =  89.0f;
	if (m_pitch < -89.0f) m_pitch = -89.0f;

	// convert screen space 2d coordinate to world space 3d coordinate?
	//vf3 worldPos = glm::unProject(vf3(mouse_pos.x, mouse_pos.y, 1.0f), m_view, m_projection, vf4(0, 0, 800, 600));
	//vf3 rayMouse = glm::normalize(worldPos - m_position);
	//m_target = m_position - rayMouse;
	
	m_target   = m_position - m_front * m_distance;
	m_position = glm::normalize(m_target);
	
	UpdateVectors();
}

void Camera::UpdateVectors()
{
	m_front.x = std::cos(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
	m_front.y = std::sin(glm::radians(m_pitch));
	m_front.z = std::sin(glm::radians(m_yaw)) * std::cos(glm::radians(m_pitch));
	m_front   = glm::normalize(m_front);

	m_right   = glm::normalize(glm::cross(m_front, m_worldUp));
	m_up      = glm::normalize(glm::cross(m_right, m_front));
}