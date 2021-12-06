#include "Math.h"
#include <cmath>

double Math::RadiansToDegree(float r_angle)
{
	return r_angle * 180.f / PI;
}

double Math::RadiansToDegree(double r_angle)
{
	return r_angle * 180.f / PI;
}

bool Math::NearZero(float val, float epsilon)
{
	return fabs(val) < epsilon ? true : false;
}

float Math::Cos(const float angle)
{
	return cosf(angle);
}

float Math::Sin(const float angle)
{
	return sinf(angle);
}

// Vector2

const Vector2 Vector2::Zero(0.f, 0.f);

const float Vector2::Mag()
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

