#pragma once
#define _USE_MATH_DEFINES
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <math.h>
#include <cmath>

using namespace sf;

class VectorMath
{
public:
	
	virtual float VectorMagnitude(Vector2f & A, Vector2f & B);

	/// <summary>
	/// Find angle value of vector BAC
	/// </summary>
	/// <param name="A"> Base point </param>
	/// <param name="B"> Second point </param>
	/// <param name="C"> Third point </param>
	/// <returns>Angle in radians</returns>
	virtual float FindAngle(Vector2f& A, Vector2f& B, Vector2f& C);

	virtual float VectorAxisDeviation(Vector2f& A, Vector2f& B);

	virtual Vector2f MirrorPoint(Vector2f& A, Vector2f& B);

	virtual Vector2f FindBis(Vector2f& A, Vector2f& B, Vector2f& C);

	inline int area(Vector2f& a, Vector2f& b, Vector2f& c);

	inline bool intersect_1(float a, float b, float c, float d);

	bool intersect(Vector2f& a, Vector2f& b, Vector2f& c, Vector2f& d);

private:
	 

	bool flag = 0;
	int counter = 0;

};

