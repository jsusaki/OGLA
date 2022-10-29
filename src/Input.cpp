#include "Input.h"

Input::Input()
{
	// Map Keys
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

	bHasInputFocus = false;
	bHasMouseFocus = false;
	m_vMousePos = { 0.0f, 0.0f };
	m_vMousePosCache = { 0.0f, 0.0f };
	m_vMouseDelta = { 0.0f, 0.0f };
	m_vMouseWindowPos = { 0.0f, 0.0f };
	m_nMouseWheelDelta = 0;
	m_nMouseWheelDeltaCache = 0;

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
	UpdateMouse();
	// store to remain consistent between frames
	m_vMousePos = m_vMousePosCache;
	m_nMouseWheelDelta = m_nMouseWheelDeltaCache;
	m_nMouseWheelDeltaCache = 0;
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

s32 Input::GetMouseX()
{
	return m_vMousePos.x;
}

s32 Input::GetMouseY()
{
	return m_vMousePos.y;
}

const vd2& Input::GetMousePos()
{
	return m_vMousePos;
}

const vd2& Input::GetMouseDelta()
{
	return m_vMouseDelta;
}

s32 Input::GetMouseWheel()
{
	return m_nMouseWheelDelta;
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
void Input::UpdateMouseState(s32 button, bool state)
{
	m_MouseNewState[button] = state;
}

void Input::UpdateMouseWheel(s32 delta)
{
	m_nMouseWheelDeltaCache += delta;
}

void Input::UpdateMousePos(f64 x, f64 y)
{
	m_vMousePosCache = { x, y };
}

void Input::UpdateMouseDelta(f64 dx, f64 dy)
{
	m_vMouseDelta = { dx - m_vMousePosCache.x, m_vMousePosCache.y - dy };
}


void Input::UpdateMouse()
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
	bHasMouseFocus = state;
}

void Input::UpdateKeyFocus(bool state)
{
	bHasInputFocus = state;
}

// Callback Functions
void Input::GLFW_SetKeyboardCallback(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetKeyCallback(window, [](GLFWwindow* window, s32 key, s32 scancode, s32 action, s32 mode)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, false);

		Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
		switch (action)
		{
			case GLFW_PRESS:
			{
				input->UpdateKeyState(input->GetKeyMap(key), true);
				break;
			}
			case GLFW_RELEASE:
			{
				input->UpdateKeyState(input->GetKeyMap(key), false);
				break;
			}
		}
	});
}

void Input::GLFW_SetMouseCursorCallback(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, f64 dx, f64 dy)
	{
		Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
		input->UpdateMouseDelta(dx, dy);
		input->UpdateMousePos(dx, dy);
	});
}

void Input::GLFW_SetMouseButtonCallback(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, s32 button, s32 action, s32 mode)
	{
		Input* input = static_cast<Input*>(glfwGetWindowUserPointer(window));
		switch (action)
		{
			case GLFW_PRESS:
			{
				input->UpdateMouseState(button, true);
				break;
			}
			case GLFW_RELEASE:
			{
				input->UpdateMouseState(button, false);
				break;
			}
		}
	});
}

void Input::GLFW_SetMouseScrollCallBack(GLFWwindow* window)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetScrollCallback(window, [](GLFWwindow* window, f64 dx, f64 dy)
	{
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