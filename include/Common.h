#pragma once
#include <cstdint>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;

// Color 
struct color
{
	float r; 
	float g;
	float b;
	float a;
};

struct pixel
{
	union
	{
		struct
		{
			u8 r; u8 g; u8 b; u8 a;
		};
	};
	pixel(u8 red, u8 green, u8 blue, u8 alpha = 0xFF) : r(red), g(green), b(blue), a(alpha) {}
};

// TODO: Math library
template <typename T>
struct v2
{
	T x;
	T y;
};
typedef v2<int> vi2;
typedef v2<float> vf2;
typedef v2<double> vd2;


template <typename T>
struct v3
{
	T x;
	T y;
	T z;
};
typedef v3<int> vi3;
typedef v3<float> vf3;
typedef v3<double> vd3;


template <typename T>
struct v4
{
	T x;
	T y;
	T z;
	T w;
};
typedef v4<int> vi4;
typedef v4<float> vf4;
typedef v4<double> vd4;
