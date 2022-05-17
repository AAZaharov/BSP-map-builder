#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <algorithm>
#include "VectorMath.h"
#include <list>

using namespace sf;

class TSmoothing : public VectorMath
{
public:

	void BuildSpline(Vector2f& p0, Vector2f& p1, Vector2f& p2);

	void SmoothTheLines();

	void SetContainer(std::vector<Vector2f>);
	void SetContainer(std::list<Vector2f>&);

	std::vector<Vector2f> GetContainer();

	void EraseContainer();

	void DrawSplines(sf::RenderWindow&);

private:

	int counter = 0;


	const float t = 0.005; //smoothing step
	std::vector<Vector2f> VectorContainer;

	std::list<Vector2f> SplineContainer;
	/*std::list<Vector2f> VectorContainer;*/
	

};

