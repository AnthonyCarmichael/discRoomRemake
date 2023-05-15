#pragma once
class Scie
{
private:
	sf::RectangleShape _posScie;
	sf::Texture _textureScie;
	sf::IntRect _rectSprite;
	sf::RectangleShape _hitbox;
	int _cptAnimation=0;

public:
	
	void initScie(int posX, int posY, int w, int h, const sf::IntRect& rectSprite, const char* nomSprite);

	const sf::Vector2f& getPosition()const;
	const sf::Vector2f& getSize()const;
	const sf::RectangleShape getRectangle()const;
	const sf::RectangleShape getHitbox()const;

	void setPosition(int posX, int posY);
	void setPosition(const sf::Vector2f& pos);

	void initMoveScie(bool& move, int& moveX, int& moveY);

	void draw(sf::RenderWindow& window)const;
};