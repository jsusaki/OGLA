#include "Input.h"

Input::Input()
{
	// Get window and set callbacks
	m_window = glfwGetCurrentContext();
	GLFW_SetKeyboardCallback();
	GLFW_SetMouseCursorCallback();
	GLFW_SetMouseButtonCallback();
	GLFW_SetMouseScrollCallBack();

	// Key Map
	m_keys[GLFW_KEY_UNKNOWN] = Key::NONE;
	m_keys[GLFW_KEY_A] = Key::A; m_keys[GLFW_KEY_B] = Key::B; m_keys[GLFW_KEY_C] = Key::C; m_keys[GLFW_KEY_D] = Key::D; m_keys[GLFW_KEY_E] = Key::E; 
	m_keys[GLFW_KEY_F] = Key::F; m_keys[GLFW_KEY_G] = Key::G; m_keys[GLFW_KEY_H] = Key::H; m_keys[GLFW_KEY_I] = Key::I; m_keys[GLFW_KEY_J] = Key::J; 
	m_keys[GLFW_KEY_K] = Key::K; m_keys[GLFW_KEY_L] = Key::L; m_keys[GLFW_KEY_M] = Key::M; m_keys[GLFW_KEY_N] = Key::N; m_keys[GLFW_KEY_O] = Key::O; 
	m_keys[GLFW_KEY_P] = Key::P; m_keys[GLFW_KEY_Q] = Key::Q; m_keys[GLFW_KEY_R] = Key::R; m_keys[GLFW_KEY_S] = Key::S; m_keys[GLFW_KEY_T] = Key::T;
	m_keys[GLFW_KEY_U] = Key::U; m_keys[GLFW_KEY_V] = Key::V; m_keys[GLFW_KEY_W] = Key::W; m_keys[GLFW_KEY_X] = Key::X; m_keys[GLFW_KEY_Y] = Key::Y; 
	m_keys[GLFW_KEY_Z] = Key::Z;

	m_keys[GLFW_KEY_0] = Key::K0; m_keys[GLFW_KEY_1] = Key::K1; m_keys[GLFW_KEY_2] = Key::K2; m_keys[GLFW_KEY_3] = Key::K3; m_keys[GLFW_KEY_4] = Key::K4;
	m_keys[GLFW_KEY_5] = Key::K5; m_keys[GLFW_KEY_6] = Key::K6; m_keys[GLFW_KEY_7] = Key::K7; m_keys[GLFW_KEY_8] = Key::K8; m_keys[GLFW_KEY_9] = Key::K9;

	m_keys[GLFW_KEY_F1] = Key::F1; m_keys[GLFW_KEY_F2] = Key::F2; m_keys[GLFW_KEY_F3] = Key::F3; m_keys[GLFW_KEY_F4] = Key::F4; 
	m_keys[GLFW_KEY_F5] = Key::F5; m_keys[GLFW_KEY_F6] = Key::F6; m_keys[GLFW_KEY_F7] = Key::F7; m_keys[GLFW_KEY_F8] = Key::F8; 
	m_keys[GLFW_KEY_F9] = Key::F9; m_keys[GLFW_KEY_F10] = Key::F10; m_keys[GLFW_KEY_F11] = Key::F11; m_keys[GLFW_KEY_F12] = Key::F12;

	m_keys[GLFW_KEY_RIGHT] = Key::RIGHT; m_keys[GLFW_KEY_LEFT] = Key::LEFT; m_keys[GLFW_KEY_DOWN] = Key::DOWN; m_keys[GLFW_KEY_UP] = Key::UP;

	m_keys[GLFW_KEY_SPACE] = Key::SPACE; m_keys[GLFW_KEY_TAB] = Key::TAB;  m_keys[GLFW_KEY_LEFT_SHIFT] = Key::SHIFT; m_keys[GLFW_KEY_LEFT_CONTROL] = Key::CTRL; m_keys[GLFW_KEY_INSERT] = Key::INS;
	m_keys[GLFW_KEY_BACKSPACE] = Key::BACK; m_keys[GLFW_KEY_ESCAPE] = Key::ESCAPE; m_keys[GLFW_KEY_ENTER] = Key::ENTER;  m_keys[GLFW_KEY_PAUSE] = Key::PAUSE; m_keys[GLFW_KEY_SCROLL_LOCK] = Key::SCROLL;
	m_keys[GLFW_KEY_DELETE] = Key::DEL; m_keys[GLFW_KEY_HOME] = Key::HOME; m_keys[GLFW_KEY_END] = Key::END; m_keys[GLFW_KEY_PAGE_UP] = Key::PGUP; m_keys[GLFW_KEY_PAGE_DOWN] = Key::PGDN;
	m_keys[GLFW_KEY_EQUAL] = Key::EQUAL; m_keys[GLFW_KEY_COMMA] = Key::COMMA; m_keys[GLFW_KEY_MINUS] = Key::MINUS; m_keys[GLFW_KEY_KP_DECIMAL] = Key::NP_DECIMAL; m_keys[GLFW_KEY_PERIOD] = Key::PERIOD;

	m_keys[GLFW_KEY_KP_0] = Key::NP0; m_keys[GLFW_KEY_KP_1] = Key::NP1; m_keys[GLFW_KEY_KP_2] = Key::NP2; m_keys[GLFW_KEY_KP_3] = Key::NP3; m_keys[GLFW_KEY_KP_4] = Key::NP4;
	m_keys[GLFW_KEY_KP_5] = Key::NP5; m_keys[GLFW_KEY_KP_6] = Key::NP6; m_keys[GLFW_KEY_KP_7] = Key::NP7; m_keys[GLFW_KEY_KP_8] = Key::NP8; m_keys[GLFW_KEY_KP_9] = Key::NP9;
	m_keys[GLFW_KEY_KP_MULTIPLY] = Key::NP_MUL;  m_keys[GLFW_KEY_KP_DIVIDE] = Key::NP_DIV; m_keys[GLFW_KEY_KP_SUBTRACT] = Key::NP_SUB; m_keys[GLFW_KEY_KP_ADD] = Key::NP_ADD;

	m_keys[GLFW_KEY_CAPS_LOCK] = Key::CAPS_LOCK;

	m_HasInputFocus = false;
	m_HasMouseFocus = false;
	m_MousePos = { 0.0f, 0.0f };
	m_MousePosCache = { 0.0f, 0.0f };
	m_MouseDelta = { 0.0f, 0.0f };
	m_MouseWindowPos = { 0.0f, 0.0f };
	m_MouseWheelDelta = 0;
	m_MouseWheelDeltaCache = 0;

	m_KeyNewState = { 0 };
	m_KeyOldState = { 0 };
	m_KeyboardState = { 0 };
	m_MouseNewState = { 0 };
	m_MouseOldState = { 0 };
	m_MouseState = { 0 };
}

