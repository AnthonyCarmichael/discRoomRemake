#pragma once
bool ifCollisionBonhomme(Bonhomme& bob);
bool ifCollisionScie(Scie& scie);
bool ifCollisionBonhommeScie(Scie& scie, Bonhomme& bob);
void setText(sf::Text& text, const char* message, sf::Font& font, const char* police, int posX, int posY, int taille, const sf::Color& color, int style);
void insertionSort(std::vector<Score>& tableauScore);
void ouvrirFichierLecture(std::ifstream& monFlux, std::string nomFichier);
void ouvrirFichierEcriture(std::ofstream& monFlux, std::string nomFichier);
void lireFichier(std::ifstream& monFlux, std::vector<Score>& tableauScore);
void ecrireFichier(std::ofstream& monFlux, std::vector<Score>& tableauScore);