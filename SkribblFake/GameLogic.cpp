#include "GameLogic.h"
#include<ctime>
#include<iostream>

void GameLogic::TimePassing(Word word)
{
	clock_t start = clock();
	int seconds_passed = 0;
	int secunde_afisare = 30;
	int size_text = word.getSizeUnrevealedWord();
	while (seconds_passed != 60)
	{

		clock_t curent = clock();
		seconds_passed = (curent - start) / CLOCKS_PER_SEC;
		std::cout << "Trecerea secundelor: " << seconds_passed << "\r";
		if (seconds_passed == secunde_afisare && secunde_afisare <= 55)
		{
			word.revealOneRandomLetter();
			std::cout << std::endl << word.getCurrentSlotState() << std::endl;
			secunde_afisare += (30 / (size_text / 2));
		}
	}
	std::cout << "Cuvantul este: " << word.getWord();
}