void Input::HandleEvent()
{
	glfwPollEvents();
	UpdateKeyboard();
	UpdateMouseButton();
	// cache to remain consistent between frames
	m_MousePos = m_MousePosCache;
	m_MouseWheelDelta = m_MouseWheelDeltaCache;
	m_MouseWheelDeltaCache = 0;
}

// Keyboard
KeyState Input::GetKey(Key k)
{
	return m_KeyboardState[k];
}

uint8_t Input::GetKeyMap(s32 k)
{
	return m_keys[k];
}

// Mouse 
KeyState Input::GetMouse(s32 b)
{
	return m_MouseState[b];
}

const vd2& Input::GetMousePos()
{
	return m_MousePos;
}

const vd2& Input::GetMouseDelta()
{
	return m_MouseDelta;
}

s32 Input::GetMouseWheel()
{
	return m_MouseWheelDelta;
}


// Keyboard
void Input::UpdateKeyState(s32 key, bool state)
{
	m_KeyNewState[key] = state;
}

void Input::UpdateKeyboard()
{
	for (u32 i = 0; i < 256; i++)
	{
		m_KeyboardState[i].pressed = false;
		m_KeyboardState[i].released = false;
		if (m_KeyNewState[i] != m_KeyOldState[i])
		{
			if (m_KeyNewState[i])
			{
				m_KeyboardState[i].pressed = !m_KeyboardState[i].held;
				m_KeyboardState[i].held = true;
			}
			else
			{
				m_KeyboardState[i].released = true;
				m_KeyboardState[i].held = false;
			}
		}
		m_KeyOldState[i] = m_KeyNewState[i];
	}
}

