#include <SFML/Graphics.hpp>
#include "Bonhomme.h"

using namespace sf;

int main() {

	RenderWindow window;
	RectangleShape fondEcran;
	Bonhomme bonhommeDisc;
	IntRect rectSprite(0, 0, 32, 32);
	Clock clock;
	Time time;

	int dir = 0;

	float lastX = 0;
	float lastY = 0;
	bool colision = false;

	window.create(VideoMode(800, 600), "Lost SFML");
	window.setFramerateLimit(60); // un appel suffit, après la création de la fenêtre

	//Écran
	fondEcran.setSize(Vector2f(800, 600));
	fondEcran.setOutlineColor(Color::Red);
	fondEcran.setOutlineThickness(5);
	fondEcran.setFillColor(Color::White);

	//Bonhomme
	bonhommeDisc.init(400 - 16, 300 - 16, 32, 32, rectSprite, "ressources/disc_room_charsets.png");
	bonhommeDisc.setPosition(400, 300);

	//bonhomme.setFillColor(Color::Blue);

	Texture textureBonhomme;
	if (!textureBonhomme.loadFromFile("ressources/charsets.bmp"))
	{
		return 1;
	}


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
					lastX = Joystick::getAxisPosition(0, sf::Joystick::X) / 15;
				}
				if (event.joystickMove.axis == sf::Joystick::Y)
				{
					lastY = event.joystickMove.position / 15;
				}
			}
		}

		time = clock.getElapsedTime();

		if (time.asMilliseconds() >= 100.0f)
		{
			bonhommeDisc.move(dir, lastX, lastY);

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

			window.clear(Color::Black);

			//UpDate
			dir = 0;
			//bonhommeDisc.move(dir, lastX, lastY);

			//DRAW
			window.draw(fondEcran);
			bonhommeDisc.draw(window);

			// fin de la frame courante, affichage de tout ce qu'on a dessiné
			window.display();
			clock.restart();
		}
	}
	exit(0);
}