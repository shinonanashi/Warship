#pragma once

#include <iostream>
#include <math.h>

struct Vector2f
{
	Vector2f()
		:x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y)
		:x(p_x), y(p_y)
	{}

	void Print()
	{
		std::cout << "(" << x << ", " << y << ")" << std::endl;
	}

	float x, y;
};

class Mathf
{
public:
	Mathf();

	static int Random(int min, int max) {

		return (rand() % (max - min + 1)) + min;
	}

	static float Lerp(float a, float b, float t) {
		return (1.0 - t) * a + b * t;
	}

	static Vector2f Normalize(Vector2f vec)
	{
		float magnitude = sqrt(vec.x * vec.x + vec.y * vec.y);

		if (magnitude != 0)
		{
			vec.x /= magnitude;
			vec.y /= magnitude;
		}
		return vec;
	}

};
