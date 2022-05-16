#pragma once
#include "VectorMath.h"
#include "FieldGenerator.h"
#include "sfLine.h"
#include <list>



class GeometryGenerator :
	public VectorMath
{
public:

	GeometryGenerator(FieldGenerator& FG): FG(&FG)
	{
		OuterColor = Color::Black;
		InnerColor = Color::Black;
	}

	GeometryGenerator(FieldGenerator& FG, sf::Color OuterColor, sf::Color InnerColor) :
		FG(&FG), OuterColor(OuterColor), InnerColor(InnerColor) {};


	void GeneratePoints();

	bool IsCollision(Vector2f, Vector2f, std::list<Vector2f>);

	std::list<CircleShape> GetPointList();
	std::list<Vector2f> GetVectorList();

	void DrawConvex(sf::RenderWindow&);
	void DrawPoints(sf::RenderWindow&);
	void DrawLines(sf::RenderWindow&);

private:

	FieldGenerator* FG = nullptr;
	sf::Color OuterColor, InnerColor;
	std::list<CircleShape> PointList;
	std::list<Vector2f> VectorList;

};

