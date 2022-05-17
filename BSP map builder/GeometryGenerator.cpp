#include "GeometryGenerator.h"

void GeometryGenerator::GeneratePoints()
{
	PointVector.erase(PointVector.begin(), PointVector.end());
	VectorList.erase(VectorList.begin(), VectorList.end());

	for (auto& f : FG->GetCellList())
	{

		int a = FG->getRandomNumber(f.p1.x, f.p2.x);
		int b = FG->getRandomNumber(f.p1.y, f.p2.y);

		CircleShape tmp(20, 20);
		tmp.setFillColor(OuterColor);
		tmp.setOrigin(20.0f, 20.0f);

		tmp.setPosition(a, b);

		PointVector.push_back(tmp);
	};

	//Create container with points

	for (auto c : PointVector)
	{
		VectorList.push_back(c.getPosition());
	}

}

bool GeometryGenerator::IsCollision(Vector2f P1, Vector2f P2)
{
	


	int VectorSize = VectorList.size();
	auto iter = std::find(VectorList.begin(), VectorList.end(), P2);
	auto iterend = std::find(VectorList.begin(), VectorList.end(), P1);

	Vector2f P3, P4;

	++iter;
	if (iter == VectorList.end())
	{
		iter = VectorList.begin();

	}

		while(iter != iterend)
		{
			
			P3 = *iter;
			++iter;
			if (iter == VectorList.end())
			{
				iter = VectorList.begin();
				if (iter == iterend)
				{
					break;
				}

			}
			else if (iter == iterend)
			{
				break;
			}

			P4 = *iter;

			if (intersect(P1, P2, P3, P4))
			{
				return 1;
			}
			++iter;
			if (iter == VectorList.end())
			{
				iter = VectorList.begin();
				if (iter == iterend)
				{
					break;
				}

			}
			else if (iter == iterend)
			{
				break;
			}
		}

	return 0;
}

bool GeometryGenerator::CollisionTest(std::list<Vector2f> VectorListTemp)
{
	int VectorSize = VectorListTemp.size();
	auto iter = VectorListTemp.begin();
	Vector2f P1, P2, P3, P4;
	for (int i = 0; i < VectorListTemp.size(); ++i)
	{
		std::advance(iter, i);
		P1 = *iter;
		++iter;
		P2 = *iter;
		++iter;
		if (iter == VectorListTemp.end())
		{
			std::cout << "Overflow of iteration: " << i << std::endl;
			break;
		}
		std::cout << "Iteration: " << i << std::endl;
		for (int j = 0; j < VectorListTemp.size()-2-i; ++j)
		{
			std::cout << "Check vector: " << j << std::endl;
			P3 = *iter;
			++iter;
			if (iter == VectorListTemp.end())
			{
				iter = VectorListTemp.begin();
				if (P1 == VectorListTemp.front())
				{
					break;
				}
			}

			P4 = *iter;
			if (intersect(P1, P2, P3, P4))
			{
				
				std::cout << "Vector(" << P1.x<<","<<P1.y << " : " << P2.x << "," << P2.y 
					<< ") and vector(" << P3.x << "," << P3.y << " : " << P4.x << "," << P4.y<< ") have collision\n\n";
			}
			else
			{
				std::cout << "Vector(" << P1.x << "," << P1.y << " : " << P2.x << "," << P2.y
					<< ") and vector(" << P3.x << "," << P3.y << " : " << P4.x << "," << P4.y << ") no collision\n\n";

			}
		}
	}


	return 0;
}

std::list<CircleShape> GeometryGenerator::GetPointList()
{
	return PointVector;
}

std::list<Vector2f> GeometryGenerator::GetVectorList()
{
	return VectorList;
}

void GeometryGenerator::DrawConvex(sf::RenderWindow& app)
{
	sf::ConvexShape Convex(PointVector.size());
	Convex.setFillColor(Color::Transparent);
	Convex.setOutlineThickness(-4);
	Convex.setOutlineColor(OuterColor);
	int counter = 0;
	for (auto v : VectorList)
	{
		Convex.setPoint(counter, v);
		++counter;
	}
	
	app.draw(Convex);
}

void GeometryGenerator::DrawPoints(sf::RenderWindow& app)
{
	for (auto& p : PointVector)
	{
		app.draw(p);
	}
}

void GeometryGenerator::DrawPoints(sf::RenderWindow& app, std::list<Vector2f>& PointList)
{
	CircleShape tmp(20);
	tmp.setOrigin(20, 20);
	tmp.setFillColor(OuterColor);

	for (auto p : PointList)
	{
		tmp.setPosition(p);
		app.draw(tmp);
	}
}

void GeometryGenerator::DrawLines(sf::RenderWindow& app)
{	
	std::list<Vector2f>::iterator iter;

	if (VectorList.size())
	{
		iter = VectorList.begin();

		while (iter != --VectorList.end())
		{
			auto P1 = *iter;
			auto P2 = *(++iter);


			sf::LineShape Line(P1, P2);
			Line.setThickness(8);
			
			// Test Collision

			if (IsCollision(P1, P2))
			{
				Line.setFillColor(Color::Red);
			}
			else
			{
				Line.setFillColor(Color::Blue);
			}

			//

			app.draw(Line);
		}
		
		sf::LineShape Line(VectorList.back(), VectorList.front());
		Line.setThickness(8);
		Line.setFillColor(Color::Blue);

		app.draw(Line);

	}
}

void GeometryGenerator::Test()
{
	std::cout << std::endl;
	int counter = 0;
	for (auto v : VectorList)
	{
		std::cout << "Point "<< counter<<": (" << v.x<<","<<v.y<<")" << std::endl;
		counter++;
	}
}
