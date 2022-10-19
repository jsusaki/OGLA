#pragma once
#include <cstdint>

struct pixel
{
	union
	{
		struct
		{
			uint8_t r;
			uint8_t g;
			uint8_t b;
			uint8_t a;
		};
	};

	pixel(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 0xFF) : r(red), g(green), b(blue), a(alpha) {}
};

template <typename T>
struct v2
{
	T x;
	T y;
};

typedef v2<int> vi2;
typedef v2<double> vd2;