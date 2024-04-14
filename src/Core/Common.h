#pragma once

// C-Standard Types
#include <cstdint>
// Numeric types
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;
using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;
using f32 = float;
using f64 = double;

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// Vector types
using vi2 = glm::ivec2;
using vf2 = glm::fvec2;
using vd2 = glm::dvec2;
using vi3 = glm::ivec3;
using vf3 = glm::fvec3;
using vd3 = glm::dvec3;
using vi4 = glm::ivec4;
using vf4 = glm::fvec4;
using vd4 = glm::dvec4;
// Matrix types
using mi4x4 = glm::imat4x4;
using mf4x4 = glm::fmat4x4;
using md4x4 = glm::dmat4x4;

// float 32-bit Color 
struct color
{
	f32 r; f32 g; f32 b; f32 a;
};

// uint 32-bit Color 
struct pixel
{
	union
	{
		u32 p;
		struct { u8 r; u8 g; u8 b; u8 a; };
	};
	pixel(u8 red, u8 green, u8 blue, u8 alpha = 0xFF) : r(red), g(green), b(blue), a(alpha) {}
};