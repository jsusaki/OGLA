#pragma once
#include "Type.h"

enum class Direction
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum class CameraMode
{
	PERSPECTIVE,
	ORTHOGRAPHIC
};

class Camera
{
public:
	Camera();
	Camera(vf3 position = { 0.0f, 0.0f, 0.0f }, vf3 worldup = { 0.0f, 1.0f, 0.0f }, f32 yaw = -90.0f, f32 pitch = 0.0f, f32 speed = 1.0f, f32 sensitivity = 0.1f);

public:
	mf4x4 GetViewMatrix();
	mf4x4 GetProjectionMatrix(f32 width, f32 height);
	vf3 GetPosition();

	void SetPerspective(f32 fov, f32 aspect, f32 near, f32 far);
	void SetOrthographic(f32 left, f32 right, f32 top, f32 bottom, f32 near, f32 far);
	void SetCameraMode(CameraMode mode);

	void KeyControl(Direction direction, f32 fElapsedTime);
	void MouseControl(vf2 mouse_pos);
	void MouseScrollControl(f32 delta);

	void UpdateVectors();

private:
	CameraMode m_mode;

	mf4x4 m_projection;
	mf4x4 m_view;

	f32 m_FOV;
	f32 m_aspect_ratio;
	f32 m_near;
	f32 m_far;
	f32 m_orthographic_scale;

	vf3 m_position;
	vf3 m_front;
	vf3 m_up;
	vf3 m_right;
	vf3 m_worldUp;
	f32 m_yaw;
	f32 m_pitch;
	f32 m_speed;
	f32 m_sensitivity;
	vf2 m_mouse_prev;
};