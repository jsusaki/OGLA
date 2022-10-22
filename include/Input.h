#pragma once
#include <iostream>
#include <map>
#include <array>

#include <GLFW/glfw3.h>

#include "Common.h"

enum Key
{
	NONE,
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
	K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
	UP, DOWN, LEFT, RIGHT,
	SPACE, TAB, SHIFT, CTRL, INS, DEL, HOME, END, PGUP, PGDN,
	BACK, ESCAPE, RETURN, ENTER, PAUSE, SCROLL,
	NP0, NP1, NP2, NP3, NP4, NP5, NP6, NP7, NP8, NP9,
	NP_MUL, NP_DIV, NP_ADD, NP_SUB, NP_DECIMAL, PERIOD,
	EQUAL, COMMA, MINUS,
	OEM_1, OEM_2, OEM_3, OEM_4, OEM_5, OEM_6, OEM_7, OEM_8,
	CAPS_LOCK, ENUM_END
};

namespace Mouse
{
	constexpr int32_t LEFT = 0;
	constexpr int32_t RIGHT = 1;
	constexpr int32_t MIDDLE = 2;
};

struct KeyState
{
	bool released = false;
	bool pressed = false;
	bool held = false;
};

class Input
{
public:
	Input();

public:
	void HandleEvent();
	// Keyboard
	KeyState GetKey(Key k);
	uint8_t GetKeyMap(int k);
	// Mouse 
	KeyState GetMouse(int b);
	int32_t GetMouseX();
	int32_t GetMouseY();
	const vd2& GetMousePos();
	const vd2& GetMouseDelta();
	int32_t GetMouseWheel();
	// Focus
	void UpdateMouseFocus(bool state);
	void UpdateKeyFocus(bool state);

public:
	// Keyboard
	void UpdateKeyState(int32_t key, bool state);
	void UpdateKeyboard();
	// Mouse
	void UpdateMouseState(int32_t button, bool state);
	void UpdateMousePos(double x, double y);
	void UpdateMouseDelta(double dx, double dy);
	void UpdateMouseWheel(int32_t delta); // not implemented yet
	void UpdateMouse();

	// Callback Functions
	void GLFW_SetKeyboardCallback(GLFWwindow* window);
	void GLFW_SetMouseCursorCallback(GLFWwindow* window);
	void GLFW_SetMouseButtonCallback(GLFWwindow* window);
	void GLFW_SetMouseScrollCallBack(GLFWwindow* window);

	// public for now...
	bool bHasInputFocus;
	bool bHasMouseFocus;
	vd2	m_vMousePos;
	vd2	m_vMousePosCache;
	vd2	m_vMouseDelta;
	vd2 m_vMouseWindowPos;
	int32_t m_nMouseWheelDelta;
	int32_t m_nMouseWheelDeltaCache;

private:
	// Key code state map
	std::map<size_t, uint8_t> m_keys;
	// Keyboard State
	std::array<bool, 256> m_KeyNewState;
	std::array<bool, 256> m_KeyOldState;
	std::array<KeyState, 256> m_KeyboardState;
	// Mouse State
	std::array<bool, 5> m_MouseNewState;
	std::array<bool, 5> m_MouseOldState;
	std::array<KeyState, 5> m_MouseState;
};