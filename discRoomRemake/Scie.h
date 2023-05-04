#pragma once
class Scie
{
private:
	sf::RectangleShape _posScie;
	sf::Texture _textureScie;
	sf::IntRect _rectSprite;

public:
	void initScie(int posX, int posY, int w, int h, const sf::IntRect& rectSprite, const char* nomSprite);

	const sf::Vector2f& getPosition()const;

	void setPosition(int posX, int posY);
	void setPosition(const sf::Vector2f& pos);

	void moveScie();

	void draw(sf::RenderWindow& window)const;
};