#ifndef RANDOM_H	
#define RANDOM_H

#include <random>
#include "Math.h"

class Random
{
public:
	static void Init();

	static void Seed(unsigned int seed);

	static float GetFloat();
	static float GetFloatRange(float min, float max);

	static Vector2 GetVector(const Vector2& min, const Vector2& max);
private:
	static std::mt19937 sGenerator;
};

#endif