// Mouse
void Input::UpdateMouseButtonState(s32 button, bool state)
{
	m_MouseNewState[button] = state;
}

void Input::UpdateMouseWheel(s32 delta)
{
	m_MouseWheelDeltaCache += delta;
}

void Input::UpdateMousePos(f64 x, f64 y)
{
	m_HasMouseFocus = true;

	/*
	// For Window Mode Only: Clamp
	if (m_vMousePosCache.x >= 800.0f)	m_vMousePosCache.x = 800.0f - 1;
	if (m_vMousePosCache.y >= 600.0f)	m_vMousePosCache.y = 600.0f - 1;
	if (m_vMousePosCache.x < 0.0f)	    m_vMousePosCache.x = 0.0f;
	if (m_vMousePosCache.y < 0.0f)		m_vMousePosCache.y = 0.0f;
	*/

	m_MousePosCache = { x , y };
}

void Input::UpdateMouseDelta(f64 dx, f64 dy)
{
	m_MouseDelta = { dx - m_MousePosCache.x, m_MousePosCache.y - dy };
}

void Input::UpdateMouseButton()
{
	for (u32 i = 0; i < 5; i++)
	{
		m_MouseState[i].pressed = false;
		m_MouseState[i].released = false;
		if (m_MouseNewState[i] != m_MouseOldState[i])
		{
			if (m_MouseNewState[i])
			{
				m_MouseState[i].pressed = !m_MouseState[i].held;
				m_MouseState[i].held = true;
			}
			else
			{
				m_MouseState[i].released = true;
				m_MouseState[i].held = false;
			}
		}
		m_MouseOldState[i] = m_MouseNewState[i];
	}
}

void Input::UpdateMouseFocus(bool state)
{
	m_HasMouseFocus = state;
}

void Input::UpdateKeyFocus(bool state)
{
	m_HasInputFocus = state;
}


void Input::GLFW_SetKeyboardCallback()
{
	glfwSetWindowUserPointer(m_window, this);
	glfwSetKeyCallback(m_window, [](GLFWwindow* window, s32 key, s32 scancode, s32 action, s32 mode) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, false);

		Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
		switch (action)
		{
		case GLFW_PRESS:   input->UpdateKeyState(input->GetKeyMap(key), true);  break;
		case GLFW_RELEASE: input->UpdateKeyState(input->GetKeyMap(key), false); break;
		}
	});
}

void Input::GLFW_SetMouseCursorCallback()
{
	glfwSetWindowUserPointer(m_window, this);
	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, f64 dx, f64 dy) {
		Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
		input->UpdateMouseDelta(dx, dy);
		input->UpdateMousePos(dx, dy);
	});
}

void Input::GLFW_SetMouseButtonCallback()
{
	glfwSetWindowUserPointer(m_window, this);
	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, s32 button, s32 action, s32 mode) {
		Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
		switch (action)
		{
		case GLFW_PRESS: input->UpdateMouseButtonState(button, true);    break;
		case GLFW_RELEASE: input->UpdateMouseButtonState(button, false); break;
		}
	});
}

void Input::GLFW_SetMouseScrollCallBack()
{
	glfwSetWindowUserPointer(m_window, this);
	glfwSetScrollCallback(m_window, [](GLFWwindow* window, f64 dx, f64 dy) {
		Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
		for (u32 i = 0; i < std::abs(dy); i++)
		{
			if (dy > 0)
			{
				input->UpdateMouseWheel(-1);
			}
			else if (dy < 0)
			{
				input->UpdateMouseWheel(1);
			}
		}
	});
}