#include "GameLogic.h"
#include<ctime>
#include<iostream>
#include<conio.h>

void GameLogic::TimePassing(Word word)
{
	clock_t start = clock();
	int secunde_afisare = 30;
	int size_text = word.getSizeUnrevealedWord();
	while ((m_secondsPassed != 60) && (!PlayersHaveGuesed()))
	{
		clock_t curent = clock();
		m_secondsPassed = (curent - start) / CLOCKS_PER_SEC;
		std::cout << "Trecerea secundelor: " << m_secondsPassed << "\r";
		if (m_secondsPassed == secunde_afisare && secunde_afisare <= 55)
		{
			word.revealOneRandomLetter();
			std::cout << std::endl << word.getCurrentSlotState() << std::endl;
			secunde_afisare += (30 / (size_text / 2));
		}
		Guess(word);
	}
	std::cout << "Cuvantul este: " << word.getWord();
	m_secondsPassed = 0;
	_getch();
}

void GameLogic::Guess(Word word)
{
	for (Player player : m_players.getAll())
	{
		if (PlayerGuess(player, word))
		{
			player.SetSecondsGuess(m_secondsPassed);
		}
	}
}

bool GameLogic::PlayerGuess(Player player, Word word)
{
	std::string guess;
	std::getline(player.GetStream(), guess);
	player.PositioningBegin();
	if (guess == word.getWord())
	{
		return true;
	}
	return false;
}

void GameLogic::AddScore()
{
}

bool GameLogic::PlayersHaveGuesed()
{
	for (Player player : m_players.getAll())
	{
		if (player.GetSecondsGuess() == 0)
		{
			return false;
		}
	}
	return true;
}
