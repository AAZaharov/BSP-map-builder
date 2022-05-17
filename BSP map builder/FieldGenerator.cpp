#include "FieldGenerator.h"

using namespace sf;

FieldGenerator::FieldGenerator(int X0, int Y0, int X1, int Y1) : X0(X0), Y0(Y0), Xn(X1), Yn(Y1)
{

	//Create first base cell

	CellList.push_back(Cell(Vector2f(X0, Y0), Vector2f(X1, Y1)));

	ConColor.push_back(GetRandomColor());
}

float FieldGenerator::getRandomNumber(float min, float max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	return static_cast<float>(rand() * fraction * (max - min + 1) + min);
}

sf::Color FieldGenerator::GetRandomColor()
{
	return sf::Color(rand() % 255, rand() % 255, rand() % 255, 200);
}

void FieldGenerator::GenerateFrame(float minRatio, float maxRatio, TypeGen Type)
{

	switch (Type)
	{
	case StepByStep:
	{
		Cell tmpcell = CellList.front();
		CellList.pop_front();

		FrameSplit(tmpcell, minRatio, maxRatio);

		break;
	}

	case Regresion:
	{
		//Find the most large frame
		float MaxCellsq = CellList.front().GetHeight() * CellList.front().GetWidth();
		Cell MaxCell;
		
		for (auto& c : CellList)
		{
			if ((c.GetHeight() * c.GetWidth()) >= MaxCellsq)
			{
				MaxCellsq = c.GetHeight() * c.GetWidth();
				MaxCell = c;
			}
		}
		
		CellList.remove(MaxCell);

		FrameSplit(MaxCell, minRatio, maxRatio);

		break;
	}

	case Cubic:
	{
		int ListSize = CellList.size();
		for (int i = 0; i <= ListSize; ++i)
		{
			Cell tmpcell = CellList.front();
			CellList.pop_front();

			FrameSplit(tmpcell, minRatio, maxRatio);

		}
		break;
	}

	default:
		break;
	}
	
}

void FieldGenerator::FrameSplit(Cell& tmpcell, float minRatio, float maxRatio)
{
	if (0.25 * tmpcell.GetWidth() < 0.75 * tmpcell.GetWidth() ||
		0.25 * tmpcell.GetHeight() < 0.75 * tmpcell.GetHeight())
	{
		int dx, dy;
		dx = getRandomNumber((minRatio * tmpcell.GetWidth()), (maxRatio * tmpcell.GetWidth()));

		dy = getRandomNumber((minRatio * tmpcell.GetHeight()), (maxRatio * tmpcell.GetHeight()));;

		if (tmpcell.GetWidth() >= tmpcell.GetHeight())
		{
			CellList.push_back(Cell(Vector2f(tmpcell.p2.x - dx, tmpcell.p1.y), tmpcell.p2));
			tmpcell.p2.x -= dx;
			ConColor.push_back(ConColor.front());
			ConColor.pop_front();

			CellList.push_back(tmpcell);
			ConColor.push_back(GetRandomColor());
		}
		else
		{
			CellList.push_back(Cell(Vector2f(tmpcell.p1.x, tmpcell.p2.y - dy), tmpcell.p2));
			tmpcell.p2.y -= dy;
			ConColor.push_back(ConColor.front());
			ConColor.pop_front();

			CellList.push_back(tmpcell);
			ConColor.push_back(GetRandomColor());
		}
	}
}

