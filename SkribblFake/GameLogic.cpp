#include "GameLogic.h"
#include<ctime>
#include<iostream>
#include<conio.h>

void GameLogic::TimePassing(Word word)
{
	for (auto i : m_players.getAll())
	{
		i.setSecondsGuess(0);
	}
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
}

void GameLogic::Guess(Word word)
{
	for (Player player : m_players.getAll())
	{
			if (PlayerGuess(player, word))
			{
				player.setSecondsGuess(m_secondsPassed);
			}
	}
}

bool GameLogic::PlayerGuess(Player player, Word word)
{
	std::string guess;
	std::getline(player.getStream(), guess);
	player.PositioningBegin();
	if (player.GetPainter() == true)
	{
		return true;
	}
	if (guess == word.getWord())
	{
		return true;
	}
	return false;
}

void GameLogic::AddScore()
{
	int alpha=0;
	for (Player player : m_players.getAll())
	{
		if(player.GetPainter()==false)
			alpha += player.getSecondsGuess();
	}
	alpha = alpha /( m_players.getAll().size()-1);
	for (Player player : m_players.getAll())
	{
		if (player.GetPainter() == true)
		{
			if (alpha == 0)
			{
				player.setScore(player.getScore() - 100);
			}
			else
			{
				int score = (60 - alpha) * 100 / 60;
				player.setScore(player.getScore() + score);
			}
		}
		else
		{
			if (player.getSecondsGuess() < 30 && player.getSecondsGuess() > 0)
			{
				player.setScore(player.getScore() + 100);
			}
			else if (player.getSecondsGuess() >= 30)
			{
				int score = (60 - player.getSecondsGuess()) * 100 / 30;
				player.setScore(player.getScore() + score);
			}
			else if (player.getSecondsGuess() == 0)
			{
				player.setScore(player.getScore() - 50);
			}
		}
		player.setSecondsGuess(0);
	}
}

bool GameLogic::PlayersHaveGuesed()
{
	int ok = 1;
	for (Player player : m_players.getAll())
	{
		if (player.getSecondsGuess() == 0)
		{
			ok = 0;
		}
	}
	if (ok == 1)
		return true;
	else
		return false;
}
