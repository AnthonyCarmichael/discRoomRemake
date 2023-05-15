#include <iostream>
#include <assert.h>
#include <iomanip>
#include "Score.h"

using namespace std;

Score::Score()
{
	_nomJoueur = "";
	_time = 0;
}

Score::~Score()
{
	_nomJoueur = "";
	_time = 0.00;
}


std::string Score::getNom() const
{
	return _nomJoueur;
}

float Score::getTime() const
{
	return _time;
}

void Score::setNom(std::string nom)
{
	assert(nom != "");
	_nomJoueur = nom;
}

void Score::setTime(float temps)
{
	assert(temps >= 0.00);
	_time = temps;
}

void Score::setScore(std::string nom, float temps)
{
	setNom(nom);
	setTime(temps);
}

void Score::print(std::ostream& sortie) const
{
	sortie << _nomJoueur << " " << _time << endl;
}

void Score::read(std::istream& entree)
{
	entree >> _nomJoueur >> _time;
}

bool Score::operator==(const Score& autreScore) const
{
	return (_nomJoueur == autreScore._nomJoueur);
}

bool Score::operator>(const Score& autreScore) const
{
	return (_time > autreScore._time);
}

bool Score::operator<(const Score& autreScore) const
{
	return (_time < autreScore._time);
}

std::ostream& operator<<(std::ostream& sortie, const Score& score)
{
	score.print(sortie);

	return sortie;
}

std::istream& operator>>(std::istream& entree, Score& score)
{
	score.read(entree);

	return entree;
}
