#include "GameRound.h"
#include <ctime>
#include <conio.h>

using namespace skribbl;

skribbl::GameRound::GameRound(DataBase& dB, crow::SimpleApp&app):
	m_dB { std::move(dB) },m_app{app}
{
	m_secondsPassed = 0;
	std::unordered_map<std::string, Player>::iterator it = m_dB.GetPlayersInGame().begin();
	m_painter = std::make_unique<Player>(it->second);
	while (it != m_dB.GetPlayersInGame().end())
	{
		m_restOfPlayers.push_back(std::make_unique<Player>(it->second));
		m_pointsAcumulated[it->second.GetName()] = 0;
		m_secondsForGuess[it->second.GetName()] = 0;
		it++;
	}
}

skribbl::GameRound::~GameRound()
{
}

DataBase& skribbl::GameRound::roundStart()
{
	//nu stiu daca ar trebui sa pun un delay mic intre alegere si startul desenului dar vedem mai tarziu 
	//cum se comporta cu serverul;
	int index = 0;
	while (index < m_restOfPlayers.size())
	{
		//aici ar trebui sa setmam cine deseneaza si cine nu si sa inceapa pe client wordChoosingSequence
		verifChoice();
		
		//aici ar trebui sa avem deja cuvantul si sa l trimitem catre tot serverul ca sa apara acolo sus in
		//functie de ce rol are fiecare (la painter tot si la restul cu revealOneRandomLetter
		//presupun ca am deja cuvantul aici;
		roundTimer();

		computeScore();

		index=swapPainter(index);

		std::unordered_map<std::string, Player>::iterator it = m_dB.GetPlayersInGame().begin();
		while (it != m_dB.GetPlayersInGame().end())
		{
			//aici pun scorul in clasa player sper:))
			it->second.SetScore(it->second.GetScore() + m_pointsAcumulated[it->second.GetName()]);

			m_pointsAcumulated[it->second.GetName()] = 0;
			m_secondsForGuess[it->second.GetName()] = 0;

			it++;
		}

		endOfRoundTimer();
	}
	return std::ref(m_dB);
}

void skribbl::GameRound::verifChoice()
{
	//trebuie sa vedem cum verificam daca a ales cuvantul
	m_secondsPassed = 0;
	clock_t start = clock();
	while (m_secondsPassed != 10)
	{
		clock_t curent = clock();
		m_secondsPassed = (curent - start) / CLOCKS_PER_SEC;
	}
}

void skribbl::GameRound::chooseThreeRandomWords()
{
	std::srand(std::time(0));

	std::vector<Word> words = m_dB.getAllWords();

	int randomIndex;
	std::vector<Word> randomWords;
	for (int i = 0; i < 3; ++i) {
		randomIndex = std::rand() % words.size();
		randomWords.push_back(words[randomIndex]);
	}
	m_wordChoice = randomWords;
}

void skribbl::GameRound::chooseOneRandomWord()
{
	std::srand(std::time(0));
	int index = std::rand() % 3;
	m_word=m_wordChoice[index];
}



void skribbl::GameRound::roundTimer()
{
	m_secondsPassed = 0;
	clock_t start = clock();
	int secunde_afisare = 30;
	int sizeText = m_word.GetWord().size();
	while ((m_secondsPassed != 60) && (!verifGuess()))
	{
		clock_t curent = clock();
		m_secondsPassed = (curent - start) / CLOCKS_PER_SEC;
		std::cout << "Trecerea secundelor: " << m_secondsPassed << "\r";
		if (m_secondsPassed == secunde_afisare && secunde_afisare <= 55)
		{
			secunde_afisare += (30 / (sizeText / 2));
			//aici ar trebui sa i spunem clientului sa mai afiseze un indiciu;
		}
	}
}

bool skribbl::GameRound::verifGuess()
{
	//aici vedem cum verificam daca player ul a ghicit
	//dupa ce stabilim cum implementam ghiceala, tot aici ar trebui sa actualizam in m_scondsForGuess 
	//in cate secunde a ghicit
	return false;
}

void skribbl::GameRound::computeScore()
{
	int secAvg = 0;
	for (auto i : m_secondsForGuess)
	{
		secAvg += i.second;
	}
	secAvg = secAvg / m_secondsForGuess.size();
	if (secAvg != 0)
	{
		m_pointsAcumulated[m_painter->GetName()] = (60 - secAvg) * 100 / 60;
	}
	else
	{
		m_pointsAcumulated[m_painter->GetName()] = -100;
	}
	for (auto it = m_restOfPlayers.begin(); it != m_restOfPlayers.end(); it++)
	{
		if (m_secondsForGuess[it->get()->GetName()] != 0)
		{
			m_pointsAcumulated[it->get()->GetName()] = (60 - m_secondsForGuess[it->get()->GetName()]) * 100 / 30;
		}
		else
		{
			m_pointsAcumulated[it->get()->GetName()] = -100;
		}
	}

}

int skribbl::GameRound::swapPainter(int index)
{
	std::swap(m_painter, m_restOfPlayers[index]);
	return ++index;
}

void skribbl::GameRound::endOfRoundTimer()
{
	//in timpul timer ului astuia o sa afisam in client tabela cu scorul deci ar trebui sa o transmitem
	//in client :*
	m_secondsPassed = 0;
	clock_t start = clock();
	while (m_secondsPassed != 10)
	{
		clock_t curent = clock();
		m_secondsPassed = (curent - start) / CLOCKS_PER_SEC;
	}
}


