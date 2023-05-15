#pragma once
class Scie
{
private:
	sf::RectangleShape _posScie;
	sf::Texture _textureScie;
	sf::IntRect _rectSprite;
	sf::RectangleShape _hitbox;
	int _type;
	int _cptAnimation=0;
	bool _move;
	int _moveX;
	int _moveY;
	int _posX;
	int _posY;
public:
	
	void initScie(int w, int h, const sf::IntRect& rectSprite, const char* nomSprite, int type);

	const sf::Vector2f& getPosition()const;
	const sf::Vector2f& getSize()const;
	const sf::RectangleShape getRectangle()const;
	const sf::RectangleShape getHitbox()const;
	int getMoveX()const;
	int getMoveY()const;

	void setPosition(int posX, int posY);
	void setPosition(const sf::Vector2f& pos);
	void setMoveX(int moveX);
	void setMoveY(int moveY);

	void initMoveScie();

	void draw(sf::RenderWindow& window)const;
};