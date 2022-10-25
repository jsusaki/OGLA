#pragma once
#include <cstdint>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

struct pixel
{
	union
	{
		struct
		{
			u8 r;
			u8 g;
			u8 b;
			u8 a;
		};
	};

	pixel(u8 red, u8 green, u8 blue, u8 alpha = 0xFF) : r(red), g(green), b(blue), a(alpha) {}
};

template <typename T>
struct v2
{
	T x;
	T y;
};

typedef v2<int> vi2;
typedef v2<double> vd2;