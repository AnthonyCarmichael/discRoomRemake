#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Bonhomme.h"
#include "Scie.h"
#include "Score.h"
#include "mesFonctions.h"

using namespace std;

bool ifCollisionBonhomme(Bonhomme& bob)
{

    if (bob.getPosition().x >= 700 - 32 && bob.getPosition().y <= 100)
    {
        bob.setPosition(sf::Vector2f(700 - 32, 100));
        bob.setHitboxPosition(700 - 26, 100 + 6);
        return true;
    }

    else if (bob.getPosition().x > 700 - 32 && bob.getPosition().y > 500 - 32)
    {
        bob.setPosition(sf::Vector2f(700 - 32, 500 - 32));
        bob.setHitboxPosition(700 - 26, 500 - 26);
        return true;
    }

    else if (bob.getPosition().x < 100 && bob.getPosition().y < 100)
    {
        bob.setPosition(sf::Vector2f(100, 100));
        bob.setHitboxPosition(100 + 6, 100 + 6);
        return true;
    }

    else if (bob.getPosition().x < 100 && bob.getPosition().y > 500 - 32)
    {
        bob.setPosition(sf::Vector2f(100, 500 - 32));
        bob.setHitboxPosition(100 + 6, 500 - 26);
        return true;
    }

    else if (bob.getPosition().x > 700 - 32)
    {
        bob.setPosition(sf::Vector2f(700 - 32, bob.getPosition().y));
        bob.setHitboxPosition(700 - 26, bob.getHitboxPosition().y);
        return true;
    }

    else if (bob.getPosition().x < 100)
    {
        bob.setPosition(sf::Vector2f(100, bob.getPosition().y));
        bob.setHitboxPosition(100 + 6, bob.getHitboxPosition().y);
        return true;
    }

    else if (bob.getPosition().y > 500 - 32)
    {
        bob.setPosition(sf::Vector2f(bob.getPosition().x, 500 - 32));
        bob.setHitboxPosition(bob.getHitboxPosition().x, 500 - 26);
        return true;
    }

    else if (bob.getPosition().y < 100)
    {
        bob.setPosition(sf::Vector2f(bob.getPosition().x, 100));
        bob.setHitboxPosition(bob.getHitboxPosition().x, 100 + 6);
        return true;
    }

    return false;

}

bool ifCollisionScie(Scie& scie,bool& move, int& moveX, int& moveY)
{
    if (scie.getPosition().x > 700 - 32 && scie.getPosition().y < 100)
    {
    moveX = moveX / -1;
    moveY = moveY / -1;
    scie.initMoveScie(move, moveX, moveY);
    return true;
    }

    else if (scie.getPosition().x > 700 - 32 && scie.getPosition().y > 500 - 32)
    {
    moveX = moveX / -1;
    moveY = moveY / -1;
    scie.initMoveScie(move, moveX, moveY);
    return true;
    }

    else if (scie.getPosition().x < 100 && scie.getPosition().y < 100)
    {
    moveX = moveX / -1;
    moveY = moveY / -1;
    scie.initMoveScie(move, moveX, moveY);
    return true;
    }

    else if (scie.getPosition().x < 100 && scie.getPosition().y > 500 - 32)
    {
    moveX = moveX / -1;
    moveY = moveY / -1;
    scie.initMoveScie(move, moveX, moveY);
    return true;
    }

    else if (scie.getPosition().x > 700 - 32)
    {
        moveX = moveX / -1;
        scie.initMoveScie(move, moveX, moveY);
        return true;
    }

    else if (scie.getPosition().x < 100)
    {
        moveX = moveX / -1;
        scie.initMoveScie(move, moveX, moveY);
        return true;
    }

    else if (scie.getPosition().y > 500 - 32)
    {
        moveY = moveY / -1;
        scie.initMoveScie(move, moveX, moveY);
        return true;
    }

    else if (scie.getPosition().y < 100)
    {
        moveY = moveY / -1;
        scie.initMoveScie(move, moveX, moveY);
        return true;
    }

    return false;

}

bool ifCollisionBonhommeScie(Scie& scie, Bonhomme& bob)
{
    if (bob.getHitbox().getGlobalBounds().intersects(scie.getHitbox().getGlobalBounds()))
    {
        return true;
    }
    
    return false;
}

void setText(sf::Text& text, const char* message, sf::Font& font, const char* police, int posX, int posY, int taille, const sf::Color& color, int style)
{
    if (!font.loadFromFile(police))
        exit(1);

    text.setFont(font); //Set la police à utiliser (elle doit avoir été loadée)
    text.setString(message);		//Set le texte à afficher
    text.setCharacterSize(taille); 			//Set la taille (en pixels)
    text.setFillColor(color);			//Set la couleur du texte
    text.setStyle(style);	//Set le style du texte
    text.setPosition(posX, posY);
}

void afficherTableauScore(std::vector<Score>& tableauScore)
{
    cout << endl << endl;
    for (int i = 0; i < tableauScore.size(); i++) {
        cout << tableauScore.at(i);
    }
    cout << endl << endl;
}
