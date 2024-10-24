#pragma once

class Bonhomme {
private:
	sf::RectangleShape _posBonhomme;
	sf::Texture _textureBonhomme;
	sf::IntRect _rectSprite;
	sf::RectangleShape _hitbox;
public:
	//initialise la position et le size du RectangleShape, 
	//load la texture et l�applique et affecte le IntRect et l�applique
	void init(int posX, int posY, int w, int h, const sf::IntRect& rectSprite, const char* nomSprite);

	//retourne et modifie la position du bonhomme
	const sf::Vector2f& getPosition()const;
	const sf::Vector2f& getHitboxPosition()const;
	const sf::RectangleShape getHitbox()const;

	void setPosition(int posX, int posY);
	void setPosition(const sf::Vector2f& pos);
	void setHitboxPosition(int posX, int posY);

	//animation du d�placement selon la direction
	void move(int &dir,float x, float y,int &animationCpt);

	//draw le RectangleShape ds la window
	void draw(sf::RenderWindow& window)const;
};


