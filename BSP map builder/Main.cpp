#include <SFML/Graphics.hpp>
#include <chrono>
#include "FieldGenerator.h"
#include "GeometryGenerator.h"
#include "sfLine.h"

using namespace sf;



int main()
{
	srand(time(NULL));

	int X = 1200;
	int Y = 1200;

	FieldGenerator FG(0, 0, X, Y);
	GeometryGenerator GeGe(FG, Color::Black, Color::Black);

	ContextSettings setting;
	setting.antialiasingLevel = 2;

	RenderWindow app(VideoMode(X, Y), "Map BSP", Style::Default, setting);
	app.setFramerateLimit(20);

	//TEXT WITH NUMBERS

	Font font;
	font.loadFromFile("CyrilicOld.ttf");

	//

	

	



	//std::vector<Vertex> VerTest;

	//VerTest.push_back(Vertex(Vector2f(100.f, 100.f), Color::Black));
	//VerTest.push_back(Vertex(Vector2f(200.f, 100.f), Color::Black));
	//VerTest.push_back(Vertex(Vector2f(100.f, 200.f), Color::Black));
	//VerTest.push_back(Vertex(Vector2f(200.f, 200.f), Color::Black));
	//VerTest.push_back(Vertex(Vector2f(100.f, 300.f), Color::Black));
	//VerTest.push_back(Vertex(Vector2f(200.f, 300.f), Color::Black));

   	while (app.isOpen())
	{

		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				app.close();

			if (e.type == Event::KeyReleased)
			{
				if (e.key.code == sf::Keyboard::Space)
				{
					
					FG.Test();


					// Test Collision
					std::list<Vector2f> VectorList = GeGe.GetVectorList();
					for (int i = 0; i < VectorList.size(); i++)
					{

						if (GeGe.IsCollision(VectorList.front(), VectorList.back(), VectorList))
						{
							std::cout << "Vector " << i << " is collision\n";
						}
						else
						{
							std::cout << "Vector " << i << " clear\n";
						}

						VectorList.emplace_back(VectorList.front());
						VectorList.pop_front();
					}
				}
			}

			if (e.type == Event::KeyReleased)
			{
				if (e.key.code == sf::Keyboard::Num1)
				{
					FG.GenerateFrame(0.25, 0.75, FG.StepByStep);
					FG.FieldsDraw();
					
				}
			}

			if (e.type == Event::KeyReleased)
			{
				if (e.key.code == sf::Keyboard::Num2)
				{
					FG.GenerateFrame(0.25, 0.75, FG.Regresion);
					FG.FieldsDraw();

				}
			}

			if (e.type == Event::KeyReleased)
			{
				if (e.key.code == sf::Keyboard::Num3)
				{
					FG.GenerateFrame(0.25, 0.75, FG.Cubic);
					FG.FieldsDraw();

				}
			}

			if (e.type == Event::KeyReleased)
			{
				if (e.key.code == sf::Keyboard::Num4)
				{
					GeGe.GeneratePoints();

				}
			}

			if (e.type == Event::KeyReleased)
			{
				if (e.key.code == sf::Keyboard::Num5)
				{
					

				}
			}

			if (e.type == Event::KeyReleased)
			{
   				if (e.key.code == sf::Keyboard::S)
				{
					FG.FramesSort();
					
				}
			}

			if (e.type == Event::KeyReleased)
			{
				if (e.key.code == sf::Keyboard::Enter)
				{
					std::cout << "Test\n";
					
				}
			}

		}

		
		app.clear(Color::White);








		for (auto& con : FG.GetConvexList())
		{
			app.draw(con);
		}


		int counter = 0;
		for (auto& f : FG.GetCellList())
		{
			std::string s = std::to_string(counter);

			Text text(s, font, 40);
			text.setFillColor(Color::Black);

			text.setStyle(sf::Text::Bold);
			text.setPosition(f.p1);
			text.move(20, 20);

			app.draw(text);

			++counter;
		}




		/*app.draw(GeGe.DrawConvex());*/

		GeGe.DrawLines(app);
		GeGe.DrawPoints(app);

		app.display();
	}
	


	return 0;
}
