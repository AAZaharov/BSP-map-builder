#pragma once
#include "VectorMath.h"
#include "FieldGenerator.h"
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

	bool IsCollision(Vector2f, Vector2f);
	bool CollisionTest(std::list<Vector2f>);

	std::list<CircleShape> GetPointList();
	std::list<Vector2f> GetVectorList();

	void DrawConvex(sf::RenderWindow&);
	void DrawPoints(sf::RenderWindow&);
	void DrawPoints(sf::RenderWindow&, std::list<Vector2f>&);
	void DrawLines(sf::RenderWindow&);

	void Test();

private:

	FieldGenerator* FG = nullptr;
	sf::Color OuterColor, InnerColor;
	std::list<CircleShape> PointVector;
	std::list<Vector2f> VectorList;

};

