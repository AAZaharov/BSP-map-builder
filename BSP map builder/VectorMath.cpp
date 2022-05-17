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

Vector2f VectorMath::FindDeltaPoint(Vector2f& begin, Vector2f& end, float shift)
{
	return Vector2f((begin.x + (end.x - begin.x) * shift), (begin.y + (end.y - begin.y) * shift));
}

inline double VectorMath::area(Vector2i& a, Vector2i& b, Vector2i& c)
{

	return ((b.x - a.x) * (c.y - a.y)) - ((b.y - a.y) * (c.x - a.x));
}

inline bool VectorMath::intersect_1(int a, int b, int c, int d)
{
	if (a > b)  std::swap(a, b);
	if (c > d)  std::swap(c, d);
	return std::max(a, c) <= std::min(b, d);
}

bool VectorMath::intersect(Vector2f& fa, Vector2f& fb, Vector2f& fc, Vector2f& fd)
{
	Vector2i a(fa);
	Vector2i b(fb);
	Vector2i c(fc);
 	Vector2i d(fd);

	//auto S = area(a, b, c);
	//auto S2 = area(a, b, d);
	//auto S3 = area(c, d, a);
	//auto S4 = area(c, d, b);


	//double t1 = (area(a, b, c)) * (area(a, b, d));
	//double t2 = (area(c, d, a)) * (area(c, d, b));
	//auto t3 = intersect_1(a.x, b.x, c.x, d.x);
	//auto t4 = intersect_1(a.y, b.y, c.y, d.y);



	return intersect_1(a.x, b.x, c.x, d.x)
		&& intersect_1(a.y, b.y, c.y, d.y)
		&& area(a, b, c) * area(a, b, d) <= 0
		&& area(c, d, a) * area(c, d, b) <= 0;
}

std::list<Vector2f> VectorMath::ScaleTopology(std::vector<Vector2f>& PointVector)
{

	std::vector<Vector2f>::iterator itA, itB, itC;

	std::list<Vector2f> ScalePointList;

	if (PointVector.size() < 3)
	{
		return ScalePointList;
	}

	Vector2f pointboofer;
	//find offset point for first point
	itA = PointVector.begin();
	itB = --PointVector.end();
	itC = itA + 1;


	pointboofer = VectorMath::FindBis(*itA, *itB, *itC);
	/*pointboofer = VectorMath::FindBis(points.at(0), points.at(points.size() - 1), points.at(1));*/
	ScalePointList.push_back(pointboofer);

	//find offsets for points from middle range 
	itB = itA + 1;
	itC = itB + 1;

	while (itC != PointVector.end())
	{

		pointboofer = VectorMath::FindBis(*itB, *itA, *itC);
		/*pointboofer = VectorMath::FindBis(points.at(i), points.at(i - 1), points.at(i + 1));*/
		ScalePointList.push_back(pointboofer);
		++itA;
		++itB;
		++itC;
	}

	//find offset point for last point
	itA = PointVector.begin();
	itB = --PointVector.end();
	itC = itB - 1;

	pointboofer = VectorMath::FindBis(*itB, *itC, *itA);
	//pointboofer = VectorMath::FindBis(points.at(points.size() - 1), points.at(points.size() - 2), points.at(0));
	ScalePointList.push_back(pointboofer);

	return ScalePointList;
	
}

std::list<Vector2f> VectorMath::ScaleTopology(std::list<Vector2f>& PointList)
{
	std::vector<Vector2f> PointVector;
	std::copy(PointList.begin(), PointList.end(), std::back_inserter(PointVector));

	return ScaleTopology(PointVector);
}
