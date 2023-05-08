#include <SFML/Graphics.hpp>
#include <iostream>
#include <time.h>
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
	/*Time time;*/

	int dirX = 0;
	int dirY = 0;
	int dir = 0;
	int dirDiagonale=0;
	int moveX = 0;
	int moveY = 0;

	float lastX = 0;
	float lastY = 0;
	float temp = 0;
	bool move = false;
	bool colision = false;
	int animationCpt = 0;

	srand(time(NULL));
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
					
					if (Keyboard::isKeyPressed(Keyboard::Left))
					{
						dir=5;//bas gauche
					}
					else if (Keyboard::isKeyPressed(Keyboard::Right))
					{
						dir = 6;//bas droite
					}
					else
					{
						dir = 1;//bas
					}
				break;
				case Keyboard::Up:
					if (Keyboard::isKeyPressed(Keyboard::Left))
					{
						dir = 7;//haut gauche
					}
					else if (Keyboard::isKeyPressed(Keyboard::Right))
					{
						dir = 8;//haut droite
					}
					else
					{
						dir = 2;//Haut
					}
					break;
				case Keyboard::Left:
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						dir = 9;//Gauche bas
					}
					else if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						dir = 10;//Gauche haut
					}
					else
					{
						dir = 3;//gauche
					}

					break;
				case Keyboard::Right:
					if (Keyboard::isKeyPressed(Keyboard::Down))
					{
						dir = 11;//Droite bas
					}
					else if (Keyboard::isKeyPressed(Keyboard::Up))
					{
						dir = 12;//Droite haut
					}
					else
					{
						dir = 4;//Droite
					}
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
				// Doit déterminer la valeur la plus importante pour choisir quelle sprite afficher pour le bonhomme
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
				else if (lastX > 0 && lastY < 0)
				{
					//conversion
					temp = lastY * -1;
					if (temp >= lastX)
					{
						dir = dirY;
					}
					else
					{
						dir = dirX;
					}
				}
				else if (lastY < 0 && lastX < 0)
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
				else if (lastY > 0 && lastX > 0)
				{
					if (lastX > lastY)
					{
						dir = dirX;
					}
					else
					{
						dir = dirY;
					}
				}
				//deadZone pas de movement
				if (lastX < 0.2 && lastX > -0.2 && lastY < 0.2 && lastY > -0.2)
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
			ifCollisionBonhomme(bonhommeDisc);
			

			//modification max
			scie.initMoveScie(move, moveX, moveY);
			ifCollisionScie(scie, move, moveX, moveY);

			window.clear(Color::Black);

			//UpDate
			dir = 0;
			dirDiagonale = 0;
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