#pragma once
#include <cmath>
#include <limits>

class Mathf
{
public:
	static inline constexpr float PI = 3.14159265358979323846f;
	static inline constexpr float TAU = 6.28318530717958647693f;
	static inline constexpr float Deg2Rad = (float)(PI / 180.0);
	static inline constexpr float Rad2Deg = (float)(180.0 / PI);

	static inline constexpr float epsilon = std::numeric_limits<float>::epsilon();

	static inline constexpr float infinity = std::numeric_limits<float>::infinity();
	static inline constexpr float negativeInfinity = -std::numeric_limits<float>::infinity();

	static constexpr float Abs(float f) { return f < 0 ? -f : f; }
	static constexpr float Min(float a, float b) { return a < b ? a : b; }
	static constexpr float Max(float a, float b) { return a > b ? a : b; }
	static constexpr float Clamp(float f, float min, float max) { return f < min ? min : f > max ? max : f; }
	static constexpr float Clamp01(float f) { return f < 0 ? 0 : f > 1 ? 1 : f; }
	static constexpr float Lerp(float a, float b, float t) { return a + (b - a) * Clamp01(t); }
	static constexpr float LerpUnclamped(float a, float b, float t) { return a + (b - a) * t; }
	static constexpr float InverseLerp(float a, float b, float value) { return Abs(b - a) < epsilon ? 0 : Clamp01((value - a) / (b - a)); }
	static constexpr float InverseLerpUnclamped(float a, float b, float value) { return Abs(b - a) < epsilon ? 0 : (value - a) / (b - a); }

	static float Mod(float f, float modulus) { return std::fmod(f, modulus); }

	static int Floor(float f) { return static_cast<int>(std::floorf(f)); }
	static int Ceil(float f) { return std::ceilf(f); }
	static int Round(float f) { return static_cast<int>(std::roundf(f)); }
	static float Floor(float f, float increment) { return std::floorf(f / increment) * increment; }
	static float Ceil(float f, float increment) { return std::ceilf(f / increment) * increment; }
	static float Round(float f, float increment) { return std::roundf(f / increment) * increment; }
	static float Truncate(float f) { return std::truncf(f); }
	static constexpr int Sign(float f) { return f < 0 ? -1 : f > 0 ? 1 : 0; }

	static float Root(float f, float root) { return std::powf(f, 1.0f / root); }
	static float Sqrt(float f) { return std::sqrtf(f); }
	static float Cbrt(float f) { return std::cbrtf(f); }
	static float Pow(float f, float power) { return std::powf(f, power); }
	static float Exp(float f) { return std::expf(f); }
	static float Log(float f) { return std::logf(f); }
	static float Log10(float f) { return std::log10f(f); }

	static float Sin(float f) { return std::sinf(f); }
	static float Cos(float f) { return std::cosf(f); }
	static float Tan(float f) { return std::tanf(f); }
	static float Asin(float f) { return std::asinf(f); }
	static float Acos(float f) { return std::acosf(f); }
	static float Atan(float f) { return std::atanf(f); }
	static float Atan2(float y, float x) { return std::atan2f(y, x); }

	static constexpr float RadiansToDegrees(float radians) { return radians * Rad2Deg; }
	static constexpr float DegreesToRadians(float degrees) { return degrees * Deg2Rad; }

	static float Remap(float f, float inMin, float inMax, float outMin, float outMax)
	{
		if (Abs(inMax - inMin) < epsilon)
			return outMin;
		float t = (f - inMin) / (inMax - inMin);
		return outMin + t * (outMax - outMin);
	}
};