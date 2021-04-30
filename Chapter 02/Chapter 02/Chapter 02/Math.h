#ifndef MATH_H
#define MATH_H

namespace Math {

	constexpr double PI = 3.14159265358979323846264338327950288;

	struct Vector2 {
		float x, y;

		Vector2() { this->x = 0.f; this->y = 0.f; }
		Vector2(float x, float y) { this->x = x; this->y = y; }
	};

	double RadiansToDegree(const float r_angle);
	double RadiansToDegree(const double r_angle);
}

#endif // !MATH_H
