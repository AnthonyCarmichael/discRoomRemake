#include <SFML/Graphics.hpp>
#include<assert.h>
#include<time.h>
#include "Scie.h"




void Scie::initScie(int w, int h, const sf::IntRect& rectSprite, const char* nomSprite, int type)
{
    if (!_textureScie.loadFromFile(nomSprite))
        exit;
    _rectSprite = rectSprite;

    _posX = rand() % (668 + 1 - 100) + 100;
    _posY = rand() % (468 + 1 - 100) + 100;

    _posScie.setSize(sf::Vector2f(w, h));
    _posScie.setPosition(sf::Vector2f(_posX, _posY));
    _posScie.setTexture(&_textureScie);//Applique la texture � position
    _posScie.setTextureRect(_rectSprite);
    _hitbox.setPosition(_posX + 4, _posY + 4);
    _hitbox.setSize(sf::Vector2f(w - 8, h - 8));
    _hitbox.setFillColor(sf::Color::Black);
    _cptAnimation = 0;
    _type = type;
    _move = false;
    _moveX = 0;
    _moveY = 0;
    _active = false;
}

const sf::Vector2f& Scie::getPosition() const
{
    return _posScie.getPosition();
}

const sf::Vector2f& Scie::getSize() const
{
    return _posScie.getSize();
}

const sf::RectangleShape Scie::getRectangle() const
{
    return _posScie;
}

const sf::RectangleShape Scie::getHitbox() const
{
    return _hitbox;
}

int Scie::getMoveX() const
{
    return _moveX;
}

int Scie::getMoveY() const
{
    return _moveY;
}

bool Scie::getActive() const
{
    return _active;
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

void Scie::setMoveX(int moveX)
{
    _moveX = moveX;
}

void Scie::setMoveY(int moveY)
{
    _moveY = moveY;
}

void Scie::setActive(bool active)
{
    _active = active;
}

void Scie::initMoveScie()
{
    if (_active)
    {
        if (!_move)
        {
            do {
                _moveX = rand() % (1 + 1 - -1) + -1;
                _moveY = rand() % (1 + 1 - -1) + -1;
                _move = true;
            } while (_moveX == 0 || _moveY == 0);
            _moveX = _moveX * 5;
            _moveY = _moveY * 5;
        }

        _posScie.move(sf::Vector2f(_moveX, _moveY));
        _hitbox.move(sf::Vector2f(_moveX, _moveY));
        _cptAnimation++;

        if (_cptAnimation == 5)
        {
            _cptAnimation = 0;
            _rectSprite.left += 32;
        }



        if (_rectSprite.left > 32)
        {
            _rectSprite.left = 0;
        }
        _posScie.setTextureRect(_rectSprite);
    }
}

void Scie::draw(sf::RenderWindow& window) const
{
    window.draw(_posScie);
    //window.draw(_hitbox);
}
