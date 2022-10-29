#pragma once

#include <cstdint>

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


// 32-bit Color 
struct color
{
	f32 r; f32 g; f32 b; f32 a;
};

// 8-bit Color
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

// Math
// TODO: Minimal Math Library
template <typename T>
struct v2
{
	T x;
	T y;
};
typedef v2<s32> vi2;
typedef v2<f32> vf2;
typedef v2<f64> vd2;


template <typename T>
struct v3
{
	T x;
	T y;
	T z;
};
typedef v3<s32> vi3;
typedef v3<f32> vf3;
typedef v3<f64> vd3;


template <typename T>
struct v4
{
	T x;
	T y;
	T z;
	T w;
};
typedef v4<s32> vi4;
typedef v4<f32> vf4;
typedef v4<f64> vd4;


template <typename T>
struct m4x4
{
	T m[4][4];
};
typedef m4x4<s32> mi4x4;
typedef m4x4<f32> mf4x4;
typedef m4x4<f64> md4x4;