#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bonhomme.h"
#include"Scie.h"
#include"mesFonctions.h"

using namespace sf;

int main() {

	RenderWindow window;
	RectangleShape fondEcran;
	Texture textureFondEcran;
	Scie scie;
	Bonhomme bonhommeDisc;
	IntRect rectSprite(0, 0, 32, 32);
	IntRect backgroundSprite(0, 0, 800, 600);
	Clock clock;
	Time time;

	int dirX = 0;
	int dirY = 0;
	int dir = 0;

	float lastX = 0;
	float lastY = 0;
	float temp = 0;
	bool colision = false;
	int animationCpt = 0;

	//modification max
	scie.initScie(150, 150, 32, 32, rectSprite, "ressources/disc_room_charsets.png");

	window.create(VideoMode(800, 600), "Lost SFML");
	window.setFramerateLimit(60); // un appel suffit, après la création de la fenêtre

	//Écran
	fondEcran.setSize(Vector2f(800, 600));
	//fondEcran.setOutlineColor(Color::Red);
	//fondEcran.setOutlineThickness(5);
	//fondEcran.setFillColor(Color::White);
	

	//Bonhomme
	bonhommeDisc.init(400 - 16, 300 - 16, 32, 32, rectSprite, "ressources/disc_room_charsets.png");
	bonhommeDisc.setPosition(400, 300);

	//bonhomme.setFillColor(Color::Blue);

	
	if (!textureFondEcran.loadFromFile("ressources/disc_room_background.png"))
	{
		return 1;
	}
	fondEcran.setTexture(&textureFondEcran);

	// on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
	while (window.isOpen())
	{
		// on inspecte tous les évènements de la fenêtre qui ont été émis depuis la précédente     itération
		Event event;

		while (window.pollEvent(event))
		{
			// évènement "fermeture demandée" : on ferme la fenêtre
			if (event.type == Event::Closed)
				window.close();
			else if (event.type == Event::KeyPressed)
			{
				switch (event.key.code) {
				case Keyboard::Escape:
					window.close();
					break;
				case Keyboard::Down:
					dir = 1;
					break;
				case Keyboard::Up:
					dir = 2;
					break;
				case Keyboard::Left:
					dir = 3;
					break;
				case Keyboard::Right:
					dir = 4;
					break;
				}
			}
			else if (event.type == Event::JoystickMoved)
			{
				if (event.joystickMove.axis == sf::Joystick::X)
				{
					lastX = Joystick::getAxisPosition(0, sf::Joystick::X) / 40;
					std::cout << "X: " << Joystick::getAxisPosition(0, sf::Joystick::X) << std::endl;
					if (lastX<0)
					{
						dirX = 3;
					}
					else if (lastX>0)
					{
						dirX = 4;
					}
				}
				if (event.joystickMove.axis == sf::Joystick::Y)
				{
					lastY = event.joystickMove.position / 40;
					std::cout << "Y: " << Joystick::getAxisPosition(0, sf::Joystick::Y) << std::endl;
					if (lastY < 0)
					{
						dirY = 2;
					}
					else if (lastY > 0)
					{
						dirY = 1;
					}
				}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// À METTRE EN FONCTIOM
				// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//comparer lastX et lastY
				if (lastX < 0 && lastY > 0)
				{
					//conversion
					temp = lastX * -1;
					if (temp >= lastY)
					{
						dir = dirX;
					}
					else
					{
						dir = dirY;
					}
				}
				else if (lastY < 0 && lastX>0)
				{
					//conversion
					temp = lastY * -1;
					if (temp >= lastY)
					{
						dir = dirX;
					}
					else
					{
						dir = dirY;
					}
				}
				else if (lastY < 0 && lastX < 0)
				{
					if (lastX >= lastY)
					{
						dir = dirX;
					}
					else
					{
						dir = dirY;
					}
				}
				else if (lastY > 0 && lastX > 0)
				{
					if (lastX <= lastY)
					{
						dir = dirX;
					}
					else
					{
						dir = dirY;
					}
				}
				//deadZone pas de movement
				if (lastX < 0.1 && lastX > -0.1 && lastY < 0.1 && lastY > -0.1)
				{
					dir = 0;
				}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		}

		//time = clock.getElapsedTime();

		//if (time.asMilliseconds() >= 100.0f)
		//{
			bonhommeDisc.move(dir, lastX, lastY, animationCpt);

			if (bonhommeDisc.getPosition().x > 800 - 32 || bonhommeDisc.getPosition().x < 0)
			{
				colision = true;
				switch (dir)
				{
				case 3:
					bonhommeDisc.setPosition(0, bonhommeDisc.getPosition().y);
					break;
				case 4:
					bonhommeDisc.setPosition(800 - 32, bonhommeDisc.getPosition().y);
					break;
				default:
					exit(1);
					break;
				}
			}
			if (bonhommeDisc.getPosition().y > 600 - 32 || bonhommeDisc.getPosition().y < 0)
			{
				colision = true;
				switch (dir)
				{
				case 1:
					bonhommeDisc.setPosition(bonhommeDisc.getPosition().x, 0);
					break;
				case 2:
					bonhommeDisc.setPosition(bonhommeDisc.getPosition().x, 600 - 32);
					break;
				default:
					exit(1);
					break;
				}
			}

			//modification max
			scie.moveScie();
			ifCollisionScie(scie);

			window.clear(Color::Black);

			//UpDate
			
			//bonhommeDisc.move(dir, lastX, lastY);

			//DRAW
			window.draw(fondEcran);
			scie.draw(window);
			bonhommeDisc.draw(window);

			// fin de la frame courante, affichage de tout ce qu'on a dessiné
			window.display();
			//clock.restart();
		//}
	}
	exit(0);
}