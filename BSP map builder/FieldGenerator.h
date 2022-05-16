#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <list>
#include <iostream>

class FieldGenerator
{
private:
	struct Cell
	{
		sf::Vector2f p1;
		sf::Vector2f p2;
		Cell()
		{}
		Cell(sf::Vector2f a, sf::Vector2f b) : p1(a), p2(b)
		{

		}

		int GetWidth()
		{
			return p2.x - p1.x;
		}
		int GetHeight()
		{
			return p2.y - p1.y;
		}
		friend bool operator==(const Cell &c1, const Cell &c2)
		{
			return (c1.p1 == c2.p1 && c1.p2 == c2.p2);
		}
	};

	enum TypeMap
	{
		Triangle,
		Round
	};



public:

	enum TypeGen
	{
		StepByStep,
		Regresion,
		Cubic
	};

	FieldGenerator(int X0, int Y0, int X1, int Y1);

	float getRandomNumber(float min, float max);

	sf::Color GetRandomColor();

	void GenerateFrame(float minRatio, float maxRatio, TypeGen);

	void FrameSplit(Cell &cell, float minRatio, float maxRatio);

	void FramesSort();

	void FieldsDraw();

	void Test();

	std::list<sf::ConvexShape> GetConvexList();

	std::list<Cell> GetCellList();


private:

	int X0, Y0, Xn, Yn;


	std::list<Cell> CellList;
	std::list<sf::ConvexShape> ConList;
	std::list<sf::Color> ConColor;


};

