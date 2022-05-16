#include "GeometryGenerator.h"

void GeometryGenerator::GeneratePoints()
{
	PointList.erase(PointList.begin(), PointList.end());
	VectorList.erase(VectorList.begin(), VectorList.end());

	for (auto& f : FG->GetCellList())
	{

		int a = FG->getRandomNumber(f.p1.x, f.p2.x);
		int b = FG->getRandomNumber(f.p1.y, f.p2.y);

		CircleShape tmp(20, 20);
		tmp.setFillColor(OuterColor);
		tmp.setOrigin(20.0f, 20.0f);

		tmp.setPosition(a, b);

		PointList.push_back(tmp);
	};

	/*con.setPointCount(0);*/

	//Create container with points

	for (auto c : PointList)
	{
		VectorList.push_back(c.getPosition());
	}

}

bool GeometryGenerator::IsCollision(Vector2f P1, Vector2f P2, std::list<Vector2f> VectorListTmp)
{

	VectorListTmp.remove(P1);
	VectorListTmp.remove(P2);
	int counter = VectorListTmp.size();
	for (int i = 0; i < counter-1; ++i)
	{
		Vector2f P3 = VectorListTmp.front();
		
		VectorListTmp.pop_front();
		Vector2f P4 = VectorListTmp.front();

		if (intersect(P1, P2, P3, P4))
		{
			std::cout << "P1(" << P1.x << "," << P1.y << ") P2(" << P2.x << "," << P2.y << ") P3(" << P3.x << "," << P3.y
				<< ") P4(" << P4.x << "," << P4.y << ") is collusion\n";
			return 1;
		}

		//float Ua = ((P4.x - P3.x) * (P1.y - P3.y) - (P4.y - P3.y) * (P1.x - P3.x)) /
		//	((P4.y - P3.y) * (P2.x - P1.x) - (P4.x - P3.x) * (P2.y - P1.y));

		//float Ub = ((P2.x - P1.x) * (P1.y - P3.y) - (P2.y - P1.y) * (P1.x - P3.x)) /
		//	((P4.y - P3.y) * (P2.x - P1.x) * (P4.x - P3.x) * (P2.y - P1.y));

		//if ((Ua >= 0.00001 && Ua <= 1) && (Ub >= 0.00001 && Ub <= 1))
		//{
		//	return 1;
		//}
	}

	return 0;
}

std::list<CircleShape> GeometryGenerator::GetPointList()
{
	return PointList;
}

std::list<Vector2f> GeometryGenerator::GetVectorList()
{
	return VectorList;
}

void GeometryGenerator::DrawConvex(sf::RenderWindow& app)
{
	sf::ConvexShape Convex(PointList.size());
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
	for (auto& p : PointList)
	{
		app.draw(p);
	}
}

void GeometryGenerator::DrawLines(sf::RenderWindow& app)
{	
	for (int i = 0; i < VectorList.size(); i++)
	{
		sf::LineShape Line(VectorList.front(), VectorList.back());
		Line.setThickness(8);
		Line.setFillColor(Color::Blue);

		// Test Collision

		//if (IsCollision(VectorList.front(), VectorList.back(), VectorList))
		//{
		//	Line.setFillColor(Color::Red);
		//}
		//else
		//{
		//	Line.setFillColor(Color::Blue);
		//}

		//
		
		VectorList.emplace_back(VectorList.front());
		VectorList.pop_front();

		app.draw(Line);
	}
}
