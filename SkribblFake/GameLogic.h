#pragma once
#include "PlayerRepo.h"

class GameLogic
{
private:
	int m_secondsPassed = 0;
	PlayerRepo m_players;

public:

	GameLogic(PlayerRepo players)
		:m_players{ players }
	{
	}
	GameLogic()=default;
	//aceasta functie afiseaza trecerea timpului si afiseaza jumatate din literele cuvantului
	void TimePassing(Word word);
	//aceasta functie verifica pentru fiecare jucator daca a ghicit cuvantul si pune in clasa Player numarul de secunde in care acesta a ghicit
	void Guess(Word word);
	//aceasta functie verifica daca un anumit jucator a ghicit cuvantul dat
	bool PlayerGuess(Player player,Word word);
	//aceasta functie adauga scor jucatorului in functie de secundele in care a ghicit
	void AddScore();
	//aceasta functie returneaza true daca toti jucatorii au ghicit corect sau fals contrar
	bool PlayersHaveGuesed();
};

