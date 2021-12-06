#ifndef MATH_H
#define MATH_H

namespace Math {

	constexpr double PI = 3.14159265358979323846264338327950288;

	double RadiansToDegree(const float r_angle);
	double RadiansToDegree(const double r_angle);

	bool NearZero(float val, float epsilon = 0.001f);

	float Cos(const float angle);
	float Sin(const float angle);
}

class Vector2 {
public:
	float x, y;

	Vector2()
		: x(0.f),
		  y(0.f)
	{}

	Vector2(float x, float y)
		: x(x),
		  y(y)
	{}

	friend Vector2 operator+(const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x + right.x, left.y + right.y);
	}

	friend Vector2 operator-(const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x - right.x, left.y - right.y);
	}

	friend Vector2 operator*(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	friend Vector2 operator*(const Vector2& left, const Vector2& right)
	{
		return Vector2(left.x * right.x, left.y * right.y);
	}

	Vector2& operator+=(float scalar)
	{
		x += scalar;
		y += scalar;
		return *this;
	}

	Vector2& operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	const float Mag();

	static const Vector2 Zero;
};

#endif // !MATH_H