void FieldGenerator::FramesSort()
{

	int flag = 0;
	std::list<Cell> SortCel;

	//Find first element
	
	for (auto& c : CellList)
	{	
		if (c.p1.x == X0 && c.p1.y == Y0)
		{
			SortCel.push_back(c);
			CellList.remove(c);
			break;
		}
	}

	//Sorting with 4 cycles
	do
	{
		switch (flag)
		{
		//Start sorting to the right
		case 0:
		{

			for (int i = 0; i < SortCel.size(); ++i)
			{
				for (auto& c : CellList)
				{

					if (SortCel.back().p2.x == c.p1.x &&
						((c.p2.y > SortCel.back().p1.y) &&
							(SortCel.back().p2.y > c.p1.y)) > 0 &&
						SortCel.back().p2.x <= c.p2.x)
					{
						SortCel.push_back(c);
						CellList.remove(c);

						if (SortCel.back().p2.x == Xn)
						{
							++flag;
							break;
						}
						break;
					}
				}
			}
			if (flag == 0) ++flag;
			break;
		}
		//Start sorting downwards
		case 1:
		{

			for (int i = 0; i < SortCel.size(); ++i)
			{
				
				for (auto& c : CellList)
				{
					//Цикл как в первом случае
					/*
					if (c.p1.y == CellList.back().p2.y &&
						((CellList.back().p2.x - c.p1.x) +
							(c.p2.x - CellList.back().p1.x)) > 0 &&
						c.p2.y > CellList.back().p2.y)		*/

					if (SortCel.back().p2.y == c.p1.y &&
						c.p2.x > SortCel.back().p1.x)
					{
						SortCel.push_back(c);
						CellList.remove(c);

						if (SortCel.back().p2.y == Yn)
						{
							++flag;
							break;
						}
						break;
					}
					
				}
			}
			if (flag == 1) ++flag;
			break;
		}
		//Start sorting to the left
		case 2:
		{

			for (int i = 0; i < SortCel.size(); ++i)
			{
				for (auto& c : CellList)
				{
					if (SortCel.back().p1.x == c.p2.x &&
						((c.p2.y > SortCel.back().p1.y) &&
							(SortCel.back().p2.y > c.p1.y)) &&
						SortCel.back().p1.x >= c.p1.x)
					{
						SortCel.push_back(c);
						CellList.remove(c);

						if (SortCel.back().p1.x == X0)
						{
							++flag;
							break;
						}
						break;
					}
					
				}
			}

			if(flag == 2) ++flag;
			break;
		}
		//Start sorting up with only one ellement adding
		case 3:
		{

			for (auto& c : CellList)
			{

				if (SortCel.back().p1.y == c.p2.y &&
					c.p1.x < SortCel.back().p2.x)
				{
					SortCel.push_back(c);
					CellList.remove(c);

					++flag;
					break;
				}
			}
			++flag;
			break;
		}
		}
	} while (flag < 4);

	CellList.erase(CellList.begin(), CellList.end());
	std::copy(SortCel.begin(), SortCel.end(), std::back_inserter(CellList));
	
}

void FieldGenerator::FieldsDraw()
{
	std::vector<sf::Color> tmpColor;
	std::copy(ConColor.begin(), ConColor.end(), std::back_inserter(tmpColor));
	int counter = 0;
	ConvexShape Convex(4);
	Convex.setOutlineThickness(-4);
	Convex.setOutlineColor(Color::Black);
	
	for (auto c : CellList)
	{
		Convex.setFillColor(tmpColor.at(counter));
		Convex.setPoint(0, c.p1);
		Convex.setPoint(1, Vector2f(c.p2.x, c.p1.y));
		Convex.setPoint(2, c.p2);
		Convex.setPoint(3, Vector2f(c.p1.x, c.p2.y));
		ConList.push_back(Convex);
		++counter;
	}

}

void FieldGenerator::Test()
{
	int counter = 0;
	for (auto c : CellList)
	{
		std::cout << counter << " X1 - " << c.p1.x << " Y1 - " << c.p1.y;
		std::cout << " X2 - " << c.p2.x << " Y2 - " << c.p2.y << " W= " << c.GetWidth() << " H= " << c.GetHeight() << std::endl;
		++counter;
	}
	std::cout << std::endl;
}

std::list<sf::ConvexShape> FieldGenerator::GetConvexList()
{
	return ConList;
}

std::list<FieldGenerator::Cell> FieldGenerator::GetCellList()
{
	return CellList;
}