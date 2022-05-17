#include <SFML/Graphics.hpp>
#include <chrono>
#include "FieldGenerator.h"
#include "GeometryGenerator.h"
#include "sfLine.h"
#include "TSmoothing.h"

using namespace sf;



int main()
{
	srand(time(NULL));

	int X = 600;
	int Y = 600;

	FieldGenerator FG(0, 0, X, Y);
	GeometryGenerator GeGe(FG, Color::Black, Color::Black);
	TSmoothing TS, TSforScale;

	ContextSettings setting;
	setting.antialiasingLevel = 2;

	RenderWindow app(VideoMode(X, Y), "Map BSP", Style::Default, setting);
	app.setFramerateLimit(20);

	
	//TEXT WITH NUMBERS

	Font font;
	font.loadFromFile("CyrilicOld.ttf");

	//

	std::list<Vector2f> ForScale;


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

					GeGe.Test();
					// Test Collision
					GeGe.CollisionTest(GeGe.GetVectorList());
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
					TS.EraseContainer();
					auto listtemp = GeGe.GetVectorList();
					TS.SetContainer(listtemp);
					TS.SmoothTheLines();

				}
			}

			if (e.type == Event::KeyReleased)
			{
				if (e.key.code == sf::Keyboard::Num6)
				{
					
					
					ForScale = GeGe.GetVectorList();
					ForScale = GeGe.ScaleTopology(ForScale);

					TSforScale.EraseContainer();
					TSforScale.SetContainer(ForScale);
					TSforScale.SmoothTheLines();
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


		// ENABLE TEXT WITH NUMBERS
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
		/// /////////////////////////////

		//DRAW SCALE POINTS FOR TEST
		{
			//TSmoothing SplinesForScale;


			GeGe.DrawPoints(app, ForScale);

			//SplinesForScale.SetContainer(ForScale);
			//SplinesForScale.SmoothTheLines();
			//SplinesForScale.DrawSplines(app);
		}
		/// /////////////////////////////


		GeGe.DrawLines(app);
		GeGe.DrawPoints(app);
		TS.DrawSplines(app);
		TSforScale.DrawSplines(app);

		app.display();
	}
	


	return 0;
}
