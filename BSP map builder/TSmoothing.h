#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <algorithm>
#include "VectorMath.h"

using namespace sf;

class TSmoothing : public VectorMath
{
public:

	Vector2f FindDeltaPoint(Vector2f& begin, Vector2f& end);

	void BuildLines(Vector2f, Vector2f);

	void BuildSpline(Vector2f& p0, Vector2f& p1, Vector2f& p2);

	void SmoothLine(std::vector<Vector2f>& PointsVector);

	std::vector<Vector2f> GetContainer();

	void EraseContainer();


	std::vector<Vector2f> Scale(std::vector<Vector2f>&);


private:

	int counter = 0;


	const float t = 0.005; //smoothing step
	std::vector<Vector2f> VectorContainer;
	

};

