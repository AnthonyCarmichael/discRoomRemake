#pragma once
class Score
{
private:
	std::string _nomJoueur;
	float _time;
public:
	Score();
	~Score();

	std::string getNom() const;
	float getTime() const;

	void setNom(std::string nom);
	
	void setTime(float temps);
	void setScore(std::string nom, float temps);

	void print(std::ostream& sortie) const;
	void read(std::istream& entree);

	bool operator>(const Score& autreScore)const;
	bool operator<(const Score& autreScore)const;
	bool operator==(const Score& autreScore)const;
};