#pragma once

#include <iostream>
#include <map>
#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Type.h"

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
	constexpr s32 LEFT = 0;
	constexpr s32 RIGHT = 1;
	constexpr s32 MIDDLE = 2;
}

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
	u8 GetKeyMap(s32 k);
	// Mouse 
	KeyState GetMouse(s32 b);
	s32 GetMouseX();
	s32 GetMouseY();
	const vd2& GetMousePos();
	const vd2& GetMouseDelta();
	s32 GetMouseWheel();
	// Focus
	void UpdateMouseFocus(bool state);
	void UpdateKeyFocus(bool state);

public:
	// Keyboard
	void UpdateKeyState(s32 key, bool state);
	void UpdateKeyboard();
	// Mouse
	void UpdateMouseButtonState(s32 button, bool state);
	void UpdateMousePos(f64 x, f64 y);
	void UpdateMouseDelta(f64 dx, f64 dy);
	void UpdateMouseWheel(s32 delta);
	void UpdateMouseButton();

private:
	// Key code state map
	std::map<size_t, u8> m_keys;
	// Keyboard State
	std::array<bool, 256> m_KeyNewState;
	std::array<bool, 256> m_KeyOldState;
	std::array<KeyState, 256> m_KeyboardState;
	// Mouse State
	std::array<bool, 5> m_MouseNewState;
	std::array<bool, 5> m_MouseOldState;
	std::array<KeyState, 5> m_MouseState;

	bool bHasInputFocus;
	bool bHasMouseFocus;
	vd2	m_vMousePos;
	vd2	m_vMousePosCache;
	vd2	m_vMouseDelta;
	vd2 m_vMouseWindowPos;
	s32 m_nMouseWheelDelta;
	s32 m_nMouseWheelDeltaCache;
};