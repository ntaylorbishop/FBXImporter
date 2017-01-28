#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "Engine/General/Core/EngineCommon.hpp"
#include "Engine/Math/IntVector2.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/IntVector3.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/AABB2.hpp"
#include "Engine/Math/Matrix4.hpp"

extern const float pi;

void InitializeRandomSeedForRand();

bool DoDiscsOverlap(const Vector2& center1, float r1, const Vector2& center2, float r2);
bool IsPointInDisk(const Vector2& point, const Vector2& center, float radius);
bool IsPointInSquare(const IntVector2& point, const AABB2Int& square);

float DistanceBetweenPoints(const IntVector2& v1, const IntVector2& v2);
float DistanceBetweenPoints(const Vector2& v1, const Vector2& v2);
float DistanceBetweenPoints(const IntVector3& v1, const IntVector3& v2);
float DistanceBetweenPoints(const Vector3& v1, const Vector3& v2);

int DistanceSquaredBetweenPoints(const IntVector2& v1, const IntVector2& v2);
float DistanceSquaredBetweenPoints(const Vector2& v1, const Vector2& v2);
int DistanceSquaredBetweenPoints(const IntVector3& v1, const IntVector3& v2);
float DistanceSquaredBetweenPoints(const Vector3& v1, const Vector3& v2);

int RandInt(int min, int max);
int RandIntZeroToSize(int n);
float Randf(float Min, float Max);

float ToRadians(float degrees);
float ToDegrees(float radians);
int Quadrant(float angle);

float RangeMap(float inValue, float inStart, float inEnd, float outStart, float outEnd);
float ClampFloat(float f, float min, float max);

float CalcShortestAngularDisplacement(float fromDegrees, float toDegrees);

float CosDegrees(float radians);
float SinDegrees(float radians);

bool NumberWithinRange(float number, float start, float end);
bool NumberWithinRange(int number, int start, int end);

float AngleBetweenVectors(const Vector3& v1, const Vector3& v2);
Vector3 Slerp(const Vector3& v1, const Vector3& v2, float time);
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

//---------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------
//FUNCTION DEFINITIONS---------------------------------------------------------------------------------------------------------------
inline float DistanceBetweenPoints(const IntVector2& v1, const IntVector2& v2) {
	return (v2 - v1).Length();
}
inline float DistanceBetweenPoints(const Vector2& v1, const Vector2& v2) {
	return (v2 - v1).Length();
}
inline float DistanceBetweenPoints(const IntVector3& v1, const IntVector3& v2) {
	return (v2 - v1).Length();
}
inline float DistanceBetweenPoints(const Vector3& v1, const Vector3& v2) {
	return (v2 - v1).Length();
}

inline bool NumberWithinRange(float number, float start, float end) {
	return number > start && number < end;
}
inline bool NumberWithinRange(int number, int start, int end) {
	return number > start && number < end;
}

//-----------------------------------------------------------------------------------------------
// Constants
//
const double TWO_PI = 6.283185307179586476925286766559;
const double PI = 3.1415926535897932384626433832795;
const double HALF_PI = 1.5707963267948966192313216916398;
const double QUARTER_PI = 0.78539816339744830961566084581988;
const double SQRT_2 = 1.4142135623730950488016887242097;
const double SQRT_3 = 1.7320508075688772935274463415059;
const double SQRT_2_OVER_2 = 0.70710678118654752440084436210485;
const double SQRT_3_OVER_2 = 0.86602540378443864676372317075294;
const double SQRT_3_OVER_3 = 0.57735026918962576450914878050196;
const double SQRT_3_OVER_6 = 0.28867513459481288225457439025098;

const float fTWO_PI = 6.283185307179586476925286766559f;
const float fPI = 3.1415926535897932384626433832795f;
const float fHALF_PI = 1.5707963267948966192313216916398f;
const float fQUARTER_PI = 0.78539816339744830961566084581988f;
const float fSQRT_2 = 1.4142135623730950488016887242097f;
const float fSQRT_3 = 1.7320508075688772935274463415059f;
const float fSQRT_2_OVER_2 = 0.70710678118654752440084436210485f;
const float fSQRT_3_OVER_2 = 0.86602540378443864676372317075294f;
const float fSQRT_3_OVER_3 = 0.57735026918962576450914878050196f;
const float fSQRT_3_OVER_6 = 0.28867513459481288225457439025098f;


//-----------------------------------------------------------------------------------------------
// Lookup tables
extern const float g_sinValuesForByteAngles[256];


