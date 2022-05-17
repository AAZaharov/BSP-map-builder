#include "TSmoothing.h"
#include <math.h>
#include <iostream>


void TSmoothing::BuildSpline(Vector2f& p0, Vector2f& p1, Vector2f& p2)
{
	Vector2f dp0 = FindDeltaPoint(p0, p1, 0.5);
	Vector2f dp2 = FindDeltaPoint(p2, p1, 0.5);


	for (float f = t; f < 1; f += t)
	{
		Vector2f vectortmp;
		vectortmp.x = (1 - f) * (1 - f) * dp0.x + 2 * f * (1 - f) * p1.x + f * f * dp2.x;
		vectortmp.y = (1 - f) * (1 - f) * dp0.y + 2 * f * (1 - f) * p1.y + f * f * dp2.y;
		SplineContainer.push_back(vectortmp);
	}
}

void TSmoothing::SmoothTheLines()
{
	std::vector<Vector2f>::iterator itA, itB, itC;

	//Build spline on the first point

	itA = VectorContainer.begin();
	itB = --VectorContainer.end();
	itC = itA+1;

	BuildSpline(*itB, *itA, *itC);


	//Build spline on the last point

	itC = itB-1;

	BuildSpline(*itC, *itB, *itA);

	//Build splines on other points
	itB = itA + 1;
	itC = itB + 1;

	while(itC != VectorContainer.end())
	{
		BuildSpline(*itA, *itB, *itC);
		++itA;
		++itB;
		++itC;
	}

}

void TSmoothing::SetContainer(std::vector<Vector2f> tmp)
{
	VectorContainer = tmp;
}

void TSmoothing::SetContainer(std::list<Vector2f>& PointList)
{
	std::vector<Vector2f> tmp;
	std::copy(PointList.begin(), PointList.end(), std::back_inserter(tmp));
	SetContainer(tmp);
}

std::vector<Vector2f> TSmoothing::GetContainer()
{
	return VectorContainer;
}

void TSmoothing::EraseContainer()
{
	VectorContainer.erase(VectorContainer.begin(), VectorContainer.end());
}


void TSmoothing::DrawSplines(sf::RenderWindow&app)
{
	CircleShape point(3);
	point.setOrigin(3, 3);
	point.setFillColor(Color::Black);
	for (auto& v : SplineContainer)
	{
		point.setPosition(v);
		app.draw(point);
	}
}

