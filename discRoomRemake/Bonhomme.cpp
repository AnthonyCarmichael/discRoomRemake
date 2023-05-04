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
}

const sf::Vector2f& Bonhomme::getPosition() const
{
	return _posBonhomme.getPosition();
}

void Bonhomme::setPosition(int posX, int posY)
{
	_posBonhomme.setPosition(posX, posY);
}

void Bonhomme::setPosition(const sf::Vector2f& pos)
{
	_posBonhomme.setPosition(pos);
}

void Bonhomme::move(int dir,float x, float y, int &animationCpt)
{
	if (x == 0 && y == 0 )
	{
		switch (dir)
		{
		case 1:
			_rectSprite.top = 0;
			_posBonhomme.move(0, 10);
			break;

		case 2:
			_rectSprite.top = 32;
			_posBonhomme.move(0, -10);
			break;

		case 3:
			_rectSprite.top = 64;
			_posBonhomme.move(-10, 0);
			break;

		case 4:
			_rectSprite.top = 96;
			_posBonhomme.move(10, 0);
			break;
		default:
			break;
		}
		if (dir > 0)
		{
			_rectSprite.left += 32;
			if (_rectSprite.left >= 128)
			{
				_rectSprite.left = 0;
			}
		}
	
		_posBonhomme.setTextureRect(_rectSprite);
	}
	else
	{
		if (dir !=0)
			animationCpt++;
		else
			animationCpt=0;
		if (animationCpt==10)
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
		
	}
	
}

void Bonhomme::draw(sf::RenderWindow& window) const
{
	window.draw(_posBonhomme);
}