//-----------------------------------------------------------------------------------------------
// Basic math utilities
//
template< typename T > const T& GetMin(const T& a, const T& b);
float GetMinFloat(const float a, const float b);
float GetMinFloat(const float a, const float b, const float c);
float GetMinFloat(const float a, const float b, const float c, const float d);
float GetMaxFloat(const float a, const float b);
float GetMaxFloat(const float a, const float b, const float c);
float GetMaxFloat(const float a, const float b, const float c, const float d);
template< typename T > T Clamp(const T& originalValue, const T& minValue, const T& maxValue);
float ClampZeroToOne(float value);
float ClampNegOneToOne(float value);
float RangeMapFloat(const float inputValue, const float inputRangeStart, const float inputRangeEnd, const float outputRangeStart, const float outputRangeEnd);
const int CalcLogBase2(int x);
const bool IsPowerOfTwo(int x);
float FastFloor(float f);
int FastFloorToInt(float f);


//-----------------------------------------------------------------------------------------------
// Angle and Trig utilities
// 
float ConvertRadiansToDegrees(float radians);
float ConvertDegreesToRadians(float degrees);
double ConvertRadiansToDegrees(double radians);
double ConvertDegreesToRadians(double degrees);
float CosDegrees(float degrees);
float SinDegrees(float degrees);
double CosDegrees(double degrees);
double SinDegrees(double degrees);
float CalcShortestAngularDeltaDegrees(float startDegrees, float endDegrees);


//-----------------------------------------------------------------------------------------------
// Interpolation/easing/tweening utilities
//
float SmoothStep(float inputZeroToOne);
float SmoothStep5(float inputZeroToOne);
float SmoothStart(float inputZeroToOne);
float SmoothStop(float inputZeroToOne);


//-----------------------------------------------------------------------------------------------
// Random number utilities
//
int GetRandomIntInRange(int minValueInclusive, int maxValueInclusive);
int GetRandomIntLessThan(int maxValueNotInclusive);
float GetRandomFloatZeroToOne();
float GetRandomFloatInRange(float minimumInclusive, float maximumInclusive);
bool GetRandomChance(float probabilityOfReturningTrue);


/////////////////////////////////////////////////////////////////////////////////////////////////
//-----------------------------------------------------------------------------------------------
template< typename T >
const T& GetMin(const T& a, const T& b)
{
	return a < b ? a : b;
}


//-----------------------------------------------------------------------------------------------
inline float GetMinFloat(const float a, const float b)
{
	return a < b ? a : b;
}


//-----------------------------------------------------------------------------------------------
inline float GetMinFloat(const float a, const float b, const float c)
{
	if (a < b)
	{
		return a < c ? a : c;
	}
	else
	{
		return b < c ? b : c;
	}
}


//-----------------------------------------------------------------------------------------------
inline float GetMinFloat(const float a, const float b, const float c, const float d)
{
	if (a < b)
	{
		if (a < c)
		{
			return a < d ? a : d;
		}
		else
		{
			return c < d ? c : d;
		}
	}
	else
	{
		if (b < c)
		{
			return b < d ? b : d;
		}
		else
		{
			return c < d ? c : d;
		}
	}
}


//-----------------------------------------------------------------------------------------------
inline float GetMaxFloat(const float a, const float b)
{
	return a > b ? a : b;
}


//-----------------------------------------------------------------------------------------------
inline float GetMaxFloat(const float a, const float b, const float c)
{
	if (a > b)
	{
		return a > c ? a : c;
	}
	else
	{
		return b > c ? b : c;
	}
}


//-----------------------------------------------------------------------------------------------
inline float GetMaxFloat(const float a, const float b, const float c, const float d)
{
	if (a > b)
	{
		if (a > c)
		{
			return a > d ? a : d;
		}
		else
		{
			return c > d ? c : d;
		}
	}
	else
	{
		if (b > c)
		{
			return b > d ? b : d;
		}
		else
		{
			return c > d ? c : d;
		}
	}
}


//-----------------------------------------------------------------------------------------------
template< typename T >
T Clamp(const T& originalValue, const T& minValue, const T& maxValue)
{
	T clampedValue = originalValue;
	if (clampedValue < minValue)
		clampedValue = minValue;
	else if (clampedValue > maxValue)
		clampedValue = maxValue;

	return clampedValue;
}


//-----------------------------------------------------------------------------------------------
inline float ClampZeroToOne(float value)
{
	if (value < 0.f)
		return 0.f;
	else if (value > 1.f)
		return 1.f;
	else
		return value;
}


//-----------------------------------------------------------------------------------------------
inline float ClampNegOneToOne(float value)
{
	if (value < -1.f)
		return -1.f;
	else if (value > 1.f)
		return 1.f;
	else
		return value;
}


//-----------------------------------------------------------------------------------------------
inline float RangeMapFloat(const float inputValue, const float inputRangeStart, const float inputRangeEnd, const float outputRangeStart, const float outputRangeEnd)
{
	float inputRangeWidth = inputRangeEnd - inputRangeStart;
	if (inputRangeWidth != 0.f)
	{
		float fractionInRange = (inputValue - inputRangeStart) / inputRangeWidth;
		return outputRangeStart + (fractionInRange * (outputRangeEnd - outputRangeStart));
	}
	else
	{
		return 0.5f * (outputRangeStart + outputRangeEnd);
	}
}


