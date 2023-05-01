#include <SFML/Graphics.hpp>

using namespace sf;

int main() {

	RenderWindow window;
	RectangleShape fondEcran;
	RectangleShape bonhomme;

	Clock clock;
	Time time;
	int dir = 2;

	float lastX = 0;
	float lastY = 0;

	window.create(VideoMode(800, 600), "Lost SFML");
	window.setFramerateLimit(60); // un appel suffit, apr�s la cr�ation de la fen�tre

	//�cran
	//fondEcran.setPosition(10, 20);
	fondEcran.setSize(Vector2f(800, 600));
	fondEcran.setOutlineColor(Color::Red);
	fondEcran.setOutlineThickness(5);
	fondEcran.setFillColor(Color::White);

	//Bonhomme
	bonhomme.setPosition(400, 300);
	bonhomme.setSize(Vector2f(32, 32));
	//bonhomme.setFillColor(Color::Blue);

	Texture textureBonhomme;
	if (!textureBonhomme.loadFromFile("ressources/charsets.bmp"))
	{
		return 1;
	}

	bonhomme.setTexture(&textureBonhomme);
	IntRect rectSprite(32, 0, 32, 32);
	bonhomme.setTextureRect(rectSprite);

	// on fait tourner le programme jusqu'� ce que la fen�tre soit ferm�e
	while (window.isOpen())
	{
		// on inspecte tous les �v�nements de la fen�tre qui ont �t� �mis depuis la pr�c�dente     it�ration
		Event event;

		while (window.pollEvent(event))
		{
			// �v�nement "fermeture demand�e" : on ferme la fen�tre
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

		//time = clock.getElapsedTime();
		//if (time.asMilliseconds() >= 100.0f)
		//{
		//	switch (dir)
		//	{
		//	case 1:
		//		rectSprite.top = 96;
		//		bonhomme.move(0, -10);
		//		break;

		//	case 2:
		//		rectSprite.top = 0;
		//		bonhomme.move(0, 10);
		//		break;

		//	case 3:
		//		rectSprite.top = 32;
		//		bonhomme.move(-10, 0);
		//		break;

		//	case 4:
		//		rectSprite.top = 64;
		//		bonhomme.move(10, 0);
		//		break;
		//	default:
		//		break;
		//	}

			////reset boucle sprite
			//rectSprite.left += 32;
			//if (rectSprite.left >= 96)
			//{
			//	rectSprite.left = 0;
			//}
			//bonhomme.setTextureRect(rectSprite);

			// effacement de la fen�tre en noir
		window.clear(Color::Black);

		//UpDate
		bonhomme.move(lastX, lastY);

		//DRAW
		window.draw(fondEcran);
		window.draw(bonhomme);

		// fin de la frame courante, affichage de tout ce qu'on a dessin�
		window.display();
		clock.restart();
	}
	exit(0);
}