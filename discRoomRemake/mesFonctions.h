#pragma once
bool ifCollisionBonhomme(Bonhomme& bob);
bool ifCollisionScie(Scie& scie, bool& move, int& moveX, int& moveY);
bool ifCollisionBonhommeScie(Scie& scie, Bonhomme& bob);
void setText(sf::Text& text, const char* message, sf::Font& font, const char* police, int posX, int posY, int taille, const sf::Color& color, int style);
void insertionSort(std::vector<Score>& tableauScore);
void ouvrirFichier(std::ifstream& monFlux, std::string nomFichier);
void lireFichier(std::ifstream& monFlux, std::vector<Score>& tableauScore);
