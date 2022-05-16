#include "VectorMath.h"
#include <iostream>



using namespace sf;

float VectorMath::VectorMagnitude(Vector2f & P1, Vector2f & P2) 
{
	return sqrt((P2.x - P1.x) * (P2.x - P1.x) + (P2.y - P1.y) * (P2.y - P1.y));
}

float VectorMath::FindAngle(Vector2f& A, Vector2f& B, Vector2f& C)
{
	float cosa = (((B.x - A.x) * (C.x - A.x) + (B.y - A.y) * (C.y - A.y)) / (VectorMagnitude(A , B) * VectorMagnitude(A, C)));

	return acos(cosa);
}


float VectorMath::VectorAxisDeviation(Vector2f& P1, Vector2f& P2)
{
	//Projection of the x-axis

	Vector2f AX((P1.x + 1), P1.y);

	return FindAngle(P1, P2, AX);;
}

Vector2f VectorMath::MirrorPoint(Vector2f& A, Vector2f& B)
{
	return Vector2f((2*A.x - B.x),(2*A.y - B.y));
}

Vector2f VectorMath::FindBis(Vector2f& A, Vector2f& B, Vector2f& C)
{

	// Find the value of angle BAC //

	float RadBAC = FindAngle(A, B, C);
	float DegBAC = RadBAC * 180 / M_PI;

	//**********************************

	// Find the angle between vector AB and the X-axis //

	float RadBAX = VectorAxisDeviation(A, B);
	float DegBAX = RadBAX * 180 / M_PI;

	if (B.y > A.y)
	{
		RadBAX = -RadBAX;
		DegBAX = 360 - DegBAX;
	}

	//**********************************

	// Find the angle between vector AC and the X-axis //

	float RadCAX = VectorAxisDeviation(A, C);
	float DegCAX = RadCAX * 180 / M_PI;

	if (C.y > A.y)
	{
		RadCAX = -RadCAX;
		DegCAX = 360 - DegCAX;
	}

	//**********************************

	//Find the bisector angle from the angle difference and the angle polarity

	float RadBis = RadBAC / 2 - RadBAX;

	float DegBis = DegBAX - DegCAX;

	bool polarity;
	if (DegBis < 0 && DegBis > -180)
	{
		polarity = 1;
	}
	else if (DegBis > 180 && DegBis < 360)
	{
		polarity = 1;
	}
	else polarity = 0;

	//**********************************

	//Find the displacement of the point

	float dX1 = cos(RadBis) * 50;
	float dY1 = sin(RadBis) * 50;

	Vector2f result((A.x + dX1), (A.y + dY1));

	//**********************************

	//Invert the displacement of the point for negative angles 
	
	if (polarity)
	{
		++counter;
		return FindBis(A, C, B);	
	}

	//**********************************

	if (counter > 0)
	{
		counter = 0;
	}
	else if (counter == 0)
	{
		result = MirrorPoint(A, result);
	}


	return result;
}

inline int VectorMath::area(Vector2f& a, Vector2f& b, Vector2f& c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline bool VectorMath::intersect_1(float a, float b, float c, float d)
{
	if (a > b)  std::swap(a, b);
	if (c > d)  std::swap(c, d);
	return std::max(a, c) <= std::min(b, d);
}

bool VectorMath::intersect(Vector2f& a, Vector2f& b, Vector2f& c, Vector2f& d)
{
	return intersect_1(a.x, b.x, c.x, d.x)
		&& intersect_1(a.y, b.y, c.y, d.y)
		&& area(a, b, c) * area(a, b, d) <= 0
		&& area(c, d, a) * area(c, d, b) <= 0;
}