//-----------------------------------------------------------------------------------------------
inline float ConvertRadiansToDegrees(float radians)
{
	return radians * (180.f / fPI);
}


//-----------------------------------------------------------------------------------------------
inline double ConvertRadiansToDegrees(double radians)
{
	return radians * (180.0 / PI);
}


//-----------------------------------------------------------------------------------------------
inline float ConvertDegreesToRadians(float degrees)
{
	return degrees * (fPI / 180.f);
}


//-----------------------------------------------------------------------------------------------
inline double ConvertDegreesToRadians(double degrees)
{
	return degrees * (PI / 180.0);
}


//-----------------------------------------------------------------------------------------------
inline float CosDegrees(float degrees)
{
	return cos(ConvertDegreesToRadians(degrees));
}


//-----------------------------------------------------------------------------------------------
inline float SinDegrees(float degrees)
{
	return sin(ConvertDegreesToRadians(degrees));
}


//-----------------------------------------------------------------------------------------------
inline double CosDegrees(double degrees)
{
	return cos(ConvertDegreesToRadians(degrees));
}


//-----------------------------------------------------------------------------------------------
inline double SinDegrees(double degrees)
{
	return sin(ConvertDegreesToRadians(degrees));
}


//-----------------------------------------------------------------------------------------------
inline float CalcShortestAngularDeltaDegrees(float startDegrees, float endDegrees)
{
	float angularDisplacementDegrees = endDegrees - startDegrees;
	while (angularDisplacementDegrees > 180.f)
		angularDisplacementDegrees -= 360.f;
	while (angularDisplacementDegrees < -180.f)
		angularDisplacementDegrees += 360.f;

	return angularDisplacementDegrees;
}


//-----------------------------------------------------------------------------------------------
// For a given positive power-of-two x, find L = CalcLogBase2( x ) such that 2^L = X.
//
// For example, CalcLogBase2( 32 ) = 5, since 2^5 = 32.
//
inline const int CalcLogBase2(int x)
{
	int numBitShifts = 0;
	while (x)
	{
		x >>= 1;
		++numBitShifts;
	}

	return numBitShifts - 1; // e.g. if we shifted 6 times right before zeroing out, we were 00100000 (32), which is 2^5 (or 1<<5).
}


//-----------------------------------------------------------------------------------------------
// Returns true if x is a positive power of two (e.g. 1, 2, 4, 8, 16, 32, 64, 128, 256, 512...)
//
inline const bool IsPowerOfTwo(int x)
{
	return x && !(x & (x - 1));
}


//-----------------------------------------------------------------------------------------------
inline float SmoothStep(float inputZeroToOne)
{
	return inputZeroToOne * inputZeroToOne * (3.f - (2.f * inputZeroToOne));
}


//-----------------------------------------------------------------------------------------------
inline float SmoothStep5(float inputZeroToOne)
{
	const float& t = inputZeroToOne;
	return t * t * t * (t * (t * 6.f - 15.f) + 10.f);
}


//-----------------------------------------------------------------------------------------------
inline float SmoothStart(float inputZeroToOne)
{
	return (inputZeroToOne * inputZeroToOne);
}


//-----------------------------------------------------------------------------------------------
inline float SmoothStop(float inputZeroToOne)
{
	float oneMinusInput = 1.f - inputZeroToOne;
	return 1.f - (oneMinusInput * oneMinusInput);
}


//-----------------------------------------------------------------------------------------------
inline int GetRandomIntInRange(int minValueInclusive, int maxValueInclusive)
{
	// #TODO: use a faster, better random number generator
	// #TODO: use more bits for higher-range numbers
	return minValueInclusive + rand() % (1 + maxValueInclusive - minValueInclusive);
}


//-----------------------------------------------------------------------------------------------
inline int GetRandomIntLessThan(int maxValueNotInclusive)
{
	// #TODO: use a faster, better random number generator
	// #TODO: use more bits for higher-range numbers
	return rand() % maxValueNotInclusive;
}


//-----------------------------------------------------------------------------------------------
inline float GetRandomFloatZeroToOne()
{
	// #TODO: use a faster, better random number generator
	const float oneOverRandMax = 1.f / static_cast<float>(RAND_MAX);
	return static_cast<float>(rand()) * oneOverRandMax;
}


//-----------------------------------------------------------------------------------------------
inline float GetRandomFloatInRange(float minimumInclusive, float maximumInclusive)
{
	// #TODO: use a faster, better random number generator
	const float randomZeroToOne = GetRandomFloatZeroToOne();
	return minimumInclusive + (randomZeroToOne * (maximumInclusive - minimumInclusive));
}


//-----------------------------------------------------------------------------------------------
inline bool GetRandomChance(float probabilityOfReturningTrue)
{
	if (probabilityOfReturningTrue >= 1.f)
		return true;

	return GetRandomFloatZeroToOne() < probabilityOfReturningTrue;
}