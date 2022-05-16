#include "TSmoothing.h"
#include <math.h>
#include <iostream>



Vector2f TSmoothing::FindDeltaPoint(Vector2f& begin, Vector2f& end)
{
	float step = 0.5;
	float dx = begin.x + (end.x - begin.x) * step;
	float dy = begin.y + (end.y - begin.y) * step;
	return Vector2f(dx, dy);
}

void TSmoothing::BuildLines(Vector2f p0, Vector2f p1)
{
	float hyp = sqrt((p1.x - p0.x) * (p1.x - p0.x) + (p1.y - p0.y) * (p1.y - p0.y));
	float cat = p1.y - p0.y;
	float alpha = hyp / cat;

	RectangleShape line_with_thickness(Vector2f(hyp, 5.f));
	line_with_thickness.setFillColor(Color::Red);
	line_with_thickness.setRotation(alpha);
}


void TSmoothing::BuildSpline(Vector2f& p0, Vector2f& p1, Vector2f& p2)
{
	Vector2f dp0 = FindDeltaPoint(p0, p1);
	Vector2f dp2 = FindDeltaPoint(p2, p1);


	for (float f = t; f < 1; f += t)
	{
		Vector2f vectortmp;
		vectortmp.x = (1 - f) * (1 - f) * dp0.x + 2 * f * (1 - f) * p1.x + f * f * dp2.x;
		vectortmp.y = (1 - f) * (1 - f) * dp0.y + 2 * f * (1 - f) * p1.y + f * f * dp2.y;
		VectorContainer.push_back(vectortmp);
	}
}

void TSmoothing::SmoothLine(std::vector<Vector2f>& PointsVector)
{
	std::vector<Vector2f> tmp;

	//Build spline on the first point
	BuildSpline(PointsVector.at(PointsVector.size() - 1), PointsVector.at(0), PointsVector.at(1));
	

	//Build spline on the last point
	BuildSpline(PointsVector.at(PointsVector.size() - 2), PointsVector.at(PointsVector.size() - 1), PointsVector.at(0));



	//Build splines on other points

	for (int i = 0; i + 2 < PointsVector.size(); ++i)
	{
		BuildSpline(PointsVector.at(i), PointsVector.at(i + 1), PointsVector.at(i + 2));
		
	}


}

std::vector<Vector2f> TSmoothing::GetContainer()
{
	return VectorContainer;
}

void TSmoothing::EraseContainer()
{
	VectorContainer.erase(VectorContainer.begin(), VectorContainer.end());
}


std::vector<Vector2f> TSmoothing::Scale(std::vector<Vector2f> &points)
{
	std::vector<Vector2f> tmp;
	Vector2f pointboofer;
	//find offset point for first cell data

	int count = 0;
	std::cout << count << std::endl;

	pointboofer = VectorMath::FindBis(points.at(0), points.at(points.size() - 1), points.at(1));
	tmp.push_back(pointboofer);

	//find offsets for points from middle range 

	for (int i = 1; i < points.size()-1; ++i)
	{
		++count;
		std::cout << count << std::endl;

		pointboofer = VectorMath::FindBis(points.at(i), points.at(i - 1), points.at(i + 1));
		tmp.push_back(pointboofer);
	}

	//find offset point for last cell data

	++count;
	std::cout << count << std::endl;

	pointboofer = VectorMath::FindBis(points.at(points.size() - 1), points.at(points.size() - 2), points.at(0));
	tmp.push_back(pointboofer);

	return tmp;
}

