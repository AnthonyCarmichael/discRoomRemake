#include <SFML/Graphics.hpp>
#include<assert.h>
#include<time.h>
#include "Scie.h"


void Scie::initScie(int posX, int posY, int w, int h, const sf::IntRect& rectSprite, const char* nomSprite)
{
    if (!_textureScie.loadFromFile("ressources/disc_room_charsets.png"))
        exit;
    _rectSprite = rectSprite;

    _posScie.setSize(sf::Vector2f(w, h));
    _posScie.setPosition(sf::Vector2f(posX, posY));
    _posScie.setTexture(&_textureScie);//Applique la texture à position
    _posScie.setTextureRect(_rectSprite);
}

const sf::Vector2f& Scie::getPosition() const
{
    return _posScie.getPosition();
}

void Scie::setPosition(int posX, int posY)
{
    assert(posX > 0);
    assert(posY > 0);

    _posScie.setPosition(posX, posY);
}

void Scie::setPosition(const sf::Vector2f& pos)
{
    _posScie.setPosition(sf::Vector2f(pos));
}

void Scie::initMoveScie(bool& move, int& moveX, int& moveY)
{

    if (!move) 
    {
        moveX = rand() % (10 + 1 - -10) + -10;
        moveY = rand() % (10 + 1 - -10) + -10;
        move = true;
    }
    /*moveX = moveX / 10;
    moveY = moveY / 10;*/
    _posScie.move(sf::Vector2f(moveX, moveY));
}

void Scie::draw(sf::RenderWindow& window) const
{
    window.draw(_posScie);
}
