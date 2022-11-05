#pragma once

// C-Standard Typess
#include <cstdint>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Type definitions
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed long long s64;
typedef float f32;
typedef double f64;

typedef glm::ivec2 vi2;
typedef glm::fvec2 vf2;
typedef glm::dvec2 vd2;

typedef glm::ivec3 vi3;
typedef glm::fvec3 vf3;
typedef glm::dvec3 vd3;

typedef glm::ivec4 vi4;
typedef glm::fvec4 vf4;
typedef glm::dvec4 vd4;

typedef glm::imat4x4 mi4x4;
typedef glm::fmat4x4 mf4x4;
typedef glm::dmat4x4 md4x4;

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