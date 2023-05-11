#include <SFML/Graphics.hpp>
#include <cassert>
#include "Bonhomme.h"

void Bonhomme::init(int posX, int posY, int w, int h, const sf::IntRect& rectSprite, const char* nomSprite)
{
	_posBonhomme.setPosition(posX, posY);
	_posBonhomme.setSize(sf::Vector2f(w, h));
	if (!_textureBonhomme.loadFromFile(nomSprite))
	{
		exit(1);
	}
	_posBonhomme.setTexture(&_textureBonhomme);
	_rectSprite = rectSprite;
	_posBonhomme.setTextureRect(rectSprite);
	_hitbox.setPosition(posX + 6, posY + 6);
	_hitbox.setSize(sf::Vector2f(w - 12, h - 12));
	_hitbox.setFillColor(sf::Color::Black);
}

const sf::Vector2f& Bonhomme::getPosition() const
{
	return _posBonhomme.getPosition();
}

const sf::Vector2f& Bonhomme::getHitboxPosition() const
{
	return _hitbox.getPosition();
}

void Bonhomme::setPosition(int posX, int posY)
{
	_posBonhomme.setPosition(posX, posY);
}

void Bonhomme::setPosition(const sf::Vector2f& pos)
{
	_posBonhomme.setPosition(pos);
}

void Bonhomme::setHitboxPosition(int posX, int posY)
{
	_hitbox.setPosition(posX, posY);
}

void Bonhomme::move(int &dir,float x, float y, int &animationCpt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (x == 0) && (y==0))
	{
		if (dir > 0)
		{
			animationCpt++;
			if (animationCpt >= 10)
			{
				_rectSprite.left += 32;
				animationCpt = 0;
			}
			if (_rectSprite.left >= 128)
			{
				_rectSprite.left = 0;
			}
		}
		switch (dir)
		{
		case 1://down
			_rectSprite.top = 0;
			_posBonhomme.move(0, 3);
			_hitbox.move(0, 3);
			break;

		case 2://up
			_rectSprite.top = 32;
			_posBonhomme.move(0, -3);
			_hitbox.move(0, -3);
			break;

		case 3://left
			_rectSprite.top = 64;
			_posBonhomme.move(-3, 0);
			_hitbox.move(-3, 0);
			break;

		case 4://right
			_rectSprite.top = 96;
			_posBonhomme.move(3, 0);
			_hitbox.move(3, 0);
			break;

		case 5://down left
			_rectSprite.top = 0;
			_posBonhomme.move(-3, 3);
			_hitbox.move(-3, 3);
			break;

		case 6://down right
			_rectSprite.top = 0;
			_posBonhomme.move(3, 3);
			_hitbox.move(3, 3);
			break;

		case 7://up left
			_rectSprite.top = 32;
			_posBonhomme.move(-3, -3);
			_hitbox.move(-3, -3);
			break;

		case 8://up right
			_rectSprite.top = 32;
			_posBonhomme.move(3, -3);
			_hitbox.move(3, -3);
			break;

		case 9://left down
			_rectSprite.top = 64;
			_posBonhomme.move(-3, 3);
			_hitbox.move(-3, 3);
			break;

		case 10://left up
			_rectSprite.top = 64;
			_posBonhomme.move(-3, -3);
			_hitbox.move(-3, -3);
			break;

		case 11://right down
			_rectSprite.top = 96;
			_posBonhomme.move(3, 3);
			_hitbox.move(3, 3);
			break;

		case 12://right up
			_rectSprite.top = 96;
			_posBonhomme.move(3, -3);
			_hitbox.move(3, -3);
			break;

		default:
			animationCpt = 0;
			break;
		}
		_posBonhomme.setTextureRect(_rectSprite);
	}
	else if (x!=0 || y!=0)//joystick
	{
		if (dir != 0)
		{
			animationCpt++;
			switch (dir)
			{
			case 1:
				_rectSprite.top = 0;
				break;

			case 2:
				_rectSprite.top = 32;
				break;

			case 3:
				_rectSprite.top = 64;
				break;

			case 4:
				_rectSprite.top = 96;
				break;
			default:
				break;
			}
		}
		else
			animationCpt = 0;
		if (animationCpt == 10)
		{
			_rectSprite.left += 32;
			if (_rectSprite.left >= 128)
			{
				_rectSprite.left = 0;
			}
			animationCpt = 0;
		}
		_posBonhomme.setTextureRect(_rectSprite);
		_posBonhomme.move(x, y);
		_hitbox.setPosition(_posBonhomme.getPosition().x + 6, _posBonhomme.getPosition().y + 6);
	}
	
}

void Bonhomme::draw(sf::RenderWindow& window) const
{
	window.draw(_posBonhomme);
	window.draw(_hitbox);
}
