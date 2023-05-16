#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <fstream>
#include <vector>
#include <map>
#include <time.h>
#include "Bonhomme.h"
#include "Scie.h"
#include "Score.h"
#include"mesFonctions.h"

using namespace sf;

int main() {

	std::ifstream lecture;
	std::ofstream ecriture;

	RenderWindow window;
	RectangleShape fondEcranMenu;
	RectangleShape fondEcranPlay;
	RectangleShape menu[3];
	Texture texturefondEcranMenu;
	Texture texturefondEcranPlay;
	Scie scie;
	std::vector<Scie> scies;
	Bonhomme bonhommeDisc;
	Score scoreJoueurActif;
	IntRect rectSprite(0, 0, 32, 32);
	IntRect backgroundSprite(0, 0, 800, 600);
	Clock clock;
	Time timer;
	Sound musicMenu;
	Sound musicPlay;
	Font font;
	Text txt1;
	Text txt2;
	Text txt3;
	Text txtHighScore1;
	Text txtHighScore2;
	Text txtInfo;
	Text txtTimer;
	Text nomJoueur;
	Text txtPosition;
	Text txtTuto;


	std::vector<Score> tableauScore;

	int dirX = 0;
	int dirY = 0;
	int dir = 0;
	int animationCpt = 0;
	float lastX = 0;
	float lastY = 0;
	float temp = 0;
	float timeRun;
	bool firstStart = true;
	bool collision = false;
	bool menubool = true;
	bool play = false;
	bool info = false;

	std::string nomJoueurTemp="";
	

	srand(time(NULL));
	
	window.create(VideoMode(800, 600), "Lost SFML");
	window.setFramerateLimit(60); // un appel suffit, après la création de la fenêtre
	//modification max
	for (int i = 0; i < 10; i++)
	{
		scie.initScie(32, 32, rectSprite, "ressources/disc_room_sprite_saw.png",1);
		scies.push_back(scie);
	}
	
		

	
	//MUSIQUE
	SoundBuffer bufferMenu;
	SoundBuffer bufferPlay;

	if (!bufferMenu.loadFromFile("ressources/disc_room_menu2.wav"))
		return -1;
	musicMenu.setBuffer(bufferMenu);
	musicMenu.setLoop(true);


	if (!bufferPlay.loadFromFile("ressources/disc_room3.wav"))
		return -1;
	musicPlay.setBuffer(bufferPlay);
	musicPlay.setLoop(true);
	
	///////////////////////////////////////////////////////////////////////////////
	//MENU
	//////////////////////////////////////////////////////////////////////////////
	
	for (int i = 0; i < 3; i++)
	{
		menu[i].setFillColor(Color::White);
		menu[i].setSize(Vector2f(100, 20));
		menu[i].setPosition(Vector2f(window.getSize().x / 2 - 30, 50 * i + 400));
		if (i==0)
			setText(txt1, "Play", font, "ressources/arial.ttf", window.getSize().x / 2, 50 * i + 400, 16, Color::Black, 0);
		if (i==1)
			setText(txt2, "Info", font, "ressources/arial.ttf", window.getSize().x / 2, 50 * i + 400, 16, Color::Black, 0);
		if (i==2)
			setText(txt3, "Quit", font, "ressources/arial.ttf", window.getSize().x / 2, 50 * i + 400, 16, Color::Black, 0);
	}

	setText(txtInfo, "Entrer un nom (trois lettres): ", font, "ressources/arial.ttf", 400, 0,24 , Color::Yellow, 0);

	setText(nomJoueur, "", font, "ressources/arial.ttf", 750, 0, 24, Color::Yellow, 0);

	setText(txtTimer, "", font, "ressources/arial.ttf", 600, 525, 24, Color::Yellow, 0);

	setText(txtHighScore1, "", font, "ressources/arial.ttf", 600, 525, 16, Color::Yellow, 0);

	setText(txtHighScore2, "", font, "ressources/arial.ttf", 600, 525, 16, Color::Yellow, 0);

	setText(txtPosition, "", font, "ressources/arial.ttf", 600, 525, 16, Color::Yellow, 0);

	setText(txtTuto, "Le but du jeu consiste à éviter les scies le plus longtemps possible. \nPour se faire, utilisez les touches WASD pour vous déplacer ou, \nVous pouvez aussi utiliser un joystick. \n \nAprès 10 secondes, une nouvelle scie apparaitra. \nAprès 3 secondes elle devient mortelle.  ", font, "ressources/arial.ttf", 10, 10, 16, Color::Yellow,0);

	ouvrirFichierLecture(lecture,"ressources/scores.txt");
	lireFichier(lecture,tableauScore);
	if (tableauScore.size() == 21)
	{
		tableauScore.erase(tableauScore.begin() + tableauScore.size() - 1);
	}
	//////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	//Écran
	fondEcranMenu.setSize(Vector2f(800, 600));
	fondEcranPlay.setSize(Vector2f(800, 600));
	//fondEcranPlay.setOutlineColor(Color::Red);
	//fondEcranPlay.setOutlineThickness(5);
	//fondEcranPlay.setFillColor(Color::White);

	if (!texturefondEcranMenu.loadFromFile("ressources/disc_room_menu.png"))
	{
		return 1;
	}
	fondEcranMenu.setTexture(&texturefondEcranMenu);

	if (!texturefondEcranPlay.loadFromFile("ressources/disc_room_background2BackUp.png"))
	{
		return 1;
	}
	fondEcranPlay.setTexture(&texturefondEcranPlay);


	//Bonhomme
	bonhommeDisc.init(150, 150, 32, 32, rectSprite, "ressources/disc_room_charsets.png");



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
				case Keyboard::S:
					
					if (Keyboard::isKeyPressed(Keyboard::A))
					{
						dir=5;//bas gauche
					}
					else if (Keyboard::isKeyPressed(Keyboard::D))
					{
						dir = 6;//bas droite
					}
					else
					{
						dir = 1;//bas
					}
				break;
				case Keyboard::W:
					if (Keyboard::isKeyPressed(Keyboard::A))
					{
						dir = 7;//haut gauche
					}
					else if (Keyboard::isKeyPressed(Keyboard::D))
					{
						dir = 8;//haut droite
					}
					else
					{
						dir = 2;//Haut
					}
					break;
				case Keyboard::A:
					if (Keyboard::isKeyPressed(Keyboard::S))
					{
						dir = 9;//Gauche bas
					}
					else if (Keyboard::isKeyPressed(Keyboard::W))
					{
						dir = 10;//Gauche haut
					}
					else
					{
						dir = 3;//gauche
					}

					break;
				case Keyboard::D:
					if (Keyboard::isKeyPressed(Keyboard::S))
					{
						dir = 11;//Droite bas
					}
					else if (Keyboard::isKeyPressed(Keyboard::W))
					{
						dir = 12;//Droite haut
					}
					else
					{
						dir = 4;//Droite
					}
					break;
				default:
					dir = 0;
					break;
				}
			}
			else if (event.type == Event::JoystickMoved)
			{
				if (event.joystickMove.axis == sf::Joystick::X)
				{
					lastX = Joystick::getAxisPosition(0, sf::Joystick::X) / 30;
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
					lastY = event.joystickMove.position / 30;
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
				// À METTRE EN FONCTIOM SI ON A LE TEMPS
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
			else if (event.type == Event::MouseButtonPressed && menubool && nomJoueurTemp.length()==3)
			{
				for (int i = 0; i < 3; i++)
				{
					if (menu[i].getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
						menu[i].setFillColor(Color::Black);
					else
						menu[i].setFillColor(Color::White);
				}
			}
			if (event.type == sf::Event::TextEntered && nomJoueurTemp.length()<3)
			{
				if (event.text.unicode >= 65 && event.text.unicode <= 90 || event.text.unicode >= 97 && event.text.unicode <=122 )
				{
					std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
					nomJoueurTemp += static_cast<char>(event.text.unicode);

					nomJoueur.setString(nomJoueurTemp);
				}
				
				
			}
		}//FIN POLL EVENT

		window.clear(Color::Black);

		//DRAW
	
		if (menubool)
		{
			
			window.draw(fondEcranMenu);

			if (firstStart)
			{
				musicMenu.play();
				firstStart = false;
			}
			if (nomJoueurTemp.length()== 3)
			{

				window.draw(nomJoueur);

				for (int i = 0; i < 3; i++)
				{
					window.draw(menu[i]);
					window.draw(txt1);
					window.draw(txt2);
					window.draw(txt3);
				}
				
			}
			else
			{
				window.draw(txtInfo);
				window.draw(nomJoueur);
				
			}
		}

		if (play)
		{
			
			window.draw(fondEcranPlay);
			window.draw(nomJoueur);
			bonhommeDisc.move(dir, lastX, lastY, animationCpt);
			ifCollisionBonhomme(bonhommeDisc);

			for (int i = 0; i < 10; i++) 
			{
				scies.at(i).initMoveScie();
				ifCollisionScie(scies.at(i));
				scies.at(i).draw(window);
			}
			
			bonhommeDisc.draw(window);
			
			for (int i = 0; i < 10; i++)
			{
				if (ifCollisionBonhommeScie(scies.at(i), bonhommeDisc))
				{
					collision = true;
				}
			}

			timer = clock.getElapsedTime();
			timeRun = timer.asSeconds();
			std::cout << timeRun << std::endl;
			
			txtTimer.setString(std::to_string(timeRun).erase(std::to_string(timeRun).size() - 4, 4));
			window.draw(txtTimer);

			if (collision == true)
			{
				scoreJoueurActif.setScore(nomJoueurTemp, timeRun);
				tableauScore.push_back(scoreJoueurActif);
				scoreJoueurActif.print(std::cout);
				insertionSort(tableauScore);
				if (tableauScore.size() == 21)
				{
					tableauScore.erase(tableauScore.begin() + tableauScore.size() - 1);
				}
				ouvrirFichierEcriture(ecriture, "ressources/scores.txt");
				ecrireFichier(ecriture, tableauScore);

				menubool = true;
				play = false;

				for (int i = 0; i < 10; i++)
				{
					scies.at(i).initScie(32, 32, rectSprite, "ressources/disc_room_sprite_saw.png", 1);
				}

				bonhommeDisc.init(150, 150, 32, 32, rectSprite, "ressources/disc_room_charsets.png");


			}
		}

		if (info)
		{
			txtInfo.setString("HIGHSCORE");
			txtInfo.setPosition(600, 80);
			window.draw(txtInfo);

			for (int i = 0; i < tableauScore.size(); i++)
			{
				txtPosition.setString(std::to_string(i + 1));
				if (i+1>=10)
					txtPosition.setPosition(600, 100 + ((i + 1) * 20));
				else
					txtPosition.setPosition(610, 100 + ((i + 1) * 20));

				txtHighScore1.setString(tableauScore.at(i).getNom());
				txtHighScore1.setPosition(635, 100 + ((i + 1) * 20));

			
				txtHighScore2.setString(std::to_string(tableauScore.at(i).getTime()).erase(std::to_string(tableauScore.at(i).getTime()).size()-4, 4));


				//Les temps alignés à la virgue
				if (tableauScore.at(i).getTime() >= 1000)
					txtHighScore2.setPosition(673, 100 + ((i + 1) * 20));
				else if ((tableauScore.at(i).getTime() >= 100))
					txtHighScore2.setPosition(682, 100 + ((i + 1) * 20));
				else if (tableauScore.at(i).getTime() >= 10)
					txtHighScore2.setPosition(691, 100 + ((i + 1) * 20));
				else
					txtHighScore2.setPosition(700, 100 + ((i + 1) * 20));

				window.draw(txtPosition);
				window.draw(txtHighScore1);
				window.draw(txtHighScore2);
				window.draw(txtTuto);
			}
		}
		//verification collision avec les scies

		

		window.display();
		window.draw(txtTimer);
		if (collision)
		{
			Sleep(1000);
			collision = false;
			musicPlay.stop();
			musicMenu.play();
		}
		
		//arrive une fois selon le choix du menu
		if (menu[0].getFillColor()==Color::Black)
		{
			menu[0].setFillColor(Color::White);
			musicMenu.stop();
			musicPlay.play();
			play = true;
			menubool = false;
			info = false;
			clock.restart();
			
		}
		if (menu[1].getFillColor() == Color::Black)
		{
			if (!info)
			{
				info = true;
			}
			else
			{
				info = false;
			}
			menu[1].setFillColor(Color::White);

			
		}
		if (menu[2].getFillColor() == Color::Black)
		{
			exit(0);
		}
	}
	exit(0);
}