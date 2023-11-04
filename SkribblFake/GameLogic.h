#pragma once
#include "PlayerRepo.h"

class GameLogic
{
private:
	int secondsPassed = 0;
	PlayerRepo players;

public:

	GameLogic()=default;
	//aceasta functie afiseaza trecerea timpului si afiseaza jumatate din literele cuvantului
	void TimePassing(Word word);
	//aceasta functie verifica pentru fiecare jucator daca a ghicit cuvantul si pune in clasa Player numarul de secunde in care acesta a ghicit
	void Guess();
	//aceasta functie verifica daca un anumit jucator a ghicit cuvantul dat
	bool PlayerGuess(Player player,Word word);
	//aceasta functie adauga scor jucatorului in functie de secundele in care a ghicit
	void AddScore();

};

