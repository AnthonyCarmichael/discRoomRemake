#pragma once
bool ifCollisionBonhomme(Bonhomme& bob);
bool ifCollisionScie(Scie& scie, bool& move, int& moveX, int& moveY);
bool ifCollisionBonhommeScie(Scie& scie, Bonhomme& bob);
void setText(sf::Text& text, const char* message, sf::Font& font, const char* police, int posX, int posY, int taille, const sf::Color& color, int style);
void afficherTableauScore(std::vector<Score>& tableauScore);